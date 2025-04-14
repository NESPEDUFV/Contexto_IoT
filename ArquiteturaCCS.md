# Arquitetura Contexto como um serviço

**Objetivo**: Distribuiçao de contexto como um serviço

**Caso de uso**: Casa inteligente

## Table of contents

- [Arquitetura Contexto como um serviço](#arquitetura-contexto-como-um-serviço)
  - [Table of contents](#table-of-contents)
  - [Requisitos mínimos](#requisitos-mínimos)
  - [Arquitetura física do sistema](#arquitetura-física-do-sistema)
  - [Escalabilidade](#escalabilidade)
  - [Descoberta de sensores](#descoberta-de-sensores)
  - [Atualização dos contextos](#atualização-dos-contextos)
  - [Distribuição de contexto](#distribuição-de-contexto)


## Requisitos mínimos

- Deve ser **escalável**

- ~~segurança ignorada a priori~~

- Deve possuir custo computacional e de memória aceitável (caso de uso isolado)

- Deve ser fácil de usar tanto por consumidores, quando por provedores de contexto.

- ~~Manutenabilidade? (desejável, mas para um protótipo não)~~

- Usará hardware dedicado a priori, para fornecer mais desempenho do que escalabilidade

O serviço deve conseguir fazer:

- aquisição de dados de objetos

- armazenamento de contexto

- pesquisa e descoberta de contexto (?)

- difusão e distribuição de contexto.

## Arquitetura física do sistema

- **Cliente**: provedores e consumidores dos dados (uma entidade podendo ser ambos)
  - provedores enviam contexto para o servidor.
  - consumidores contatam o servidor para obter contexto de provedores.

- **Servidor de aplicação**: núcleo de processamento, gerencia a troca de informações e os dados

- Servidor de dados? (como mapear? usar rdf? usar tabelas normais?)

    usando RDF da pra usar fuseki-server. Pra se comunicar com ele podemos usar a API RESTful dele usando libcurl (#include <curl/curl.h>) em C++

> seria um sub conceito de DaaS (Data as a Service)? (bom para usar de referencia no artigo)

.

> fazer tudo dentro do NS3 ou fazer uma aplicação fora que se comunica com ele?
> Fora do ns3: liberdade pra escolher linguagem (ex: python facilitaria, mas pioraria desempenho)
> dentro do ns3: tem q fazer em C++

A priori vamos pensar em fazer tudo dentro do NS3

> <https://github.com/drogonframework/drogon> -> C++17/20 based HTTP application framework

Protocolo IoT: MQTT (para provedores de contexto enviar os dados), HTTP/REST (para consumidores de contexto receber os dados e fazer as requisições).

Será necessário implementar normalização dos dados por agora? (exemplo: temp, temperature, TEMP_C).

## Escalabilidade

Manter no local uma quantidade limitada do histórico de contexto, o restante pode ser enviado para uma "nuvem" (ex: 100 valores históricos de buffer, o restante em nuvem)

## Descoberta de sensores

- Serviço chega, manda em broadcast que chegou, objetos com a aplicação requisitam conexão? (simplificado d+)

Os objetos já conhecem o serviço?

~~Wireshark/tcpdump pra investigar a rede?~~

Tem como usar os hubs de iot existentes (SmartThings, Tuya Smart, Alexa), mas precisa dos tokens de acesso e a comunicação com eles (hubs) seriam via HTTP/REST, ACHO que a comunicação deles com os objetos seriam MQTT. A vantagem é que facilitaria essa questão da descoberta e comunicação com os mesmos. (parte da segurança e comunicação fica por conta do hub).

Exemplo: <https://api.smartthings.com/v1/locations/{locationId}>

gera:

```JSON
"locationId": "6b3d1909-1e1c-43ec-adc2-5f941de4fbf9",
"name": "Home",
"countryCode": "USA",
"latitude": 45.00708112,
"longitude": -93.11223629,
"regionRadius": 150,
"temperatureScale": "F",
"timeZoneId": "America/Chicago",
"locale": "en_US",
"parent":  {
  "type": "LOCATIONGROUP",
  "id": "6ecb6c06-7319-49b1-8ebd-f97660efdd06"
},
"created": 1547920800,
"lastModified": 1548007200
```

Daria pra usar esses hubs e na "contratação" do serviço pedir esses tokens. Meio q centralizaria os hubs e gerenciaria as informações dos objetos, os hubs ainda continuariam sendo pra controle. **Abstrair?**

- Os objetos se conectam a aplicativos (hubs) ou conectam diretamente a uma aplicação (arduíno programado pra um endpoint)

- No caso de se conectar a aplicativos, o proprio <nomeDoServiço> pode tentar se conectar dado o token (o sistema deve ser aberto nessa parte para se adaptar aos novos hubs existentes) (pode ser simplificado)
- No caso de conexão direta o objeto tenta se conectar ao serviço com MQTT diretamente.

## Atualização dos contextos

Os hubs/objetos ativam um gatilho de envio da atualização do contexto e enviam uma mensagem HTTP/MQTT conforme a disponibilidade (priorizando MQTT).

Poderia completar as informações usando o OD4CoT na primeira vez que o objeto chega ao serviço.

## Distribuição de contexto

Aqui teria que ter uma medida de segurança forte, no mínimo um token. É possível pra deixar simplificado ou nem usar nessa solução ingênua.

o serviço recebe requisições de informação e devolve o que foi solicitado.

ex:
Consumidor manda uma solicitação HTTP com um JSON formatado do que quer, o servidor de aplicação transforma isso em uma query no estilo RDF, realiza a query no DB, formata o resultado para um JSON e devolve pro Consumidor com HTTP ou MQTT.
