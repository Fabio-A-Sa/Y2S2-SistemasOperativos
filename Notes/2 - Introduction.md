# 2 - Introduction

## Tópicos

1. O Sistema Operativo
2. Estrutura de um computador
3. Funcionamento do computador
4. Estruturas de memória

## 1 - O Sistema Operativo

### Definição

Programa que é um intermediário entre o hardware do computador e do utilizador. É responsável por executar os programas do utilizador, resolver os seus problemas mais facilmente e usar o hardware de uma forma mais eficiente. <br>
O único programa que roda o tempo todo é o `kernel`, e os outros ou são programas de sistema ou aplicações.

### Funções

Depende do ponto de vista. Por um lado, a maioria dos utilizadores preferem a facilidade de utilização e uma boa performence e não querem saber da utilização de recursos. Mas há casos em que os computadores pertencem a servidores (mais recursos necessários), há computadores portáteis onde a bateria é importante e há sistemas sem GUI, como de alguns automóveis. Cada sistema operativo é adaptado para a sua função. <br>
O OS é:
1. Um `alocador de recursos`: monitora todos os recursos de hardware e software e garante a minimização de conflitos para uma melhor performence;
2. Um `controlador de programas`: controla a execução de programas para prevenir erros e utilizações impróprias;

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

## 4 - Estruturas de memória

`Memória principal`: a única porção grande de memória que o CPU pode acessar diretamente. É de random access e tipicamente volátil. <br>
`Armazenamento secundário`: a extensão da memória principal, que é não volátil. <br>
`HD`: Hard Disk. Disco coberto por uma superfície magnética, com controlador, pistas (tracks) e setores. <br>
`SSD`: Solid-State Disk. Mais rápido que o HD, também não volátil. <br>

### Memória cache

Copia informação para um sistema mais rápido para o CPU.

### Hierarquia de serviços de armazenamento:

1. Registos
2. Cache
3. Memória principal
4. SSD
5. HD
6. Optical Disk
7. Magnetic Tapes