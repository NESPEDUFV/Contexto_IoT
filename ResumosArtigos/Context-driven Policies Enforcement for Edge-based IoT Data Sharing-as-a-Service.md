# Context-driven Policies Enforcement for Edge-based IoT Data Sharing-as-a-Service

apresentou uma nova estrutura dinâmica de aplicação de políticas baseada em contexto para dar suporte ao compartilhamento de dados de IoT (on-Edge) com base em contratos dinâmicos. (Web 3?)

Apresentou especificações de política de controle de acesso específicas do locatário e o mecanismo de execução no nível Edge. As políticas e sua execução são baseadas em contratos de dados entre o provedor do Hub e os locatários, inicializados e armazenados centralmente na Nuvem;

Oferece suporte ao compartilhamento de dados de IoT orientado por contexto por meio de políticas de controle de acesso de maneiras flexíveis, de acordo com os contextos de IoT em nível de aplicativo, que são atualizados dinamicamente por serviços de detecção de contexto, ou seja, usando IA/ML no Edge;

A estrutura baseada no Edge pode impor políticas de controle de acesso específicas do locatário aos dados que estão sendo compartilhados dinamicamente de acordo com as mudanças de contexto da IoT no Edge e mudanças de contrato na Nuvem.

O modelo de serviço se concentra principalmente em como o Hub pode controlar o compartilhamento de dados como um serviço para diferentes consumidores de dados (chamados locatários) com base em contextos dinâmicos.

Como há muitos Hubs conectados ao sistema de Nuvem, precisamos de um mecanismo escalável para sincronizar contextos de dados e políticas de aplicação entre a Nuvem e o Edge.

Como demonstração, usamos o framework Apache Kafka [15] para implementar o Sistema de Mensagens para sincronização. Notamos que o framework Kafka pode não ser suficiente em Edges de larga escala; no entanto, assumimos que o Hub com detecção de contexto é uma parte da rede onde um consumidor/produtor Kafka será executado.

Rego is a JSON based policy language