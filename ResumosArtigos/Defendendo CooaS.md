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

FIWARE [14]

“FIWARE.” [Online]. Available: https://www.fiware.org/. [Accessed: 05-Dec-2017].

"Uma estrutura com curadoria de componentes de *plataforma de código aberto* para acelerar o desenvolvimento de soluções inteligentes"

Codigo aberto mas aparentemente inovações podem ser monetizadas, mas isso não quer dizer que tudo é pago, os membros que contribuem possui livre acesso

possui um banco de dados imenso de várias coisas, inclusive com modelos do banco [smart-data-models](https://www.fiware.org/smart-data-models/), exemplo de um dado de qualidade da agua em JSON [exemplo](https://smart-data-models.github.io/dataModel.WaterQuality/WaterQualityObserved/examples/example.json)

aparentemente ele não é um meio de distribuição de contexto geral e sim um facilitador de conexão do provedor de contexto com o consumidor de contexto sem ser algo intermediário, estando no provedor e no consumidor (foi o q entendi, não tinha mt coisa falando dele resumido)

Existem vários componentes nesse fiware, principalmente de "Context broker" e data conector.

talvez seria interessante conribuir nossa ontologia lá com eles se tiver como, eles tem tudo a ver com IoT e ciencia do contexto

ponto negativo: não mostrou uma arquitetura replicável e nem como usar de forma simples, seria necessário ir em tutoriais da ferramenta e fazer uma busca secundária para tal

CA4IoT [15]

C. Perera, A. Zaslavsky, P. Christen, and D. Georgakopoulos, “CA4IOT: Context awareness for Internet of Things,” in Proceedings - 2012 IEEE Int. Conf. on Green Computing and Communications, GreenCom 2012, Conf. on Internet of Things, iThings 2012 and Conf. on Cyber, Physical and Social Computing, CPSCom 2012, 2012, pp. 775–782.

CAMPUS [16]

E. J. Y. Wei and A. T. S. Chan, “CAMPUS: A middleware for automated context-aware adaptation decision making at run time,” Pervasive Mob. Comput., vol. 9, no. 1, pp. 35–56, 2013.

CASF [17]

J. Kang and S. Park, “Context-aware services framework based on semantic web services for automatic discovery and integration of context,” Int. J. Adv. Comput. Technol., vol. 5, no. 4, 2013.

Não consegui ter acesso
