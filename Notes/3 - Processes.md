# 3 - Processes

Um processo é um programa em execução que pode ter vários estados (new, running, waiting, ready, terminated). Enquanto que um programa é passivo, é somente um ficheiro executável, o processo é ativo pois há a execução propriamente dita. Existem várias partes usadas nos processos:

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

Cada thread do processador consegue executar um processo de cada vez. Com mais threads é possível maximizar o número de tarefas efetuadas por segundo, como se tivessemos vários Process Control Block e múltiplos Program Counters.

