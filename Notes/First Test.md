# Preparação para o primeiro teste

## Tópicos:

1. Definição de sistema operativo, funções e serviços;
2. Partes e funcionamento do computador;
3. Hierarquia de Memória;
4. Tipos de processamentos. Multiprograming vs. Multitasking;
5. Ambientes de computação;
6. Estrutura;
7. System Calls e passagem de Parâmetros;
8. Processos;
9. Process Scheduling;
10. Criação e término de processos;
11. Interprocess Comunication;
12. Sockets and pipes;
13. Sincronização de processos;
14. ...

## 1 - Sistema Operativo

Intermediário entre o harware e o utilizador, para ser mais acessível e fácil de usar. O sistema operativo é acionado por interrupções e é:
1. Alocador de recursos - minimiza os conflitos entre hardware e software para uma melhor performence;
2. Controlador de programas - previne erros entre programas e utilizações impróprias;
3. Manipulador de dados - tanto ficheiros, como diretórios e a própria memória;

### Serviços do sistema operativo

Execução de programas, operações I/O, manipulador de ficheiros de sistema, detector de erros, comunicação, protetor de recursos e segurança em operações I/O.

## 2 - Funcionamento do Computador

Divisão em Hardware + Sistema Operativo + Aplicações / Programas + Utilizadores. Primeiro atua o `bootstrap`, na ROM e inicia o sistema e o kernel. O CPU ligam-se à memória e controladores (com local buffer para instruções de memória). Memória Cache e o DMA (direct memory access), para tarefas enquanto o CPU faz outras, precisa do CPU para iniciar e acabar o processo, e há interrupt por cada bloco e não por cada byte movido.

## 3 - Hierquia de memória

Do mais caro / mais rápido / menor para o maior: registos, cache, memória principal, SSD, HD, Optical Disk, Magnetic Tapes. Voláteis (1, 2, 3) e não voláteis (4, 5, 6, 7).

## 4 - Tipos de processamento

- Entre processadores: processamento assimétrico (cada processador tem a sua tarefa) e processamento simétrico (todos os processadores fazem todas as tarefas);
- Entre sistemas: clustering assimétrico (cada máquina tem a sua tarefa, há uma máquina master em hot-standby que monitora as outras e substitui caso alguma falhe) e clustering simétrico (várias máquinas em execução, monitorando-se mutuamente);

Para o segundo caso, existem:
1. SAN (Storage-Area Network) - manipula programas para processamento paralelo;
2. DLM (Distributed Lock Manager) - evita conflitos em operações concorrentes; 

### Multiprograming vs. Multitasking/Timesharing

Enquanto que no primeiro caso organiza as tarefas para que o CPU tenha sempre algo que fazer (mas apenas uma parte dos trabalhos está colocada na memória), no segundo a transição entre tarefas é tão rápida que dá para o utilizador interagir com o programa. A segunda é melhor.

## 5 - Ambientes de Computação

1. Tradicional - uso geral. Um CLI (command line) e um GUI (graphical user interface);
2. Mobile - telemóveis, tablets;
3. Distributed - networks, como se fosse um único sistema;
4. Client-Server - respondem às exigências do utilizador, com interfaces, bd, retirar e colocar arquivos;
5. Peer-to-Peer - não há distinção entre clientes e servidores, através do protocolo discovery;
6. Virtualization - como nas virtual machines;
7. Cloud computing - públicas, privadas e na sua maioria híbridas;
8. Real time embedded systems - executam tarefas sem terem o mesmo sistema operativo. Restrições e tempo bem delimitado para cada tarefa;

## 6 - Estrutura

1. MS-DOS (Simple Structure) - funcionalidades num menor espaço. não divisível por módulos (estão muito interligados) e formado por: application programs, resident system programs, device drivers, ROM BIOS device drivers;

2. Unix (Non Simple Structure - Monolithic) - limitado pelo harware. Duas partes: system programs e kernel (acima do hardware, abaixo das system calls, permite o file system, CPU scheduling, memory management);

3. MicroKernel - ligação entre serviços (drivers, file drivers, virtual memory) e o client server, com maior memória alocada -> menos código está a ser executado em kernel mode (bit = 0) e mais em user mode (bit = 1)

## 7 - System Calls e passagem de Parâmetros

Para aceder a memória ou harware (conteúdo restrito, previligiado), o processo transita de User Mode para Kernel Mode (menos seguro, se ocorrer um erro afeta o sistema todo). Há três tipos de passagem de parâmetros:

1. Pelos registos. Pode não haver tantos registos como parâmetros. Limita.
2. Passados em bloco na memória. O endereço do bloco é passado num registo. Não limita.
3. Colocados numa stack (pushed) e o sistema operativo faz (pop) quando necessário. Não limita.

## 8 - Processos

Processos (ativos) são programas (passivos) em execução, independentes mas cooperativos. Os programas podem ter vários processos, um processo pode ter várias unidades de processamento (threads). Divisível em texto (código do programa), data (variáveis globais), current activity (program counter, processor registers), heap (memória dinamicamente alocada) e stack (registos de retorno, parêmetros, variáveis locais - memória temporária). Podem ser classificados como:
1. I/O-bound process - mais I/O do que computações, não usa muito o CPU;
2. CPU-bound process - mais computações, usa pouco os I/O;

