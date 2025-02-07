# Defendendo CooaS

O artigo nos trás os seguintes trabalhos relacionados:

Os trabalhos mais antigos irei confiar nos autores do CooaS, ler eles irá tomar um tempo bom.

Hassani et al. dividiram os trabalhos dos mais antigos aos mais recentes cada um com seus problemas se aplicados hoje.

1. > Sistema mais antigo que abordava algo relacionado ao tema:

    The Active Badge System [9]
    R. Want, A. Hopper, and V. Falcao, “The Active Badge Location
    System,” vol. 10, no. 1, pp. 91–102, 1992.

    O problema desse é q o foco era usar apenas dados de localização.
    Queremos contextos próprios, mas diversos.

2. > Sistema que tentaram alcançar um nível maior de generalização e suporte a mais tipos de contextos.

    Toolkit [10]

    A. Dey, G. Abowd, and D. Salber, “A Conceptual Framework and a
    Toolkit for Supporting the Rapid Prototyping of Context-Aware
    Applications,” Human-Computer Interact., vol. 16, no. 2, pp. 97–166,
    2001.

    SOCAM [11]

    T. Gu, H. K. Pung, and D. Q. Zhang, “A service-oriented middleware
    for building context-aware services,” J. Netw. Comput. Appl., vol. 28,
    no. 1, pp. 1–18, 2005.

    Cobra [12]

    H. L. Chen, “COBRA : An Intelligent Broker Architecture for
    Pervasive Context-Aware Systems,” Interfaces (Providence)., vol. 54,
    no. November, p. 129, 2004.

    No entando esses sistemas sofrem de uma série de restrições comuns que os tornam ineficientes para serem usados ​​em sistemas com reconhecimento de contexto do mundo real. Essas restrições incluíam **falta de tolerância a falhas** e **escalabilidade**, **suporte de interoperabilidade ruim** e **raciocínio ingênuo**.

