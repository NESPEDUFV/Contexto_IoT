#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

/*               n3   
*                |
*     n0 n1 n2  n4-----n5  n6  n7  n8
*     |  |  |   |      |   |   |   |
*     ===========      =============
*/

using namespace ns3;
NS_LOG_COMPONENT_DEFINE("teste2");

int main(int argc, char *argv[])
{
    Time::SetResolution(Time::NS);
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    Ptr<Node>n3 = CreateObject<Node>();
    Ptr<Node>n4 = CreateObject<Node>();
    Ptr<Node>n5 = CreateObject<Node>();

    NodeContainer p2pOne(n4,n3);
    NodeContainer p2pTwo(n4,n5);

    NodeContainer csmaConteinerOne;
    csmaConteinerOne.Create(3);
    csmaConteinerOne.Add(n4);
    NodeContainer csmaConteinerTwo;
    csmaConteinerTwo.Add(n5);
    csmaConteinerTwo.Create(3);

    PointToPointHelper p2p;
    p2p.SetDeviceAttribute("DataRate", StringValue("5Mbps"));
    p2p.SetChannelAttribute("Delay", StringValue("2ms"));
    
    NetDeviceContainer p2pDeviceOne,p2pDeviceTwo;
    p2pDeviceOne = p2p.Install(p2pOne);
    p2pDeviceTwo = p2p.Install(p2pTwo);

    CsmaHelper csma;
    csma.SetChannelAttribute("DataRate", StringValue("100Mbps"));
    csma.SetChannelAttribute("Delay", TimeValue(NanoSeconds(6560)));

    NetDeviceContainer csmaDeviceOne,csmaDeviceTwo;
    csmaDeviceOne = csma.Install(csmaConteinerOne);
    csmaDeviceTwo = csma.Install(csmaConteinerTwo);

    InternetStackHelper stack;
    stack.Install(p2pOne);
    stack.Install(p2pTwo);
    stack.Install(csmaConteinerOne);
    stack.Install(csmaConteinerTwo);

    Ipv4AddressHelper address;

    address.SetBase("10.1.1.0","255.255.255.0");
    Ipv4InterfaceContainer p2pIntefaceOne = address.Assign(p2pDeviceOne);

    address.SetBase("10.1.2.0","255.255.255.0");
    Ipv4InterfaceContainer p2pIntefaceTwo = address.Assign(p2pDeviceTwo);

    address.SetBase("10.1.3.0","255.255.255.0");
    Ipv4InterfaceContainer csmaIntefaceOne = address.Assign(csmaDeviceOne);

    address.SetBase("10.1.4.0","255.255.255.0");
    Ipv4InterfaceContainer csmaIntefaceTwo = address.Assign(csmaDeviceTwo);

    Ipv4GlobalRoutingHelper::PopulateRoutingTables();//perguntar sobre

    UdpEchoServerHelper echoServer(9);

   ApplicationContainer serverApps = echoServer.Install(csmaConteinerOne.Get(0));
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(csmaIntefaceOne.GetAddress(0), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    ApplicationContainer clientApps = echoClient.Install(csmaConteinerTwo.Get(3));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    

    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
