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


FIWARE [14]
CA4IoT [15] 
CAMPUS [16]
CASF [17]

[10] A. Dey, G. Abowd, and D. Salber, “A Conceptual Framework and a Toolkit for Supporting the Rapid Prototyping of Context-Aware Applications,” Human-Computer Interact., vol. 16, no. 2, pp. 97–166, 2001.

[11] T. Gu, H. K. Pung, and D. Q. Zhang, “A service-oriented middleware for building context-aware services,” J. Netw. Comput.  Appl., vol. 28, no. 1, pp. 1–18, 2005.

[12] H. L. Chen, “COBRA : An Intelligent Broker Architecture for Pervasive Context-Aware Systems,” Interfaces (Providence)., vol. 54, no. November, p. 129, 2004.



[14] “FIWARE.”  [Online].Available https://www.fiware.org/. [Accessed: 05-Dec-2017].

[15] C. Perera, A. Zaslavsky, P. Christen, and D. Georgakopoulos, “CA4IOT: Context awareness for Internet of Things,” in Proceedings - 2012 IEEE Int. Conf. on Green Computing and Communications, GreenCom 2012, Conf. on Internet of Things, iThings 2012 and Conf.  on Cyber, Physical and Social Computing, CPSCom 2012, 2012, pp.775–782.

[16] E. J. Y. Wei and A. T. S. Chan, “CAMPUS: A middleware for automated context-aware adaptation decision making at run time,” Pervasive Mob. Comput., vol. 9, no. 1, pp. 35–56, 2013.

[17] J. Kang and S. Park, “Context-aware services framework based on semantic web services for automatic discovery and integration of context,” Int. J. Adv. Comput. Technol., vol. 5, no. 4, 2013.