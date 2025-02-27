# Tese Hassani

## CONTEX-AS-A-SERVICE: OVERVIEW AND DEFINITIONS

CoaaS é uma plataforma de gerenciamento de contexto que foi projetada para facilitar o desenvolvimento de aplicativos de IoT sensíveis ao contexto, fornecendo um mecanismo genérico, porém personalizável, para consultar e publicar contexto.

O CoaaS permite que os aplicativos forneçam e consumam contexto sobre suas entidades de interesse de forma integrada, sem exigir integração manual de silos de IoT.

Context consumer
qualquer sistema ou entidade que precisa consultar contexto

Context provider
qualuqer entidade ou sistema que gera/libera contexto
da pra diferenciar algumas classes aqui, como: provedores de contexto bruto (sensores), provedores de contexto refinado, provedores de contexto misto

APIs podem ser provedores de contexto

Como resultado, com base no tipo de CPs (context providers), cada provedor de contexto pode ter um ou mais serviços, que produzem contexto sobre uma entidade. Nós nos referimos a esses serviços como Serviços de Contexto.

Um Context Service fornece informações contextuais sobre uma entidade específica. O Context Service pode ser representado como uma tripla:〈E, CA, P〉

- onde E denota a entidade relacionada,
- CA é um conjunto de atributos de contexto fornecidos e
- Predicates (denotados por P) formam uma expressão lógica composta definida sobre CA.

O CoaaS pode interagir com CPs de duas maneiras: buscando contexto sob demanda ou recebendo fluxos de contexto/dados.

No primeiro caso, os CPs devem ter registrado a descrição de seus serviços primeiro enviando uma solicitação de registro de serviço de contexto (CSR). Então, o CoaaS pode recuperar dados sobre entidades de IoT enviando solicitações aos provedores correspondentes sob demanda.

No segundo caso as atualizações de contexto contêm atualizações dos estados das entidades e são processadas pelo CoaaS para monitorar situações

On the other hand, context consumers can retrieve context information from the
middleware by issuing context queries (CQ).

o CoaaS se preocupa em inferir contextos high-level

CooaS trabalha dividindo consultas de contexto em diversas requisições de contexto para entidades diferentes

## COAAS PLATFORM BLUEPRINT ARCHITECTURE

CMPs have six major functionalities, namely

1. sensor data acquisition
2. context storage
3. context lookup and discovery
4. privacy, security and access control
5. context processing and reasoning
6. context diffusion and distribution.

As this figure shows, the CoaaS platform has five main components with their responsabilities:

1. [Communication and Security Manager](Context-as-a-Service%20Platform.md#security-and-communication-manager)
   1. (iv) Privacy, security and access control
2. [Context Query Engine (CQE)](Context-as-a-Service%20Platform.md#context-query-engine-cqe)
   1. (i) Sensor data acquisition (para requests discretas, contexto sob demanda)
   2. (iii) Context service registration and discovery
   3. (vi) Context querying (Context diffusion and distribution)
   4. ver cap 4 sec 4.1
3. Situation Monitoring Engine (SME)
   1. (i) Sensor data acquisition (para stream de dados, request contínua context updates)
   2. (v) Context processing and reasoning
   3. infere situações
   4. detecta e provê notificação das mudanças detectadas
   5. monitora real-time context
   6. ver cap 4 sec 4.5
4. [Context Storage Management System (CSMS)](Context-as-a-Service%20Platform.md#context-storage-management-system-csms)
   1. (i) Sensor data acquisition ?
   2. (ii) Context Storage
   3. (iii) Context service registration and discovery
   4. detalhado em Medvedev, Indrawan-Santiago, et al., 2017
5. and [Context Reasoning Engine (CRE)](Context-as-a-Service%20Platform.md#context-reasoning-engine-cre).
   1. (v) Context processing and reasoning

Algo interessante do CSMS
Em segundo lugar, ele armazena em cache informações contextuais para garantir um tempo de resposta de consulta razoável e lida com problemas como latências de rede e potencial indisponibilidade de fontes de contexto.

## CONTEXT DEFINITION AND QUERY LANGUAGE (CDQL)

### CONTEXT QUERY LANGUAGE (CQL)

Literalmente um SQL de contexto (a forma que consultas são feitas é baseado em sujeitos, predicados e objetos)

é possível fazer consultas periódicas com uma clausula específica (subscription e every)

