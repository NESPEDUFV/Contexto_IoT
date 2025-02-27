# SMART OBJECTS ONTOLOGY DATASET

ontological dataset of smart objects
OnData: Smart Objects
OnData SO (leia com mineires)

## Tabel of contents

- [SMART OBJECTS ONTOLOGY DATASET](#smart-objects-ontology-dataset)
  - [Tabel of contents](#tabel-of-contents)
  - [A estrada até aqui](#a-estrada-até-aqui)
  - [Objetivo](#objetivo)
  - [Metodologia](#metodologia)
  - [Padronizações](#padronizações)

## A estrada até aqui

Até agora então foi obtido uma uma **lista de areas de aplicações** de IoT, com base nelas foi obtido uma **lista de aplicações** nessas áreas e com base nessas aplicações foi pensado uma **lista de objetos inteligentes** que fazem parte delas e a partir disso foi pesquisado uma **lista de contextos** que esses objetos tem e possíveis valores que podem assumir (**instancias reais de objetos**)

## Objetivo

Agora vamos para uma parte mais filosófica da pesquisa, que é transformar todas essas informações, todo esse conhecimento de forma que o computador entenda e consiga processar a fim de ser criado uma base de dados completa coerente e concisa (mas trazendo toda a informação evitando perdas).

Para isso ficamos entre representar esse conhecimento de diferentes formas:

- CSV
- JSON
- Ontologia

Em todos eles nós iriamos conseguir trazer as informações de forma que o computador entenda, mas a forma que menos perde esse conhecimento é usando o conceito de **ontologia**, por mais complexo que possa ser, posteriormente os usuários do dataset poderão remontar ele e decidir quais são as informações relevantes para otimizar na aplicação que desejar, por exemplo fazer uma transformação para um JSON da relação area de aplicação - objeto.

Nossa escolha foi baseada [academicamente](../ResumosArtigos/Campus.md#camada-de-conehcimento) e como um consenso de trabalhar com isso no nosso grupo de projeto, trazendo mais organização e certo processamento nesse momento antes dos dados serem de fato usados.

## Metodologia

Como temos uma quantidade bem grande de informações, vamos aplicar uma abordagem top-down a priori para dar a estrutura do dataset

Será dividido em 5 passos

1. Definições das areas de aplicações (a relação objeto-area se encontra [nesse link](https://docs.google.com/spreadsheets/d/19MWqELJt4dg3BPA6r8yR_rO9394NSPdZCil8MgJf7wI/edit?gid=0#gid=0))
2. Definições de tipos (cluster) de objetos
   1. (talvez seria interessante trazer as aplicações)
3. Definições de objetos generalizados
4. Definições de instancias de objetos
5. Definições dos contextos dos objetos

Os tópicos 1 e 2 podem estar em um mesmo arquivo ([appAreas.ttl](/dataset/SOODS/appAreas.ttl)), eles fazem sentido estar juntos

Os tópicos 3 e 4 também podem ficar juntos em um arquivo ([objects.ttl](/dataset/SOODS/objects.ttl))

O tópico 5 é interessante deixar separado ([contexts.ttl](/dataset/SOODS/contexts.ttl))

(Isso não quer dizer que não vão ser usados nos arquivos, apenas definidos em arquivos diferentes)

Caso seja necessário remodelar ou adicionar novas informações em cada um dos passos em qualquer tempo de implementação, o mesmo deverá ser pensado e feito o quanto antes para não virar uma bola de neve, é agora mesmo que podemos desenhar e apagar o desenho até ficar bonito, depois não vai ter como.

## Padronizações

- Será usado
  - camelCase na escrita de predicados
  - TitleCase em sujeitos e objetos
  - sempre no singular
- Dataset em Ingles (cuidado ao usar o tradutor)
- Medidas no sistema internacional
- Usar o que vimos do minicurso
- Usar bem as identações

Qualquer duvida ou notou que algo precisa ser padronizado: não exite em perguntar ou pedir uma reunião

Viu que algo está desorganizado, aponte isso.

Lembrando: 2 cabeças pensam mais que uma, 3 pensam mais que duas e 4 pensam mais que 3, toda ideia é valida.
