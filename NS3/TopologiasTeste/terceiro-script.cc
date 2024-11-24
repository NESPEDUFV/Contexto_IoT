// O objetivo deste script é entender como se usa o módulo wifi
// para isso vamos fazer um teste simples ligando 2 nós a um
// roteador e transmitir uma mensagem entre eles
// neste exempĺo não vamos nos preocupar com mobilidade

/*
    A                B
    *        *       *  
    |        |       |
    n0      |_|      n1  
            ap
        (roteador)

*/ 

// ele me obriga settar mobilidade para nó wifi :(

#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("terceiro-script");

int
main(int argc, char* argv[])
{
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    Ptr<Node> n0 = CreateObject<Node>();
    Ptr<Node> n1 = CreateObject<Node>();
    Ptr<Node> r0 = CreateObject<Node>();

    NodeContainer all(n0, n1, r0);
    NodeContainer wifiStaNodes(n0, n1);
    NodeContainer wifiApNodes(r0);

    YansWifiChannelHelper channel = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy;
    phy.SetChannel(channel.Create());

    WifiMacHelper mac;
    Ssid ssid = Ssid("ns-3-ssid");

    WifiHelper wifi;

    NetDeviceContainer staDevices;
    mac.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid),
                "ActiveProbing", BooleanValue(false));
    staDevices = wifi.Install(phy, mac, wifiStaNodes);

    NetDeviceContainer apDevices;
    mac.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid));
    apDevices = wifi.Install(phy, mac, wifiApNodes);

    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", 
                                  DoubleValue(0.0),
                                  "MinY",
                                  DoubleValue(0.0),
                                  "DeltaX",
                                  DoubleValue(5.0),
                                  "DeltaY",
                                  DoubleValue(5.0),
                                  "GridWidth",
                                  UintegerValue(3),
                                  "LayoutType",
                                  StringValue("RowFirst"));
    
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(all);

    InternetStackHelper stack;
    stack.Install(all);

    Ipv6AddressHelper ipv6;
    ipv6.SetBase(Ipv6Address("2024:1::"), Ipv6Prefix(64));
    Ipv6InterfaceContainer i1 = ipv6.Assign(staDevices);
    Ipv6InterfaceContainer i2 = ipv6.Assign(apDevices);
    i2.SetForwarding(0, true);
    i2.SetDefaultRouteInAllNodes(0);

    uint32_t packetSize = 4096;
    uint32_t maxPacketCount = 1;

    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(wifiStaNodes.Get(0));
    serverApps.Start(Seconds(0.0));
    serverApps.Stop(Seconds(20.0));

    UdpEchoClientHelper echoClient(i1.GetAddress(0, 1), 9);
    echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));
    echoClient.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
    ApplicationContainer clientApps = echoClient.Install(wifiStaNodes.Get(1));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Simulator::Stop(Seconds(10.0));

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
 // precisa tomar cuidado pq não fechou o programa