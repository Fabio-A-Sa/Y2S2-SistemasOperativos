# 2 - Introduction

## Tópicos

1. O Sistema Operativo
2. Estrutura de um computador
3. Funcionamento do computador
4. Estruturas de memória
5. Processamento
6. Proteção e Segurança
7. Estruturas de dados do Kernel
8. Ambientes de Computação

## 1 - O Sistema Operativo

### Definição

Programa que é um intermediário entre o hardware do computador e do utilizador. É responsável por executar os programas do utilizador, resolver os seus problemas mais facilmente e usar o hardware de uma forma mais eficiente. <br>
O único programa que roda o tempo todo é o `kernel`, e os outros ou são programas de sistema ou aplicações.

### Funções

Depende do ponto de vista. Por um lado, a maioria dos utilizadores preferem a facilidade de utilização e uma boa performence e não querem saber da utilização de recursos. Mas há casos em que os computadores pertencem a servidores (mais recursos necessários), há computadores portáteis onde a bateria é importante e há sistemas sem GUI, como de alguns automóveis. Cada sistema operativo é adaptado para a sua função. <br>
O OS é:
1. Um `alocador de recursos`: monitora todos os recursos de hardware e software e garante a minimização de conflitos para uma melhor performence;
2. Um `controlador de programas`: controla a execução de programas para prevenir erros e utilizações impróprias;
3. Um `manipulador de dados`: tanto com ficheiros, como diretórios ou memória;

## 2 - Estrutura do computador

Um computador pode ser dividido em quatro partes:

1. Hardware: recursos básicos, como CPU, memória e dispositivos I/O;
2. Operating System: controla e cordena a utilização do hardware entre várias aplicações do utilizador;
3. Aplicações e programas: define o meio em que o sistema é usado, como compiladores, browsers, DBs e jogos;
4. Utilizadores: pessoas, máquinas, outros computadores;

## 3 - Funcionamento do Computador

Quando ligamos, a primeira coisa que inicia é o `bootstrap program`. Este programa está normalmente no ROM, também conhecido como `firmware`, e inicializa todos os aspectos do sistema incluindo o kernel. <br>
A memória é ligada ao CPU e a todos os controladores (de disco, USB e graphics adapter). Todos estes dispositivos competem por ciclos de memória e de CPU. <br>
Cada controlador tem o seu `buffer` e o CPU move os dados da memória para os buffers de cada dispositivo, atendendo aos ciclos de relógio e aos `interrups` gerados quando o dispositivo acaba a tarefa. <br>
Um `vector de interrupção` contém todos os endereços das rotinas, que são geradas por excepções (derivadas do pedido do utilizador  ou por um erro). Assim, o sistema operativo é acionado por interrupção.
<br>

Para executar um programa este precisa de estar em memória, assim como parte (ou todos) os dados a manipular.

## 4 - Estruturas de memória

Nem todas as memórias têm de ser rápidas. Exemplos: `WORM` (write-once, read-many-times) e `RM` (read-write), que são acedidas somente por aplicações do sistema operativo. <br>
Outros exemplos mais comuns:

`Memória principal`: a única porção grande de memória que o CPU pode acessar diretamente. É de random access e tipicamente volátil. <br>
`Armazenamento secundário`: a extensão da memória principal, que é não volátil. <br>
`HD`: Hard Disk. Disco coberto por uma superfície magnética, com controlador, pistas (tracks) e setores. <br>
`SSD`: Solid-State Disk. Mais rápido que o HD, também não volátil. <br>

### Cache

Copia informação para um sistema temporário mais rápido para acesso do CPU. Se a informação está em cache, é mostrada diretamente, senão é transferida da memória principal para a cache e aí é mostrada. A manipulação da memória cache tem de atender a diversos critérios, como a repetição, o espaço temporal e de ocupação.

### DMA - Direct Memory Access

Um controlador que permite manter a utilização de dispositivos I/O sem necessitar da intervenção do CPU no processo (somente para iniciar e terminar a tarefa, usando interrupts - um por bloco em vez de um por byte).

### Hierarquia de serviços de armazenamento:

Por ordem crescente de tempo de acesso e de tamanho, por ordem decrescente de banda:

1. Registos
2. Cache
3. Memória principal
4. SSD
5. HD
6. Optical Disk
7. Magnetic Tapes

Voláteis (1, 2, 3) e não voláteis (4, 5, 6, 7).

## 5 - Processamento

Há sistemas com um ou mais processadores. Com mais processadores (cores/núcleos) aumenta a rapidez, confiabilidade e tolerância a erros. Existem dois tipos de processamento paralelo:
1. Processamento assimétrico - quando cada processador/core executa uma tarefa em específico;
2. Processamento simétrico - quando cada processador/core executa todas as tarefas;

Os sistemas de redes de computadores também podem adoptar esta técnica de multiprocessamento, usando uma SAN (Storage-Area Network) para manipular programas que foram já escritos para processamento paralelo e um DLM (Distributed Lock Manager) para evitar conflitos em operações concorrentes. Existem dois processos principais:
1. Clustering assimétrico - uma máquina em modo de espera ativa;
2. Clustering simétrico - tem várias máquinas em execução, monitorando-se mutuamente;

Cada vez mais os processadores permitem um dual-mode entre o `user mode` (mode bit = 1) e o `kernel mode` (mode bit = 0) para proteção do sistema, como por exemplo loops infinitos. <br>
O sistema operativo é responsável por criar, eliminar, suspender, sincronizar e comunicar com todos os processos.

## 6 - Proteção e Segurança

Mecanismos de controlo de acesso aos processos, dados ou recursos através do sistema operativo. Utilização de IDs únicos para cada utilizador, grupo, com permissões definidas entre ficheiros por questões de segurança.

## 7 - Estruturas de dados do Kernel

- [x] Lists
  - Simples
  - Dupla
  - Circular
- [x] Balanced Binary Seach Trees
  - Red Black Trees
- [x] Hash Functions
  - Hash Tables
  - Bitmap

## 8 - Ambientes de Computação

### 8.1 - Traditional

Máquinas de uso geral. Com a internet, portais, e computadores em rede é necessário existirem firewalls que protegem os computadores de ataques externos

### 8.2 - Mobile

Nos Tablets, smartphones, que têm algumas funções extra do que os tradicionais portáteis (exemplo: GPS, giroscópio e realidade aumentada). Apple iOS e Google Android.

### 8.3 - Distributed

Funcionam com Networks, comunicações entre diversos dispositivos através de protocolos (IP / TCP). O Network Operating System providencia uma ilusão de um simples sistema.

### 8.4 - Client Server

Os sistemas são agora servidores que respondem às exigências do utilizador. Providencia uma interface para o cliente, como por exemplo uma base de dados, e uma interface para retirar e colocar arquivos.

### 8.5 - Peer-to-Peer

Sistema distribuído em que não há distinção entre clientes e servidores. Registam o serviço centralmente através do protocolo discovery.

### 8.6 - Virtualization

Emulação quando o CPU age de forma diferente conforme o objectivo e Virtualização quando o OS está nativamente dentro de outro OS, ambos compilados (tal como acontece nas Virtual Machines, que usam um kernel para cada processo de sistema operativo).

### 8.7 - Cloud Computing

Existem clouds públicas (acessíveis via Internet e gratuitas), privadas (para uma empresa usar em específico) e híbridas.

### 8.8 - Real Time Embedded Systems

Sistemas embarcados, alguns executam tarefas sem terem mesmo um sistema operativo. Contém restrições e tempo bem delimitado para cada tarefa.