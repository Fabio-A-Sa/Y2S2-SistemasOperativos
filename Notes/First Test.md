# Preparação para o primeiro teste

## Tópicos:

1. Definição de sistema operativo e funções;
2. Partes e funcionamento do computador;
3. Hierarquia de Memória;
4. Tipos de processamentos;
5. Ambientes de computação
6. ...

## 1 - Sistema Operativo

Intermediário entre o harware e o utilizador, para ser mais acessível e fácil de usar. O sistema operativo é acionado por interrupções e é:
1. Alocador de recursos - minimiza os conflitos entre hardware e software para uma melhor performence;
2. Controlador de programas - previne erros entre programas e utilizações impróprias;
3. Manipulador de dados - tanto ficheiros, como diretórios e a própria memória;

## 2 - Funcionamento do Computador

Divisão em Hardware + Sistema Operativo + Aplicações / Programas + Utilizadores. Primeiro atua o `bootstrap`, na ROM e inicia o sistema e o kernel. O CPU ligam-se à memória e controladores (com local buffer para instruções de memória). Memória Cache e o DMA (direct memory access), para tarefas enquanto o CPU faz outras, precisa do CPU para iniciar e acabar o processo, e há interrupt por cada bloco e não por cada byte movido.

## 3 - Hierquia de memória

Do mais caro / mais rápido / menor para o maior: registos, cache, memória principal, SSD, HD, Optical Disk, Magnetic Tapes. Voláteis (1, 2, 3) e não voláteis (4, 5, 6, 7).

## 4 - Tipos de processamento

- Entre processadores: processamento assimétrico (cada processador tem a sua tarefa) e processamento simétrico (todos os processadores fazem todas as tarefas);
- Entre sistemas: clustering assimétrico () e clustering simétrico (várias máquinas em execução, monitorando-se mutuamente);