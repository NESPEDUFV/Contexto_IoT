#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/netanim-module.h"
#include "ns3/wifi-module.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE("GridCommunication");

int main(int argc, char* argv[])
{
    // Configurar grid 21x21
    uint32_t gridSize = 21;

    // Criar grupos de nós
    NodeContainer computadorNode;
    computadorNode.Create(1);

    NodeContainer espelhoNodes;
    espelhoNodes.Create(2);

    NodeContainer televisaoNode;
    televisaoNode.Create(1);

    NodeContainer echoDotNodes;
    echoDotNodes.Create(2);

    NodeContainer cameraNodes;
    cameraNodes.Create(5);

    NodeContainer sofaNode;
    sofaNode.Create(1);

    NodeContainer camaNode;
    camaNode.Create(1);

    // Combinar todos os nós
    NodeContainer allNodes = NodeContainer(computadorNode, espelhoNodes, televisaoNode, 
                                           echoDotNodes, cameraNodes, sofaNode, camaNode);

    // Configurar pilha de internet
    InternetStackHelper internet;
    internet.Install(allNodes);

    // Atribuir endereços IP
    Ipv4AddressHelper ipv4;
    ipv4.SetBase("10.1.0.0", "255.255.255.0");

    Ipv4InterfaceContainer interfaces = ipv4.Assign(NetDeviceContainer());

    // Configurar mobilidade em um grid fixo de 21x21
    MobilityHelper mobility;
    mobility.SetPositionAllocator("ns3::GridPositionAllocator",
                                  "MinX", DoubleValue(0.0),
                                  "MinY", DoubleValue(0.0),
                                  "DeltaX", DoubleValue(1.0),
                                  "DeltaY", DoubleValue(1.0),
                                  "GridWidth", UintegerValue(gridSize),
                                  "LayoutType", StringValue("RowFirst"));
    mobility.SetMobilityModel("ns3::ConstantPositionMobilityModel");
    mobility.Install(allNodes);

    // Posicionar os objetos manualmente (considerando y de baixo para cima)
    Ptr<MobilityModel> position;
    position = computadorNode.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(6, 5, 0.0)); // Computador

    position = espelhoNodes.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(7, 2, 0.0)); // Espelho Inteligente 1

    position = espelhoNodes.Get(1)->GetObject<MobilityModel>();
    position->SetPosition(Vector(12, 3, 0.0)); // Espelho Inteligente 2

    position = televisaoNode.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(9, 11, 0.0)); // Televisão

    position = echoDotNodes.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(7, 5, 0.0)); // Echo Dot Alexa 1

    position = echoDotNodes.Get(1)->GetObject<MobilityModel>();
    position->SetPosition(Vector(19, 4, 0.0)); // Echo Dot Alexa 2

    position = cameraNodes.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(2, 13, 0.0)); // Câmera 1

    position = cameraNodes.Get(1)->GetObject<MobilityModel>();
    position->SetPosition(Vector(11, 12, 0.0)); // Câmera 2

    position = cameraNodes.Get(2)->GetObject<MobilityModel>();
    position->SetPosition(Vector(12, 12, 0.0)); // Câmera 3

    position = cameraNodes.Get(3)->GetObject<MobilityModel>();
    position->SetPosition(Vector(12, 8, 0.0)); // Câmera 4

    position = cameraNodes.Get(4)->GetObject<MobilityModel>();
    position->SetPosition(Vector(2, 6, 0.0)); // Câmera 5

    position = sofaNode.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(9, 8, 0.0)); // Sofá

    position = camaNode.Get(0)->GetObject<MobilityModel>();
    position->SetPosition(Vector(3, 3, 0.0)); // Cama

    // Configurar comunicação de eco entre os nós
    uint16_t port = 9; // Porta de comunicação
    UdpEchoServerHelper echoServer(port);

    ApplicationContainer serverApps = echoServer.Install(allNodes);
    serverApps.Start(Seconds(1.0));
    serverApps.Stop(Seconds(10.0));

    UdpEchoClientHelper echoClient(Ipv4Address("10.1.0.1"), port);
    echoClient.SetAttribute("MaxPackets", UintegerValue(10));
    echoClient.SetAttribute("Interval", TimeValue(Seconds(1.0)));
    echoClient.SetAttribute("PacketSize", UintegerValue(512));

    ApplicationContainer clientApps = echoClient.Install(allNodes);
    clientApps.Start(Seconds(2.0));
    clientApps.Stop(Seconds(10.0));

    // Configurar animação
    AnimationInterface anim("grid-communication.xml");
    anim.SetBackgroundImage("NS3/InteliggentHouse/casaInteligente.png", 0, 0, 0.02, 0.02, 0.7);

    // Definir legendas para os nós
    anim.UpdateNodeDescription(computadorNode.Get(0), "Computador");
    anim.UpdateNodeDescription(espelhoNodes.Get(0), "Espelho Inteligente 1");
    anim.UpdateNodeDescription(espelhoNodes.Get(1), "Espelho Inteligente 2");
    anim.UpdateNodeDescription(televisaoNode.Get(0), "Televisão");
    anim.UpdateNodeDescription(echoDotNodes.Get(0), "Echo Dot Alexa 1");
    anim.UpdateNodeDescription(echoDotNodes.Get(1), "Echo Dot Alexa 2");
    anim.UpdateNodeDescription(cameraNodes.Get(0), "Câmera 1");
    anim.UpdateNodeDescription(cameraNodes.Get(1), "Câmera 2");
    anim.UpdateNodeDescription(cameraNodes.Get(2), "Câmera 3");
    anim.UpdateNodeDescription(cameraNodes.Get(3), "Câmera 4");
    anim.UpdateNodeDescription(cameraNodes.Get(4), "Câmera 5");
    anim.UpdateNodeDescription(sofaNode.Get(0), "Sofá");
    anim.UpdateNodeDescription(camaNode.Get(0), "Cama");
     // Colorir os grupos
    anim.UpdateNodeColor(computadorNode.Get(0), 255, 0, 0); // Vermelho
    anim.UpdateNodeColor(espelhoNodes.Get(0), 0, 255, 0);   // Verde
    anim.UpdateNodeColor(espelhoNodes.Get(1), 0, 255, 0);
    anim.UpdateNodeColor(televisaoNode.Get(0), 0, 0, 255);  // Azul
    anim.UpdateNodeColor(echoDotNodes.Get(0), 255, 255, 0); // Amarelo
    anim.UpdateNodeColor(echoDotNodes.Get(1), 255, 255, 0);
    anim.UpdateNodeColor(cameraNodes.Get(0), 255, 0, 255);  // Magenta
    anim.UpdateNodeColor(cameraNodes.Get(1), 255, 0, 255);
    anim.UpdateNodeColor(cameraNodes.Get(2), 255, 0, 255);
    anim.UpdateNodeColor(cameraNodes.Get(3), 255, 0, 255);
    anim.UpdateNodeColor(cameraNodes.Get(4), 255, 0, 255);
    anim.UpdateNodeColor(sofaNode.Get(0), 0, 255, 255);     // Ciano
    anim.UpdateNodeColor(camaNode.Get(0), 128, 64, 0);      // Marrom

    Simulator::Run();
    Simulator::Destroy();
    return 0;
}