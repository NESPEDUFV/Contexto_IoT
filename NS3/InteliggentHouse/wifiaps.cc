#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/netanim-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("MultiApWifiExample");

void CourseChange(std::string context, Ptr<const MobilityModel> model)
{
    Vector position = model->GetPosition();
    NS_LOG_UNCOND(context << " x = " << position.x << ", y = " << position.y);
}

int
main(int argc, char* argv[])
{
    bool verbose = true;
    bool tracing = false;
    uint32_t nWifi = 50; // Número de nós móveis
    uint32_t nAp = 3;   // Número de APs

    CommandLine cmd(__FILE__);
    cmd.AddValue("verbose", "Tell echo applications to log if true", verbose);
    cmd.AddValue("tracing", "Enable pcap tracing", tracing);
    cmd.AddValue("nWifi", "Number of wifi STA devices", nWifi);
    cmd.AddValue("nAp", "Number of wifi AP devices", nAp);
    cmd.Parse(argc, argv);

    if (verbose)
    {
        LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
        LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    }

    NodeContainer wifiStaNodes;
    wifiStaNodes.Create(nWifi);
    NodeContainer wifiApNodes;
    wifiApNodes.Create(nAp);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    Ssid ssid = Ssid("ns-3-ssid");

    WifiHelper wifi;
    wifi.SetRemoteStationManager("ns3::MinstrelHtWifiManager");

    NetDeviceContainer staDevices;
    mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid), "ActiveProbing", BooleanValue(false));
    staDevices = wifi.Install(phy, mac, wifiStaNodes);

    NetDeviceContainer apDevices;
    mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
    apDevices = wifi.Install(phy, mac, wifiApNodes);

    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", DoubleValue(0.0),
                                  "MinY", DoubleValue(0.0),
                                  "DeltaX", DoubleValue(10.0),
                                  "DeltaY", DoubleValue(10.0),
                                  "GridWidth", UintegerValue(10),
                                  "LayoutType", StringValue("RowFirst"));

    mobility.SetMobilityModel("ns3::RandomWalk2dMobilityModel",
                              "Bounds", RectangleValue(Rectangle(-200, 200, -200, 200)));
    
    //set the bounds for include 10 nwifi
    mobility.Install(wifiStaNodes);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiApNodes);

    InternetStackHelper stack;
    stack.Install(wifiApNodes);
    stack.Install(wifiStaNodes);

    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer staInterfaces;
    staInterfaces = address.Assign(staDevices);
    Ipv4InterfaceContainer apInterfaces;
    apInterfaces = address.Assign(apDevices);

    // Install UDP Echo Server on each STA node
    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(wifiStaNodes);
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    // Install UDP Echo Client on each AP node to send messages to each STA node
    for (uint32_t i = 0; i < nWifi; ++i)
    {
        UdpEchoClientHelper echoClient(staInterfaces.GetAddress(i), 9);
        echoClient.SetAttribute("MaxPackets", UintegerValue(1));
        echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
        echoClient.SetAttribute("PacketSize", UintegerValue(1024));

        ApplicationContainer clientApps = echoClient.Install(wifiApNodes.Get(i % nAp));
        clientApps.Stop(Seconds(10.0));
    }

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds(10.0));

    Config::Connect("/NodeList/*/$ns3::MobilityModel/CourseChange", MakeCallback(&CourseChange));

    if (tracing)
    {
        phy.SetPcapDataLinkType(WifiPhyHelper::DLT_IEEE802_11_RADIO);
        phy.EnablePcap("multi-ap-wifi", apDevices.Get(0));
    }
    AnimationInterface anim("multi-ap-wifi.xml");

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}