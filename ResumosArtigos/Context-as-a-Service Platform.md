# Context-as-a-Service Platform: Exchange and Share Context in an IoT Ecosystem

Com o crescimento gigante da internet das coisas a demanda por inteligencia orientada ao contexto vai ser um fator fundamental em diversas areas

No paper eles propuseram uma plataforma operacional chamada CoaaS que permite objetos inteligentes descobrir, validar e compartilhar contextos relevantes e confiáveis.

A plataforma consiste em

- Communication manager (tratamento inicial de todas as mensagens recebidas e enviadas: consultas de contexto, atualizações de contexto e respostas de contexto)
- uma engine (mecanismo) de consulta de contextos
- um mecanismo de raciocínio de contexto
- sistema de gerenciamento de armazenamento de contexto para gerenciamento de contexto escalável e orientado ao desempenho.

Eles usaram um estudo de casa de cidade inteligente: “Smart parking and charging for electrical vehicles”

Um número notável de abordagens de gerenciamento de contexto foi proposto pela comunidade de pesquisa [3-6]. As principais funcionalidades dessas plataformas de middleware de gerenciamento de contexto podem ser subdivididas em seis classes principais:

1. Raw Data Acquisition (Aquisição de dados brutos)
2. Context Storage (Armazenamento de contexto)
3. Context Lookup and Discovery (Consulta e descoberta de contexto)
4. Context Distribution(Distribuição de contexto)
5. Privacy, Security and Access Control (Privacidade, segurança e controle de acesso)
6. Context Processing and Reasoning (Processamento e raciocínio de contexto)

"No entanto, até onde sabemos, nenhuma das plataformas existentes conseguiu penetrar no mercado devido a várias deficiências que são destacadas na Secção II"

O CoaaS permite que os aplicativos forneçam e consumam contexto perfeitamente, sem exigir integração manual de silos de IoT.

(O que é silos?)
sources of context

Leitura Parte 2:

"Consequentemente, é possível construir uma plataforma de **middleware** que gerencie a interação com fontes de contexto e ofereça informações contextuais para aplicativos sensíveis ao contexto como um serviço."

"esses sistemas sofrem de uma série de restrições comuns que os tornam ineficientes para serem usados ​​em sistemas com reconhecimento de contexto do mundo real. Essas restrições incluíam **falta de tolerância a falhas** e **escalabilidade**, **suporte de interoperabilidade ruim** e **raciocínio ingênuo**"

" [...] falharam em evoluir para um nível padrão da indústria."

"Acreditamos que a principal deficiência desses sistemas de middleware é a falta de uma linguagem de consulta de contexto (CQL) abrangente e flexível que permita que aplicativos com reconhecimento de contexto reutilizem dados contextuais existentes com base em seus requisitos específicos [7]. "

Os autores dão foco na falta do uso de CQLs, visto que são pouco conhecidas e são muito importantes.

a principal motivação por trás do CoaaS é facilitar o compartilhamento de contexto fornecido por diferentes fontes, chamadas de Provedores de Contexto, com aplicativos sensíveis ao contexto, chamados de Consumidores de Contexto.

1. Context Provider (CP) refere-se a qualquer ponto final de IoT que pode fornecer um ou muitos Context Services. Um Context Service é uma interface que fornece contexto sobre uma entidade específica.
2. Context Consumer (CC) refere-se a qualquer ponto final de IoT que solicita informações contextuais sobre uma entidade de interesse. Um context consumer está interessado em coletar informações contextuais sobre uma entidade específica com certas características. Para atingir esse objetivo, o context consumer emitirá uma Context Query.
3. Consulta de contexto é uma solicitação de informações contextuais (contexto de baixo ou alto nível inferido de atributos de contexto) extraídas de uma ou muitas entidades.
4. Cada consulta de contexto pode ser dividida em várias sub-solicitações (Solicitações de Contexto), onde o resultado final da consulta será computado agregando os resultados dessas sub-solicitações, fornecendo-os diretamente sem alterações ou usando-os para inferir um contexto de nível superior.

As consultas assíncronas podem ser subdivididas em consultas de contexto baseadas em eventos e periódicas

Outra característica importante do CDQL é o suporte de funções de agregação e raciocínio (CONTEXT-FUNCTION) que permitem consultar contexto de alto nível e também mitigar os problemas de privacidade do compartilhamento de dados de provedores confidenciais com consumidores externos

CDQL aborda a interoperabilidade usando padrões baseados em domínio (por exemplo, ontologias, vocabulários semânticos, esquemas).

adotamos e estendemos a ontologia OWL-S [19] adicionando a descrição de contexto das entidades associadas aos serviços de contexto [8].

## CONTEXT-AS-A-SERVICE (COAAS) ARCHITECTURE

CoaaS framework is composed of four main components:

1. Security and Communication Manager
   1. podemos nn ter segurança a priori
2. Context Query Engine (CQE) *\**
   1. Query Parser pode ser simplificado
