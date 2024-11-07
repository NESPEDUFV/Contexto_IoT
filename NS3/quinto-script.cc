#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"

/*  Redes com multiplos pontos de acesso 
    Aqui nós padrão também são ap, redes diferentes 

ap      ap                                                     
*   *   *   *   *   *
|   |   |   |   |   |
n0  n1  n2  n3  n4  n5
10.1.1.0    10.1.2.0

*/

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("quinto-script");

int main(int argc, char* argv[]){
    
    // Habilitando Logs
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    
    int nsta = 3;

    NodeContainer sta1, sta2;
    sta1.Create(nsta);
    sta2.Create(nsta);

    NodeContainer ap1, ap2;
    ap1.Add(sta1.Get(0));
    ap2.Add(sta1.Get(nsta-1));

// Criando ambiente 1
    YansWifiChannelHelper channel1 = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy1;
    phy1.SetChannel(channel1.Create());

    WifiMacHelper mac1;
    Ssid ssid1 = Ssid("RedeWifi1");

    WifiHelper wifi;

    NetDeviceContainer staDevices1;
    mac1.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid1), "ActiveProbing", BooleanValue(false));
    staDevices1 = wifi.Install(phy1, mac1, sta1);

    NetDeviceContainer apDevices1;
    mac1.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid1));
    apDevices1 = wifi.Install(phy1, mac1, ap1);   

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
                                  UintegerValue(10),
                                  "LayoutType",
                                  StringValue("RowFirst"));

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(sta1);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ap1);

    YansWifiChannelHelper channel2 = YansWifiChannelHelper::Default();
    YansWifiPhyHelper phy2;
    phy2.SetChannel(channel2.Create());

    WifiMacHelper mac2;
    Ssid ssid2 = Ssid("RedeWifi2");

    NetDeviceContainer staDevices2;
    mac2.SetType("ns3::StaWifiMac", "Ssid", SsidValue(ssid2), "ActiveProbing", BooleanValue(false));
    staDevices2 = wifi.Install(phy2, mac2, sta2);

    NetDeviceContainer apDevices2;
    mac2.SetType("ns3::ApWifiMac", "Ssid", SsidValue(ssid2));
    apDevices2 = wifi.Install(phy2, mac2, ap2);   
    
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(sta2);

    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ap2);

    InternetStackHelper stack;
    stack.Install(ap1);
    stack.Install(ap2);
    stack.Install(sta1);
    stack.Install(sta2);

    Ipv4AddressHelper address;

    Ipv4InterfaceContainer staInterface1, ap1Interface1;
    Ipv4InterfaceContainer staInterface2, ap2Interface2;

    address.SetBase("10.1.1.0", "255.255.255.0");
    staInterface1 = address.Assign(staDevices1);
    ap1Interface1 = address.Assign(apDevices1);

    address.SetBase("10.1.2.0", "255.255.255.0");
    staInterface2 = address.Assign(staDevices2);
    ap2Interface2 = address.Assign(apDevices2);

    UdpEchoServerHelper echoServer(9);

    ApplicationContainer serverApps = echoServer.Install(sta1.Get(0));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(staInterface1.GetAddress(0), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(sta2.Get(1));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();

    Simulator::Stop(Seconds(10.0));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
