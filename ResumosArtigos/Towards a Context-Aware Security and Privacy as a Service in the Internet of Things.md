# Towards a Context-Aware Security and Privacy as a Service in the Internet of Things

No paper eles apresentam uma arquitetura de privacidade e segurança de sensibilidade ao contexto para IoT , foca BASTANTE em questões de segurança

O plano de segurança foi feito por meio da composição dinâmica de micro serviços baseados em contexto

## Knowledge Plane

### Aquisição de contexto ()

### Base de informações de contexto (CIB) (DB das informações baixo nível de contexto)

### Modelagem de Contexto
- the key-value model, (simplicity and flexibility)
- ontology-based model, 
- hybrid model, 
- etc. [12]

### Quality of Context (QoC)

Basicamente há uma computação de parametros para medir a qualidade do contexto (baixo nível) recebido. Então o resultado dessas medições vão ser interpretados para determinar a existencia de possíveis conflitos. Dependendo do tipo de conflito, será posto em práticas algumas políticas para prover um contexto de melhor qualidade (Por exemplo, a política de detecção de localização do usuário pode ser baseada no quão atual é a informação)

### Context Reasoning and Prediction (CRP)

é o processo de dedução de contexto de alto nível a partir de diversas informações de contexto de baixo nível.

Existem várias técnicas de raciocínio contextual, incluindo

- ontology-based, 
- machine learning, 
- fuzzy logic

"In our architecture, supervised learning technique will be used by the CRP module, because of its good accuracy."

### Context Base (CB) (DB das informações alto nível de contexto)

### Context Dispatcher (CD).

Distribui o contexto high level

### Risk Assessment Manager (RAM) and the User Preferences Management (UPM)

gerencia as preferencias de usuário sobre os contextos

pular a parte de segurança?