3. Context Storage Management System (CSMS), and
   1. ontologia
4. Context Reasoning Engine (CRE).
   1. não precisamos a priori (inferencia de contexto)

### Security and Communication Manager

**O Communication Manager é responsável pelo tratamento inicial de todas as mensagens recebidas e enviadas, ou seja, consultas de contexto, atualizações de contexto e respostas de contexto. Este módulo atua como um proxy e distribui todas as mensagens recebidas de CPs e CCs para os componentes correspondentes.**

Para garantir a privacidade e a segurança do CoaaS, este componente é vinculado ao módulo de segurança. O módulo de segurança verifica primeiramente a validade das mensagens recebidas e autentica as solicitações. Além disso, o Security Manager verifica se o consumidor de contexto tem acesso ao serviço de contexto solicitado ou não (autorização). Por fim, ele também é responsável por monitorar todas as mensagens recebidas para identificar quaisquer padrões suspeitos, como ataques de negação de serviço distribuído (DDoS).

### Context Query Engine (CQE)  

Este módulo é principalmente responsável por analisar as consultas recebidas, gerar e orquestrar o plano de execução da consulta e produzir o resultado final da consulta. Além disso, este componente também cuida de buscar os dados necessários dos provedores de contexto sob demanda.

Quando uma consulta é emitida para o CoaaS, após passar pelas verificações de segurança, ela será enviada para o **Query Parser**.

O **Query Parser** tem três responsabilidades principais:

- a saber, e analisar as consultas recebidas,
- dividi-las em várias solicitações de contexto e
- determinar o plano de execução da consulta.
Então, a consulta analisada mais o plano de execução serão passados ​​para o **Query Coordinator**.

O **Query Coordinator** desempenha um papel de orquestrador no CQE. Este módulo é responsável por gerenciar e monitorar todo o procedimento de execução de uma consulta de contexto.

Na próxima etapa, as solicitações de contexto serão enviadas para o **Context Service Discovery and Selector** (CSDS).

CSDS é responsável por encontrar o serviço de contexto mais apropriado para uma solicitação recebida. Este componente consiste em duas partes:

- O **Context Service Discovery**, que é implementado como parte do CSMS, encontra serviços de contexto que correspondem aos requisitos de uma solicitação de contexto. Ele passará as descrições dos serviços candidatos para o **Service Selector**.
O fluxo de trabalho deste componente consiste em duas partes. Primeiro, ele encontra serviços de contexto que correspondem aos requisitos de uma solicitação de contexto. Então, com base nos serviços descobertos, ele retorna um conjunto classificado dos melhores serviços de contexto disponíveis que podem satisfazer os requisitos de uma solicitação, considerando diferentes métricas, como Custo do Serviço e Qualidade do Serviço.

Execution plan generator: monta um grafo de dependencias, se der ciclo não é possível fazer a consulta
esse grafo é para paralelizar consultas de contexto que são dependentes de dispositivos diferentes

- Em seguida, o **Service Selector** retorna um conjunto classificado dos melhores serviços de contexto disponíveis que podem satisfazer os requisitos de uma solicitação considerando diferentes métricas, como Custo do Serviço e Qualidade do Serviço.

Após selecionar o melhor provedor de contexto elegível para cada solicitação de contexto, as solicitações serão passadas para o **Context Service Invoker**.

Este componente é responsável por buscar o contexto do provedor de contexto correspondente para recuperar as informações contextuais necessárias e passar as informações recuperadas para o agregador de consultas.

Finalmente, o **Query Aggregator** combina os resultados de todas as solicitações de contexto e forma o resultado final da consulta. Além disso, o contexto recuperado pode ser usado pelo CRE para produzir contexto de alto nível.

### Context Storage Management System (CSMS)

Explicado detalhadamente em [20].
Tem três objetivos principais

- Primeiro, para descoberta de serviço, precisamos de um repositório contendo descrições de serviços de contexto.
Contendo:
  - Possibilidade de registrar os provedores de serviço e a capacidade de atualizar o estado do serviço
  - Descoberta e seleção de serviços de contexto.

- Segundo, para garantir tempo de resposta de consulta razoável e lidar com problemas como latências de rede e potencial indisponibilidade de fontes de contexto, há uma necessidade de armazenar em cache informações contextuais.
  - Recommenders
  - Data Stream Engine?
  -

- Terceiro, o processo de derivação de contexto é baseado em padrões e histórico conhecidos, bem como na previsão de contexto futuro para permitir adaptação proativa.
  - Context repository
  -

As razões acima nos levam ao entendimento da necessidade de um **CSMS como parte central da plataforma de middleware CoaaS**.

O CSMS consiste em cinco componentes lógicos

O **Storage Query Execution Manager (SQEM)** é o ponto de entrada para solicitações de contexto do CQE. Ele traduz solicitações de entrada para as linguagens de consulta correspondentes dos datastores subjacentes e retorna resultados filtrados e agregados de volta ao CQE.

**O Context Service Description Module (CSDM)** facilita a descoberta de serviços.