Cada processo tem um ID, um state (new, running, waiting, ready, terminated), e um PCB (Process Control Block). Este último tem:
- o estado do processo;
- o número do processo, pID;
- program counter, local da próxima instrução a executar;
- o conteúdo de todos os registos a usar;
- CPU scheduling information (priorities);
- limites de memória;
- I/O, como lista de ficheiros abertos;

Context Switch -> Ato de mudar entre processos. Ir ao PCB do processo gguardar o estado/contexto, pegar noutro PCB de outro processo e carregar as informações para o CPU. Não deve ser uma operação muito demorada, uma vez que nessa altura o CPU fica a consumir ciclos de relógio sem efetuar qualquer trabalho.

## 9 - Process Scheduling

Escolhe processos para serem executados pelo CPU através de filas (job, todos, ready, na memória principal, device, estão à espera de I/O). Os Schedulers podem ser:
1. Short-term / CPU scheduler - invocado frequentemente, milissegundos, seleciona o processo que deve ser executado a seguir, alocando-o no CPU;
2. Long-term / job scheduler - invocado pouco, segundos ou minutos, controla o estado de multiprogramming. Coloca na queue o próximo processo pronto a executar (status == ready);
3. Medium-term scheduler - se o grau de multiprogramming tiver de ser decrementado. Remove o processo da memória, coloca-o no disco, trás de volta ao disco para continuar a execução - processo de swapping;

## 10 - Criação e término de processos

O processo pai (process identifier, pid = 1, init) cria os outros usando uma system call fork(), formando uma tree de processos. Pai e filho podem partilhar todos os recursos, ou parte, ou nada, podem ser executados concorrentemente ou o pai espera até que o filho termine.

- `fork()` para criar um child. Retorna um inteiro que é igual a zero se for um novo processo;
- `exec()` para executar o processo criado;
- `exit()` para terminar o processo criado e dar merge no pai que o criou;
- `abort()` para o pai matar o filho (por excesso de recursos usados, por não necessitar mais, pelo pai também estar quase a morrer);
- `wait()` para o pai esperar pelo processo do filho;

Normalmente, quando um pai morre, morrem todos os filhos descendentes. Senão, os filhos são considerados `process zombi` quando nenhum pai está a esperá-lo (e obviamente não fez o wait()) ou `process orphan`, se o pai morreu sem invocar o wait().

## 11 - IPC (Interproceess Communication)

Para partilha de informação, melhorar a rapidez da computação, modularidade e conveniência, temos dois processos: Shared Memory e Message Passing. Daí resulta o paradigma do produtor-consumidor (com bounded e unbounded buffer) no caso do shared memmory. Se for bounded, o produtor só coloca quando o index está vazio, o consumidor só consome quando o index não está vazio. Para o Message Passing, temos o send() e o receive(), através de um communication link.

### Communication link

Ocorrem através de implementações Físicas (Memória partilhada, harware bus, network) e lógicas (Direct or indirect, Sincronizada ou não sincronizada em tempo, buffer automático ou explícito);

1. Diretas - único link, normalmente bidirecional. send (P, *message*);
2. Indiretas - por portas/mailbox, cada um com id, cada par de processos pode ter vários links. send (A, *message*);
3. Sincronizadas - em modo blocking:
    - send: o que envia fica bloqueado até que a mensagem seja recebida;
    - receive: o que recebe fica bloqueado até que a mensagem esteja disponível;
4. Não sincronizadas - em modo non-blocking:
    - send: o que envia continua em execução normal depois;
    - receive: o que recebe, pode receber a mensagem válida ou nula;
5. Buferring:
    - Capacidade zero - o sender deve esperar pelo processo que irá receber;
    - Capacidade finita - o sender deve esperar se a ligação estiver cheia;
    - Capacidade infinita - o sender nunca espera;

## 12 - Sockets and Pipes

1. Sockets - Ip + porta. A comunicação é feita entre um par de sockets.
2. Pipes - Canal de comunicação entre dois processos. Podemos ter `ordinary pipes`, que não podem ser acedidas externamente ao processo que a criou (normalmente o processo pai cria um ordinary pipe para comunicar com o processo filho que criou). São unidirecionais, pelo que a escrita é feita na ponta *write-end* e o receive na parte *read-end*; e `named pipes`, que podem ser acedidas sem uma relação pai-filho. São mais poderosas que as *ordinary pipes*, onde a comunicação é bidirecional e vários processos podem usar a mesma *pipe* para comunicação. Existe em sistemas Windows e Unix.

## 13 - Sincronização de processos

O Scheduling pode ser de dois tipos:
1. `Preemptive` – permite entrada na zona crítica quando está em kernel mode. (Running | Waiting) -> Ready;
2. `Non-preemptive` – executa até sair do kernel model ou até voluntariamente. Essencialmente livre do race condition. Running -> Waiting or Terminates.

### 13.1 - Secção crítica

Zona onde os processos podem mudar o conteúdo de variáveis, ficheiros. Sem cuidado resulta em race condition e leva a resultados inesperados. Os processos competem para chegar à secção crítica.

Soluções:

1. Mutual Exclusion - Se um processo está na secção crítica, outro não pode estar a ser executado;
2. Progress - nenhum processo pode ser ultrapassado indefinidamente;
3. Bounded Waiting - limite do número de esperas que um processo pode fazer em relação a outros que já tenham entrado na secção crítica;

### 13.2 - Peterson's Solution


