# 3 - Processes

Um processo é um programa em execução que pode ter vários estados (new, running, waiting, ready, terminated). Enquanto que um programa é passivo, é somente um ficheiro executável, o processo é ativo pois há a execução propriamente dita. Todos os processos de um sistema devem ser independentes e cooperativos entre si. <br>

Um processo pode ser descrito de duas formas distintas:

1. `I/0-bound process` - dispende mais tempo a fazer operações input ou output do que computações, usando pouco tempo do CPU de cada vez;

2. `CUP-bound process` - dispende mais tempo a fazer computações, leva mais tempo do CPU do que operações input/output;

Existem várias partes usadas nos processos:

1. Text section, onde está o código do programa
2. Program counter e os registos do processador
3. Stack, onde são guardadas os dados temporários, como variáveis locais
4. Data section, para as variáveis globais
5. Heap, contém a memória alocada dinamicamente

<p align="center">
<img src = "..\\Images\\Memory.png" alt = "memory sheme" title = "memory scheme" width = "300" height = "400">
</p>

### Process Control Block (PCB)

Também conhecido como Task Control Block, contém a informação associada a cada processo. 

<p align="center">
<img src = "..\\Images\\Process Control Block.png" alt = "pcb" title = "pcb" width = "300" height = "400">
</p>

Legenda:

- Process state: running, waiting, new, ready, terminated
- Process number: número do processo
- Program counter: localização das instruções para executar a seguir
- Registers: conteúdo de todo o processo, X0 até X31
- Memory limits: memória alocada para o processo
- List of open files

### Threads

Cada thread do processador consegue executar um processo de cada vez. Com mais threads é possível maximizar o número de tarefas efetuadas por segundo, como se tivessemos vários Process Control Block e múltiplos Program Counters. O Process sheduling (agendamento de processos), trata de organizar os processos por ordem preferencial.

#### 1 - Short-term sheduler / CPU sheduler

Seleciona que processo pode ser executado a seguir e alocado no CPU. Às vezes só há este sheduler no sistema. Este é invocado frequentemente, em milisegundos, pois tem de ser rápido.

#### 2 - Long-term sheduler / job sheduler

Seleciona que processo deve ser trazido para a fila de processos prontos a executar, executado com pouca frequência (segundos ou minutos), pois deve ser lento.

## Process Creation

O processo Pai cria um processo filho que, ao criar outro processo, forma uma árvore de processos. Em Unix, o pai de todos é o `init` com pid (process identifier) = 1. A partir daí saem todos os outros do sistema. Ou o pai deixa o filho terminar, ou então entram em concorrência de execução (competição por tempo de CPU e ciclos de relógio).

- `fork()` para criar um child;
- `exec()` para executar o processo criado;
- `exit()` para terminar o processo criado e dar merge no pai que o criou;
- `abort()` para o pai matar o filho (por excesso de recursos usados, por não necessitar mais, pelo pai também estar quase a morrer);
- `wait()` para o pai esperar pelo processo do filho;

Normalmente, quando um pai morre, morrem todos os filhos descendentes. Senão, os filhos são considerados `process zombi` quando nenhum pai está a esperá-lo (e obviamente não fez o wait()) ou `process orphan`, se o pai morreu sem invocar o wait().

## Comunicação entre processos

Os processos, embora independentes (porque não devem perturbar ou influenciar a execução de outros processos), devem comunicar para:

- troca de informações / mensagens;
- partilha de zona de memória;
- modularidade;
- conveniência;

Principal problema: acaba por existir um processo que cria a informação para que outro processo (o consumidor) o utilize. Pelo que a utilização de um buffer (seja ele `unbounded-buffer` ou `bouder-buffer`).

```c
/* bounder - buffer example */
#define BUFFER_SIZE 10
typedef struct {
    int *values[];
} item;

item buffer[BUFFER_SIZE];
int in = 0, out = 0;
```

### Communication link

Entre dois processos há um único link, normalmente bidirecional, e cuja ligação é feita automaticamente. Ocorrem através de implementações:

1. Físicas
    - Memória partilhada;
    - Hardware bus;
    - Network;
2. Logical
    - Direct or indirect;
    - Sincronizada ou não sincronizada (tempo);
    - Com buffer automático ou explícito;

#### Diretas

Entre dois processos há um único link, normalmente bidirecional, e cuja ligação é feita automaticamente.

```c
send (P, *message*); <!-- send a message to process P -->
receive (Q, *message*); <!-- receive a message from process Q -->
```

#### Indiretas

Mensagens recebidas pelas portas (*ports* or *mailbox*), em que cada uma contém um id único onde os processos podem comunicar. Cada par de processos pode ter vários links, ao contrário da comunicação direta anteriormente descrita.

```c
send (A, *message*); <!-- send a message to mailbox A -->
receive (A, *message*); <!-- receive a message from mailbox A -->
```

#### Sincronizadas

Mensagens trocadas em modo `blocking`:
- Blocking send: o processo que envia fica bloqueado até que a mensagem seja recebida por outro processo;
- Blocking receive: o processo que está a receber fica bloqueado até que a mensagem esteja disponível; 

#### Não sincronizadas

Mensagens trocadas em modo `non-blocking`:
- Non blocking send: o processo que envia, envia a mensagem e continua em execução;
- Non blocking receive: o processo que recebe, ou recebe uma mensagem válida ou nula;

#### Buferring

Pode ter três capacidades:

1. Capacidade zero - o sender deve esperar pelo processo que irá receber;
2. Capacidade finita - o sender deve esperar se a ligação estiver cheia;
3. Capacidade infinita - o sender nunca espera;

## Comunicação em sistemas Client-Server

Através destes sistemas:

### Sockets

Um endpoint da comunicação. Resulta na concatenação entre um endereço `ip` e uma `port`. Exemplo: `161.25.19.8:1625`. <br>
A comunicação é feita entre um par de *Sockets*.

### Pipes

