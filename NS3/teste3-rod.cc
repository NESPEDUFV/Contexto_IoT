#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"

/*           (6) AP
*        *   *   *
*        |   |   |  (2)    (1)      (5)
*       n5  n6  n7------n0-------n1  n2  n3
*                |               |   |   |
*             (3)|               =========
*                n8  n9  n10       
*                |    |   |
*                *    *   *
*               AP    (4)
*/

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("teste3");

int main(int argc, char  *argv[])
{
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    Ptr<Node> n0 = CreateObject<Node>();
    Ptr<Node> n1 = CreateObject<Node>();
    Ptr<Node> n7 = CreateObject<Node>();
    Ptr<Node> n8 = CreateObject<Node>();
    NodeContainer p2pOne (n0,n1);
    NodeContainer p2pTwo (n0,n7);
    NodeContainer p2pThree(n7,n8);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));

    NetDeviceContainer p2pDeviceOne, p2pDeviceTwo, p2pDeviceThree;
    p2pDeviceOne = p2p.Install(p2pOne);
    p2pDeviceTwo = p2p.Install(p2pTwo);
    p2pDeviceThree = p2p.Install(p2pThree);

    NodeContainer csmaOne;
    csmaOne.Add(n1);
    csmaOne.Create(200);

    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

    NetDeviceContainer csmaDevice;
    csmaDevice = csma.Install(csmaOne);

    NodeContainer wifiStaOne;
    wifiStaOne.Create(2);
    NodeContainer wifiApOne = n7;

    YansWifiChannelHelper channelOne = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phyOne;
    phyOne.SetChannel(channelOne.Create());

    WifiMacHelper macOne;
    Ssid ssidOne = Ssid("RedeWifiOne");

    WifiHelper wifi;

    NetDeviceContainer staDevicesOne;
    macOne.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssidOne), "ActiveProbing", BooleanValue(false));
    staDevicesOne = wifi.Install(phyOne, macOne, wifiStaOne);

    NetDeviceContainer apDevicesOne;
    macOne.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssidOne));
    apDevicesOne = wifi.Install(phyOne, macOne, wifiApOne);   

    MobilityHelper mobility;

    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX",
                                  DoubleValue(0.0),
                                  "MinY",
                                  DoubleValue(0.0),
                                  "DeltaX",
                                  DoubleValue(5.0),
                                  "DeltaY",
                                  DoubleValue(10.0),
                                  "GridWidth",
                                  UintegerValue(3),
                                  "LayoutType",
                                  StringValue("RowFirst"));

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiStaOne);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiApOne);



    NodeContainer wifiStaTwo;
    wifiStaTwo.Create(2);
    NodeContainer wifiApTwo = n8;

    YansWifiChannelHelper channelTwo = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phyTwo;
    phyTwo.SetChannel(channelTwo.Create());

    WifiMacHelper macTwo;
    Ssid ssidTwo = Ssid("RedeWifiTwo");

    NetDeviceContainer staDevicesTwo;
    macTwo.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssidTwo), "ActiveProbing", BooleanValue(false));
    staDevicesTwo = wifi.Install(phyTwo, macTwo, wifiStaTwo);

    NetDeviceContainer apDevicesTwo;
    macTwo.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssidTwo));
    apDevicesTwo = wifi.Install(phyTwo, macTwo, wifiApTwo);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiStaTwo);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(wifiApTwo);

    InternetStackHelper stack;
    stack.Install(p2pOne);
    stack.Install(p2pTwo);
    stack.Install(p2pThree);
    stack.Install(csmaOne);
    stack.Install(wifiStaOne);
    stack.Install(wifiApOne);
    stack.Install(wifiStaTwo);
    stack.Install(wifiApTwo);

    Ipv4AddressHelper address;

    address.SetBase("10.1.1.0", "255.255.255.0");
    Ipv4InterfaceContainer p2pInterfaceOne;
    p2pInterfaceOne = address.Assign(p2pDeviceOne);

    address.SetBase("10.1.2.0", "255.255.255.0");
    Ipv4InterfaceContainer p2pInterfaceTwo;
    p2pInterfaceTwo = address.Assign(p2pDeviceTwo);

    address.SetBase("10.1.3.0", "255.255.255.0");
    Ipv4InterfaceContainer p2pInterfaceThree;
    p2pInterfaceThree = address.Assign(p2pDeviceThree);

    address.SetBase("10.1.5.0", "255.255.255.0");
    Ipv4InterfaceContainer csmaInterfaceOne;
    csmaInterfaceOne = address.Assign(csmaDevice);

    address.SetBase("10.1.6.0", "255.255.255.0");
    Ipv4InterfaceContainer staInterfaceOne = address.Assign(staDevicesOne);
    Ipv4InterfaceContainer apInterfaceOne = address.Assign(apDevicesOne);

    address.SetBase("10.1.4.0", "255.255.255.0");
    Ipv4InterfaceContainer staInterfaceTwo = address.Assign(staDevicesTwo);
    Ipv4InterfaceContainer apInterfaceTwo = address.Assign(apDevicesTwo);

    UdpEchoServerHelper echoServer(9);

    ApplicationContainer serverApps = echoServer.Install(wifiStaOne.Get(0));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(staInterfaceOne.GetAddress(0), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(3));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(csmaOne.Get(1));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds(10.0));

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
