# Arquitetura Contexto como um serviço

**Objetivo**: Distribuiçao de contexto como um serviço

**Caso de uso**: Casa inteligente

## Requisitos mínimos

- Deve ser **escalável**

- ~segurança ignorada a priori~

- Deve possuir custo computacional e de memória aceitável (caso de uso isolado)

- Deve ser fácil de usar tanto por consumidores, quando por provedores de contexto.

- ~Manutenabilidade? (desejável, mas para um protótipo não)~

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

> seria um sub conceito de DaaS (Data as a Service)?

> fazer tudo dentro do NS3 ou fazer uma aplicação fora que se comunica com ele?
> Fora do ns3: liberdade pra escolher linguagem (python facilitaria, mas pioraria desempenho)
> dentro do ns3: tem q fazer em C++

A priori vamos pensar em fazer tudo dentro do NS3

> <https://github.com/drogonframework/drogon> -> C++17/20 based HTTP application framework

Protocolo IoT: MQTT (para provedores de contexto), HTTP/REST (para consumidores de contexto).

Será necessário implementar normalização dos dados por agora? (exemplo: temp, temperature, TEMP_C).

## Escalabilidade

Manter no local uma quantidade limitada do histórico de contexto, o restante pode ser enviado para nuvem (ex: 100 valores)

## Descoberta de sensores

Serviço chega, manda em broadcast que chegou objetos com a aplicação requisitam conexão?