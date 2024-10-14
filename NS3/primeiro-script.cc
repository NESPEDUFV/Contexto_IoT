// Includes basicos >>> verificar a necessidade de disponibilidade

// Aplicação base (possível criar outras utilizando herança de POO)
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"

// Namespace para aumentar legibilidade
using namespace ns3;

// Definindo o nome do log
NS_LOG_COMPONENT_DEFINE("PrimeiroScript");

// Aqui começa de fato o script
// Vamos fazer primeiro o first.cc e depois aumentá-lo em outro projeto
//
//     10.1.1.0
// n0 ------------ n1
//   ponto-a-ponto
//
// Basicamente esse é um simples projeto de eco cliente e servidor
// utilizando o UDP

int main(int argc, char* argv[]){

    // O simulador trabalha com escalas de tempo, dependendo do que e
    // como será usado, é interessante editar a escala (verifique o
    // ENUM da classe para ver as opções)
    Time::SetResolution(Time::NS);

    // Para conseguir ver os resultados é necessário habilitar os logs
    // correspondentes
    LogComponentEnable("UdpEchoClientApplication", LOG_LEVEL_INFO);
    LogComponentEnable("UdpEchoServerApplication", LOG_LEVEL_INFO);

    // Agora vamos começar pelo basico: criar nós
    // Para criar e editar os nós o ns3 utilisa-se de um conceito de 
    // "containers", que basicamente junta todos os semelhantes e
    // faz as alterações todos de uma só vez, a priori parece confuso,
    // mas vamo lá, tu consegue
    NodeContainer nodes;
    nodes.Create(2);

    // Agora vamos unir os nós com um enlace ponto a ponto, para isso 
    // teremos de usar o PointoToPointHelper, que possibilitará a edição
    // do canal de enlace e a instalação deles nos nós
    PointToPointHelper pointToPoint;

    // Para ver todos os atributos de dispositivo modificáveis do enlace 
    // acesse:
    // https://www.nsnam.org/docs/release/3.16/doxygen/classns3_1_1_point_to_point_net_device.html 
    pointToPoint.SetDeviceAttribute("DataRate", StringValue("5Mbps")); 
    // Para ver todos os atributos do canal basta procurar no Doxigen
    // "PointToPointChannel"
    pointToPoint.SetChannelAttribute("Delay", StringValue("2ms"));

    // Utilizamos NodeContainer apenas para criar os nós da simulação,
    // agora vamos instalar neles o dispositivo e as configurações de 
    // enlace criadas, gerando assim dispositivos de rede (agora não 
    // são apenas "nós"). Usaremos então um NetDeviceContainer para 
    // persistir a rede criada (note que se deseja usar diversos tipos
    // de enlace é necessário criar os nós separadamente. É possível
    // também que um nó tenha mais de um tipo de enlace, basta que o
    // mesmo nó esteja em "NodeContainers diferentes" veja em second.cc
    // note também que por ser um canal ponto a ponto é necessário que 
    // o NodeContainer tenha apenas 2 nós
    NetDeviceContainer devices;
    devices = pointToPoint.Install(nodes);

    // Após ter instalado, temos dois nós: cada um com um dispositivo
    // ponto a ponto instalado em um único canal entre eles.

    // Agora vamos instalar os protocolos de internet em cada nó
    InternetStackHelper stack;
    stack.Install(nodes);

    // Agora teremos que associar os nós dos dispositivos com 
    // endereços IP, vamos utilizar aqui IPV4, mas pode ser IPV6, etc...
    Ipv4AddressHelper address;
    address.SetBase("10.1.1.0", "255.255.255.0"); // (address, mask, init)

    // Vai gerando endereços até o limite de nós ou limite da mascara, 
    // Gera erro se tentar usar um mesmo endereço para dispositivos
    // diferentes

    // Para fazer associação entre uma faixa de endereços IPs e um 
    // conteiner de dispositivos é necessário usar Ipv4Interface
    Ipv4InterfaceContainer interfaces;
    interfaces = address.Assign(devices);

    // Agora temos toda a topologia da rede já montada e pronta pra uso
    // Vamos adicionar aplicações para gerar tráfego na rede, echo udp.
    UdpEchoServerHelper echoServer(9); // 9 é a porta
    ApplicationContainer serverApps;
    serverApps = echoServer.Install(nodes.Get(1)); // n1 é nosso server
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    // Vamos agora fazer o cliente falar com o servidor
    // Basicamente criamos uma aplicação que irá mandar uma mensagem ao
    // servidor (endereço do servidor n1, porta da aplicação)
    UdpEchoClientHelper echoClient(interfaces.GetAddress(1), 9);
    echoClient.SetAttribute("MaxPackets", UintegerValue(1));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(1024));

    // n0 é nosso cliente
    ApplicationContainer clientApps = echoClient.Install(nodes.Get(0));
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    Simulator::Run();
    Simulator::Destroy();
    
    return 0;
}
