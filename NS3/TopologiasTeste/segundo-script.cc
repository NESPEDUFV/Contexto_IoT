#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
//#include "ns3/network-module.h"
#include "ns3/csma-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/ipv6-routing-table-entry.h"
#include "ns3/ipv6-static-routing-helper.h"
#include <fstream>
// Default Network Topology
//
//   router        
//     r0   Ipv6
//     |--------------- n1
//     |    Ipv6
//     |--------------- n2
//     |    Ipv6
//     |--------------- n3
//
//   all point-to-point or csma, with Ipv6
//

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("SegundoExemplo");

int
main(int argc, char** argv){

    Time::SetResolution(Time::NS);

    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    LogComponentEnable("SegundoExemplo", LOG_LEVEL_INFO);
    //LogComponentEnable("Ipv6Interface", LOG_LEVEL_ALL);

    // Criando nós e suas respectivas ligações p2p

    NS_LOG_INFO("Create nodes.");
    Ptr<Node> r0 = CreateObject<Node>();
    Ptr<Node> n1 = CreateObject<Node>();
    Ptr<Node> n2 = CreateObject<Node>();
    Ptr<Node> n3 = CreateObject<Node>();

    // container é como se fosse um vetor
    NS_LOG_INFO("Create node containers.");
    NodeContainer net1(r0, n1);
    NodeContainer net2(r0, n2);
    NodeContainer net3(r0, n3);
    NodeContainer all(r0, n1, n2, n3);

    NS_LOG_INFO("Create internet stack.");
    InternetStackHelper stack;
    stack.Install(all);

    // vamos usar csma em vez de p2p pra ver se funciona esse trem
    // funcionou com csma pq eu escrevi errado uma parte lá embaixo
    // vamos tentar com p2p novamente

    NS_LOG_INFO("Create channels.");
    PointToPointHelper p2p;
    p2p.SetChannelAttribute("Delay", StringValue("1ms"));
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));

    NetDeviceContainer d1 = p2p.Install(net1);
    NetDeviceContainer d2 = p2p.Install(net2);
    NetDeviceContainer d3 = p2p.Install(net3);

    //CsmaHelper csma;
    //csma.SetChannelAttribute("DataRate", DataRateValue(5000000));
    //csma.SetChannelAttribute("Delay", TimeValue(MilliSeconds(2)));
    //NetDeviceContainer d1 = csma.Install(net1);
    //NetDeviceContainer d2 = csma.Install(net2);
    //NetDeviceContainer d3 = csma.Install(net3);

    // OBS: a os containers trata os nós como um vetor, se o container recebe 
    // vários outros containers (com Add) ele só concatena os "vetores":
    // c1 = [n1, n2]
    // c2 = [n2, n3]
    // interface = helper.Assign(c1)
    // interface = [n1, n2]
    // interface.Add(helper.Assign(c2))
    // interface = [n1, n2, n2, n3]

    NS_LOG_INFO("Create networks and assign IPv6 addresses.");
    Ipv6AddressHelper ipv6;
    
    ipv6.SetBase(Ipv6Address("2001:1::"), Ipv6Prefix(64));
    Ipv6InterfaceContainer i1 = ipv6.Assign(d1);
    i1.SetForwarding(0, true);
    i1.SetDefaultRouteInAllNodes(0); 
    //NS_LOG_INFO("Fez i1");

    ipv6.SetBase(Ipv6Address("2001:2::"), Ipv6Prefix(64));
    Ipv6InterfaceContainer i2 = ipv6.Assign(d2);
    //i2.SetForwarding(0, true);
    //i2.SetDefaultRouteInAllNodes(0);
    //NS_LOG_INFO("Fez i2");

    ipv6.SetBase(Ipv6Address("2001:3::"), Ipv6Prefix(64));
    Ipv6InterfaceContainer i3 = ipv6.Assign(d3);
    //i3.SetForwarding(0, true);
    //i3.SetDefaultRouteInAllNodes(0);    
    //NS_LOG_INFO("Fez i3");

    uint32_t packetSize = 4096;
    uint32_t maxPacketCount = 1;

    UdpEchoClientHelper echoClient(i1.GetAddress(1, 1), 9);
    echoClient.SetAttribute("PacketSize", UintegerValue(packetSize));
    echoClient.SetAttribute("MaxPackets", UintegerValue(maxPacketCount));
    ApplicationContainer clientApps = echoClient.Install(net3.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    UdpEchoServerHelper echoServer(9);
    ApplicationContainer serverApps = echoServer.Install(net1.Get(1));
    serverApps.Start(Seconds(0.0));
    serverApps.Stop(Seconds(20.0));

    // Inicialização da simulação
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}

// REFATORAR O COD AGORA N0 SENDO UM ROTEADOR 