3. > Sistemas que abordaram e tratatam  essas limitações (middlewares)

    Hassani et al. diz que os sistemas a seguir "Embora tenham resolvido com sucesso algumas das limitações mencionadas, eles não conseguiram evoluir para um nível padrão da indústria."

    "Acreditamos que a principal deficiência desses sistemas de middleware é a falta de uma linguagem de consulta de contexto (CQL) abrangente e flexível que permita que aplicativos com reconhecimento de contexto reutilizem dados contextuais existentes com base em seus requisitos específicos [7]. "

    Os autores dão foco na falta do uso de CQLs, visto que são pouco conhecidas e muito importantes.

    Vamo ve se isso é vdd

    > FIWARE [14]

    “FIWARE.” [Online]. Available: <https://www.fiware.org/>. [Accessed: 05-Dec-2017].

    "Uma estrutura com curadoria de componentes de *plataforma de código aberto* para acelerar o desenvolvimento de soluções inteligentes"

    Codigo aberto mas aparentemente inovações podem ser monetizadas, mas isso não quer dizer que tudo é pago, os membros que contribuem possui livre acesso

    possui um banco de dados imenso de várias coisas, inclusive com modelos do banco [smart-data-models](https://www.fiware.org/smart-data-models/), exemplo de um dado de qualidade da agua em JSON [exemplo](https://smart-data-models.github.io/dataModel.WaterQuality/WaterQualityObserved/examples/example.json)

    aparentemente ele não é um meio de distribuição de contexto geral e sim um facilitador de conexão do provedor de contexto com o consumidor de contexto sem ser algo intermediário, estando no provedor e no consumidor (foi o q entendi, não tinha mt coisa falando dele resumido)

    Existem vários componentes nesse fiware, principalmente de "Context broker" e data conector.

    talvez seria interessante conribuir nossa ontologia lá com eles se tiver como, eles tem tudo a ver com IoT e ciencia do contexto

    pontos negativos:
    - não mostrou uma arquitetura replicável e nem como usar de forma simples,
      - seria necessário ir em tutoriais da ferramenta e fazer uma busca secundária para tal
    - usa JSON para abordar contextos (paia)

    > CA4IoT [15]

    C. Perera, A. Zaslavsky, P. Christen, and D. Georgakopoulos, “CA4IOT: Context awareness for Internet of Things,” in Proceedings - 2012 IEEE Int. Conf. on Green Computing and Communications, GreenCom 2012, Conf. on Internet of Things, iThings 2012 and Conf. on Cyber, Physical and Social Computing, CPSCom 2012, 2012, pp. 775–782.

    "Neste artigo, propomos a arquitetura Context Awareness for Internet of Things (CA4IOT) para ajudar os usuários a automatizar a tarefa de selecionar os sensores de acordo com os problemas/tarefas em questão. Focamos na configuração automatizada de mecanismos de filtragem, fusão e raciocínio que podem ser aplicados aos fluxos de dados de sensores coletados usando sensores selecionados."

    basicamente ele escolhe o melhor provedor de contexto para o consumidor? isso não é distribuir contexto, é facilitar a ligação entre eles e gerar inferencia de contexto usando um intermediário.

    "However, sensor networks are the backbone of the IoT."

    "Nosso objetivo é projetar uma solução para ajudar os usuários a automatizar a tarefa de seleção de sensores de acordo com os problemas/tarefas em questão."

    no artigo eles respondem a seguinte pergunta: "Como reduzir a complexidade da seleção de sensores apropriados entendendo os requisitos/problemas do usuário?"

    para essa construção eles focaram em abordar os seguintes requisitos:

    1. Capacidade de conectar sensores ao middleware de IoT facilmente
    2. Capacidade de entender e manter informações de contexto (o que, quando, quem, como, por que) sobre sensores:
    3. Capacidade de entender o requisito/solicitação/problema do usuário
    4. Capacidade de preencher a lacuna entre os requisitos de usuário de alto nível e os recursos de sensores de baixo nível
    5. Capacidade de extrair informações de contexto de alto nível usando dados brutos de sensores de baixo nível
    6. Capacidade de gerenciar usuários

    O CA4IOT não está focado em fornecer uma solução de software completa que atenda a todos os requisitos necessários no paradigma da IoT.

    Recomendamos não empregar o CA4IOT como um middleware independente, mas combinar a arquitetura, os modelos e as técnicas em soluções de middleware de IoT existentes que pretendem atender às demandas do paradigma de IoT.

   ## Arquitetura CA4IOT

    A arquiterura do CA4IOT é composta por 2 camadas externas que envolvem 4 camadas internas, elas são descritas a seguir:

    1. Camada do Usuário (UL): Esta é a camada que representa os usuários e não é uma camada central no CA4IOT. Os usuários podem ser usuários humanos, aplicativos ou serviços. O User Oriented Front End (UOFE) é parte desta camada e, portanto, não é um componente central na arquitetura do CA4IOT. [Externa]

    2. Camada de Disseminação de Dados, Semântica e Contexto (DSCDL): Esta camada é responsável por gerenciar usuários. Os componentes pertencentes a esta camada são data dispatcher, request manager e publish/subscribe. [Interna]

    3. Camada de Processamento e Raciocínio (CPRL): Esta é a camada mais importante no CA4IOT. Ela é responsável pelo processamento de dados, raciocínio, fusão, geração e armazenamento de conhecimento. Os componentes pertencentes a esta camada são registro de contexto, base de conhecimento de contexto, mecanismo de raciocínio, gerador de contexto e descobridor semântico, processamento de contexto primário, processador de contexto secundário, registro de provedor de contexto, operador de fusão de dados e repositório de fusão de dados. [Interna]

    4. Camada de Descoberta de Contexto e Semântica (CSDL): Esta camada é responsável por gerenciar contexto e descobridores semânticos, o que inclui gerar, configurar e armazenar. Os componentes pertencentes a esta camada são contexto e descobridores semânticos, gerador de contexto e descobridor semântico e repositório de contexto e descobridores semânticos. [Interna]

    5. Camada de Aquisição de Dados do Sensor (SDAL): Esta camada é responsável por adquirir dados. Esta camada aparece na maioria das soluções de middleware de gerenciamento de contexto, rede de sensores e IoT com diferentes terminologias, como wrappers, gateways, manipuladores, proxies, mediadores, etc. Esta camada se comunica com sensores de hardware e software e recupera dados do sensor no CA4IOT. Os componentes que pertencem a esta camada são wrappers de sensor, repositório de wrapper, gerador de wrapper, repositório local de definição de dispositivo de sensor (SDD) e repositório de nuvem SDD. [Interna]

    6. Camada de Detecção (SL): Esta camada representa todos os sensores de software e hardware (físicos e virtuais). Além disso, esta camada não faz parte da arquitetura CA4IOT principal. [Externa]

    "Some of the popular data formats are XML, CVS, and JSON."

    Ele não se importa em como os dados são enviados e os formatos dos dados na saída

    o Gerente de Solicitações recebe um arquivo XML contento a requisição, a valida e executa

    Sensor Wrapper(s)

    Parece muito o CooaS, mas sem a query e forma de armazenamento de contexto específica que o CooaS trás

    > CAMPUS [16]

    E. J. Y. Wei and A. T. S. Chan, “CAMPUS: A middleware for automated context-aware adaptation decision making at run time,” Pervasive Mob. Comput., vol. 9, no. 1, pp. 35–56, 2013.

    > CASF [17]

    J. Kang and S. Park, “Context-aware services framework based on semantic web services for automatic discovery and integration of context,” Int. J. Adv. Comput. Technol., vol. 5, no. 4, 2013.

    Não consegui ter acesso