**O Context Repository (CR)** armazena e gerencia informações contextuais relacionadas a entidades, que incluem valores atuais e históricos.

**O Subscription Module (SM)** facilita todo o processo de notificação dos assinantes (Observer?) sobre uma situação definida pelo CDQL detectada.
O SM também inclui um **Data Stream Engine (DSE)**, que permite o processamento escalável e de alto rendimento de um grande número de eventos de entrada para compreensão da situação quase em tempo real.

**O Performance Repository (PR)** contém logs e histórico de operação, que são essenciais para a análise do desempenho do sistema.

**Os Recommenders** são um conjunto de componentes de software projetados com o propósito de gerenciar o processo de consulta de armazenamento e ajustar o desempenho do sistema. Esses componentes de software dependem de dados coletados no PR. Os recomendadores abrangem áreas como recuperação e armazenamento proativo de dados, indexação adaptável e ordenação da execução de partes de consultas.

### Context Reasoning Engine (CRE)

Talvez não será nosso foco por agora

A principal tarefa do **Context Reasoning Engine** é inferir situações a partir de dados sensoriais brutos ou contexto primitivo de baixo nível existente.

É uma necessidade comum em muitos aplicativos de IoT com reconhecimento de contexto consultar sobre a situação de uma entidade de contexto ou disparar uma consulta quando uma situação específica é detectada.

As situações podem ser vistas como contexto de alto nível que é inferido de vários contextos de baixo nível[21].

**As situações geralmente dependem do aplicativo. Portanto, não é possível predefinir uma lista abrangente delas.**

Essa é a razão pela qual estendemos o CDQL para dar suporte à definição dinâmica de funções situacionais como parte da consulta.

No CoaaS, adotamos o modelo introduzido em [22] que define uma situação em ambientes generalizados como uma coleção de regiões em espaços multidimensionais.

Com base em [22], para representar a situação de uma entidade de contexto, três elementos devem ser definidos:

1. situações possíveis para uma entidade de contexto (Aplicações, contextos de alto nível?)
2. atributos de contexto que estão envolvidos no raciocínio (Tipo de contexto) e  
3. uma coleção de valores contextuais aceitos (ou seja, regiões) para cada situação (instancias de contexto).

Da mesma forma, o CQE também é desenvolvido com base na Teoria dos Espaços de Contexto [22] e segue os mesmos princípios.

Além disso, um conjunto de diferentes técnicas de raciocínio são implementadas neste componente, como extração de características, lógica de descrição, raciocínio baseado em regras e inferência probabilística.

## Implementação

Fizeram um protótipo do que seria, não um software completo, baseado em microsserviços escaláveis e tolerantes a falhas

Ideal para implantação em nuvem

> nosso projeto não necessáriamente precisa de implantação na nuvem

implementaram um IDE web

Implementaram um aplicativo do caso de uso de um estacionamento inteligente que usa o CoaaS

FIWARE [14]
CA4IoT [15]
CAMPUS [16]
CASF [17]

[10] A. Dey, G. Abowd, and D. Salber, “A Conceptual Framework and a Toolkit for Supporting the Rapid Prototyping of Context-Aware Applications,” Human-Computer Interact., vol. 16, no. 2, pp. 97–166, 2001.

[11] T. Gu, H. K. Pung, and D. Q. Zhang, “A service-oriented middleware for building context-aware services,” J. Netw. Comput.  Appl., vol. 28, no. 1, pp. 1–18, 2005.

[12] H. L. Chen, “COBRA : An Intelligent Broker Architecture for Pervasive Context-Aware Systems,” Interfaces (Providence)., vol. 54, no. November, p. 129, 2004.

[14] “FIWARE.”  [Online].Available <https://www.fiware.org/>. [Accessed: 05-Dec-2017].

[15] C. Perera, A. Zaslavsky, P. Christen, and D. Georgakopoulos, “CA4IOT: Context awareness for Internet of Things,” in Proceedings - 2012 IEEE Int. Conf. on Green Computing and Communications, GreenCom 2012, Conf. on Internet of Things, iThings 2012 and Conf.  on Cyber, Physical and Social Computing, CPSCom 2012, 2012, pp.775–782.

[16] E. J. Y. Wei and A. T. S. Chan, “CAMPUS: A middleware for automated context-aware adaptation decision making at run time,” Pervasive Mob. Comput., vol. 9, no. 1, pp. 35–56, 2013.

[17] J. Kang and S. Park, “Context-aware services framework based on semantic web services for automatic discovery and integration of context,” Int. J. Adv. Comput. Technol., vol. 5, no. 4, 2013.

Coisas para tirar do Backlog final ou deixar como coisas secundárias para se implementar:

- Camada de segurança na parte de comunicação
- CRE que serve para inferir situações (contexto de alto nível que é inferido de vários contextos de baixo nível) a partir de dados sensoriais brutos ou contexto primitivo de baixo nível existente
- query parser pode ser simplificado
