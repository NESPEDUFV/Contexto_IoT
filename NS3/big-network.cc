#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ssid.h"
#include "ns3/yans-wifi-helper.h"
#include <ctime>
#include <iostream>
/*  Redes com multiplos pontos de acesso 
    Aqui nós padrão também são ap, rede igual 


    n n n n ap n n
    n n n n ap n n n n n
    n n n n ap n n n n n
    n n n n ap n n n n n


*/

/*

    n
    n
    n
    n45
    n36
    n27
    n18
    n9



*/

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("quinto-script");

int main(int argc, char* argv[]){
    time_t comeco;
    time(&comeco);
    // Habilitando Logs
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    LogComponentEnable("quinto-script", LOG_LEVEL_INFO);
    
    int nsta = 10;

    CommandLine cmd(__FILE__);
    cmd.AddValue("nsta", "Number of \"extra\" CSMA nodes/devices", nsta);

    cmd.Parse(argc, argv);

    nsta = nsta == 0 ? 1 : nsta;

    NodeContainer sta1, ap1, all;
    sta1.Create(nsta);
    ap1.Create((int) nsta/9 + 1);

    all = all.GetGlobal();

    NS_LOG_INFO("sta nodes " << sta1.GetN());
    NS_LOG_INFO("ap nodes " << ap1.GetN());
    NS_LOG_INFO("all nodes " << all.GetN());

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
                                  DoubleValue(3.0),
                                  "DeltaY",
                                  DoubleValue(5.0),
                                  "GridWidth",
                                  UintegerValue(9),
                                  "LayoutType",
                                  StringValue("RowFirst"));

    /* O que estamos criando com a mobilidade:

        - começando a colocar nós no ponto (MinX, MinY)
        - colocando GridWidth nós por "linha"
        - os nós estarão a DeltaX de distancia dos outros em x
        - os nós estarão a DeltaY de distancia dos outros em y 
                                                   X   Y
        - temos espaço para colocar aps no vetor [14,  i] com
          i variando de acordo com a quantidade de nós ap
    */ 

    // TODO: Alocar na mão os sta
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(sta1);

    Ptr<ListPositionAllocator> positionAllocator = CreateObject<ListPositionAllocator>();
    for (int i=0; i < (int) ap1.GetN(); i+=5){
        positionAllocator->Add(Vector(14, i, 0));    
    }

    mobility.SetPositionAllocator(positionAllocator); 
    // Aqui foi criado um alocador de posições específicas para os aps
    
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(ap1);

    InternetStackHelper stack;
    stack.Install(all);

    Ipv4AddressHelper address;

    Ipv4InterfaceContainer staInterface1, ap1Interface1;

    address.SetBase("10.0.0.0", "255.0.0.0");
    staInterface1 = address.Assign(staDevices1);
    ap1Interface1 = address.Assign(apDevices1);

    // ELE SOBRESCREVE OS ENDEREÇOS, FDM

    NS_LOG_INFO("endereço de sta[0] " << staInterface1.GetAddress(0));
    NS_LOG_INFO("endereço de sta[nsta-1] " << staInterface1.GetAddress(nsta-1));

    UdpEchoServerHelper echoServer(9);

    ApplicationContainer serverApps = echoServer.Install(sta1.Get(0));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(staInterface1.GetAddress(0), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(sta1.Get(nsta-1));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();
    
    Simulator::Stop(Seconds(10.0));

    Simulator::Run();
    Simulator::Destroy();
    std::cout << "Tempo decorrido: " << time(NULL) - comeco << "\n";

return 0;
}
