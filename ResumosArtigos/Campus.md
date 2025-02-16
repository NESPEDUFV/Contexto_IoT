# CAMPUS: A middleware for automated context-aware adaptation decision making at run time

Atinge o objetivo com a confluência de três tecnologias principais: adaptação composicional, ontologia e lógica descritiva/raciocínio lógico de primeira ordem

Em particular, o CAMPUS propõe um novo modelo de programação baseado na adaptação composicional para construir aplicações sensíveis ao contexto e facilitar decisões de adaptação

O CAMPUS também formula um modelo abrangente baseado em ontologia para capturar os conceitos e relacionamentos importantes de entidades no modelo de programação, que são necessários para decisões de adaptação automatizadas e sensíveis ao contexto.

O principal objetivo do middleware CAMPUS é automatizar decisões de adaptação sensíveis ao contexto em tempo de execução.

Logically, CAMPUS is divided into a programming layer, a knowledge layer, and a decision layer

## Arquitetura do CAMPUS

### Camada de programação

A camada de programação do CAMPUS é responsável por construir e reconfigurar aplicaçoes sensíveis ao contexto de acordo com as instruções da camada de decisão. Isso é alcançado pelo modelo de programação ATM (abreviação de Adaptable Task Model) que é baseado na adaptação composicional e na abordagem de separação de preocupações.

Em geral, as abordagens para realizar a adaptação sensível ao contexto podem ser classificadas em adaptação transformacional e adaptação composicional [18,19].

Na adaptação transformacional, os aplicativos modificam diretamente as especificações e/ou implementações relacionadas para responder a contextos em mudança.

A adaptação composicional, em contraste, responde aos contextos por meio da adição, remoção, substituição ou mesmo alteração das interconexões das partes algorítmicas ou estruturais dos aplicativos.

Por exemplo, para adaptar o conteúdo da web a ser renderizado em um dispositivo móvel com restrição de exibição, é necessário transcodificar a imagem, com o objetivo final de reduzir a quantidade de dados a serem transferidos.

Na adaptação de transformação, os conteúdos são transcodificados diretamente. Os códigos de transcodificação geralmente são profundamente incorporados ao aplicativo.

Em contraste, na adaptação composicional, o objetivo é descobrir e selecionar o componente de transcodificação mais adequado que pode ser composto no fluxo de dados processados.

### Camada de conehcimento

Na ciência da computação, ontologia é uma descrição dos conceitos e relacionamentos que podem existir para um agente ou uma comunidade de agentes e geralmente é escrita como um conjunto de definições de vocabulário formal [26].

> here are several reasons to develop ontologies as the underlying description scheme for CAMPUS.

1. ontologias formais são uma solução comprovada para gerenciar a heterogeneidade inerente presente no conhecimento de diferentes fontes [27]. Ontologias podem ser usadas para representar explicitamente o significado e a semântica de entidades contextuais e computacionais e, assim, permitir que entidades heterogêneas tenham um conjunto comum de conceitos enquanto interagem umas com as outras.
2. ontologias simplificarão muito as tarefas de raciocínio automatizado baseado em semântica e tomada de decisão. Ontologias incluem definições interpretáveis ​​por máquina de conceitos no domínio e os relacionamentos entre eles. Elas são expressas em uma linguagem formal baseada em lógica, para que distinções consistentes e significativas possam ser feitas entre as classes, propriedades e relações. É importante ressaltar que um número considerável de mecanismos de raciocínio existentes pode ser empregado para executar raciocínio automatizado e tomada de decisão nas ontologias CAMPUS.
3. Finalmente, muitos editores gráficos de ontologia, como o Protégé OWL,2 estão disponíveis para facilitar o desenvolvimento de ontologias. Ontologias de contexto de larga escala também podem ser compostas sem a necessidade de começar do zero, reutilizando as ontologias bem definidas de diferentes domínios.

descrições de ontologias usadas:

1. Ontologias de contexto modelam várias entidades de contexto para compartilhar informações contextuais em um ambiente dinâmico.
2. Ontologias de tasklet descrevem as propriedades de tasklets individuais e seus requisitos para condições contextuais.
3. Ontologias de serviço descrevem as propriedades de serviços sensíveis ao contexto e seus requisitos para tasklets.

(tasklet==tarefa)

### Camada de decisão

O CAMPUS alcança a adaptação sensível ao contexto adaptando as partes tasklet das tarefas. A camada de decisão usa um modelo de decisão normativa multiestágio para escolher as melhores alternativas de tasklet para tarefas dadas.
O modelo multiestágio incorpora múltiplos estágios qualitativamente separáveis, ou seja, múltiplas fases baseadas em heurística seguidas por uma fase de escolha. Em um modelo multiestágio, o tomador de decisão primeiro usa estratégias de decisão menos exigentes cognitivamente para eliminar alternativas inaceitáveis, reduzindo assim o número de alternativas restantes na decisão de escolha.
Na fase de escolha, o tomador de decisão pode usar estratégias de decisão mais exigentes cognitivamente para escolher entre as alternativas restantes. Todo o procedimento de tomada de decisão do CAMPUS é dividido em três fases: pré-processamento, triagem e escolha.

1. Na fase de pré-processamento, várias tarefas de pré-processamento são realizadas para garantir que as ontologias sejam semanticamente consistentes e para preparar informações refinadas para as fases seguintes. Por exemplo, tasklets qualificados são registrados como alternativas para cada tarefa.
2. No segundo estágio de triagem, alternativas de tasklet que foram registradas na primeira fase são triadas se não forem satisfeitas pelas informações contextuais atualizadas.
3. Se mais de uma alternativa de tasklet aceitável sobreviver à fase de triagem, a fase de escolha seleciona a melhor alternativa entre as sobreviventes, usando a função de utilidade de aptidão que será detalhada na Seção 6.

## The CAMPUS ontologies

As ontologias CAMPUS são um conjunto de ontologias que capturam conceitos e relacionamentos em vários domínios de interesse.

1. Ontologias de contexto modelam várias entidades de contexto para compartilhar informações contextuais em um ambiente dinâmico.
2. Ontologias de tasklet descrevem as propriedades de tasklets individuais e seus requisitos para condições contextuais. Exemplos incluem as funcionalidades fornecidas por um tasklet, os tipos de dados que um tasklet pode processar e produzir e os recursos de computação exigidos por um tasklet.
3. Ontologias de serviço descrevem as propriedades de serviços com reconhecimento de contexto e seus requisitos para tasklets. Alguns exemplos de requisitos incluem a composição de serviços, a funcionalidade desejada de tarefas e seus tipos de dados de entrada e saída exigidos.
