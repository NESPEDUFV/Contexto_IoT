// Nesse script vamos gerar uma topologia um pouco mais complexa
// com vários tipos de conexão e diversos nós e roteadores
// vamos também implementar uma aplicação de "ping"
/*
                ap           ap
    *   *   *   *            *   *   *   * 
    |   |   |   |    p2p     |   |   |   | 
    n0  n1  n2  r0----------r1  n3  n4  n5    
                :
            p2p : 
                :
                r2  n6  n7 
                |   |   |
                ==========
                    LAN
*/
// todos com ipv6 para praticar
// será feito 2 pings: um de n7 até n4 e outro de n0 até n5


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

NS_LOG_COMPONENT_DEFINE("quarto-script");

int main(int argc, char* argv[]){
    
    // Habilitando Logs
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);
    
    // Declaração dos nós
    Ptr<Node> r0 = CreateObject<Node>();
    Ptr<Node> r1 = CreateObject<Node>();
    Ptr<Node> r2 = CreateObject<Node>();
    Ptr<Node> n0 = CreateObject<Node>();
    Ptr<Node> n1 = CreateObject<Node>();
    Ptr<Node> n2 = CreateObject<Node>();
    Ptr<Node> n3 = CreateObject<Node>();
    Ptr<Node> n4 = CreateObject<Node>();
    Ptr<Node> n5 = CreateObject<Node>();
    Ptr<Node> n6 = CreateObject<Node>();
    Ptr<Node> n7 = CreateObject<Node>();

    // Declaração dos containers (redes)   
    NodeContainer all(r0, r1, r2, n0, n1, n2 ,n3 ,n4, n5, n6);
    NodeContainer wifinet1ap(r0);
    NodeContainer wifinet2ap(r1);
    NodeContainer wifinet1sta(n0, n1, n2);
    NodeContainer wifinet2sta(n3, n4, n5);
    NodeContainer csmanet(r2, n6, n7);
    NodeContainer p2pr0r1(r0,r1);
    NodeContainer p2pr0r2(r0,r1);

    // Colocando a pilha de protocolos da internet nos nós
    InternetStackHelper stack;
    stack.Install(all);

    // Colocando a camada física nos nós (estabelecendo conexões)
    

    Simulator::Stop(Seconds(20.0));
    Simulator::Run();
    Simulator::Destroy();

    return 0;
}
