# 3 - Processes

Um processo é um programa em execução que pode ter vários estados (new, running, waiting, ready, terminated). Enquanto que um programa é passivo, é somente um ficheiro executável, o processo é ativo pois há a execução propriamente dita. Existem várias partes usadas nos processos:

1. Text section, onde está o código do programa
2. Program counter e os registos do processador
3. Stack, onde são guardadas os dados temporários, como variáveis locais
4. Data section, para as variáveis globais
5. Heap, contém a memória alocada dinamicamente

<p align="center">
<img src = "..\\Images\\Memory.png" alt = "memory sheme" title = "memory scheme" width = "400" height = "600">
</p>

### Process Control Block (PCB)

