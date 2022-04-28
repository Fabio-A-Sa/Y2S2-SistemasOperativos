# 5 - Kernel - Gestão de Memória

## Tópicos

1. Gestão de CPU;
2. Gestão de memória;
3. Gestão de dispositivos I/O;
4. Sistema de Ficheiros;

## Gestão de Memória

Todos os computadores atuais implementam a arquitetura de `von Newmann` ou `stored program architecture`, onde o computador é divido em três partes lógicas:
- CPU, a unidade principal de processamento (dados voláteis, preço por byte muito maior);
- Memória, onde estão guardados os dados e programas, os processos são mantidos aqui (dados voláteis);
- Dispositivos I/O, nomeadamente discos (HDD e SSD) (dados persistentes, preço por byte barato);

### Latência

Tempo que demora entre o pedido da informação e a recepção dessa mesma informação.

### Instruction Fetch, Load e Store

Instruction fecth -> buscar um novo processo para a memória <br>
Quando o CPU vai buscar à memória a nova instrução a executar, ou leitura de registos ou escrita em registos. Aqui a latência anda na ordem das dezenas de ciclos de relógio. Em disco, a latência é muito superior.

## Gestão de memória eficiente

Se os endereços das funções fossem endereços físicos da memória, daria erro pois o compilador só o poderia executar numa determinada zona.

1. `Endereço físico` - na memória física do sistema;
2. `Endereço virtual` - endereço que só vale dentro do espaço de endereçamento do processo;

Cada processo, quando iniciado, guarda informações em dois sítios de memória:

- O `PCB`, que reune informação sobre o estado atual do processo, o process id, os registos, o status;
- O `Espaço de endereçamento`: texto, dados, heap e stack. Começa em 0 e termina num limite l, indicado pela arquitetura do processador. Se a arquitetura for de X bits, o espaço de endereçamento vai de 0 até 2^X-1 bits, vai de 0x00000000 até 0xFFFFFFFF, ou seja, 4GB. Um processo só pode ocupar, no máximo, 4GB, embora a maior parte tenha um espaço de endereçamento muito inferior;

## Transição da memória virtual para a memória física

Base = distância entre a posição inicial 0 e o início do espaço de endereçamentos alocada na memória física
Se endereço virtual for menor que o endereço limite do processo:
    - Endereço físico = Endereço virtual + base
Else:
    - Memory error

```c++
char *p;
int x = *p; // erro -> endereço virtual fora do espaço de endereçamento
```

A base e o limite são fixos, e são guardados em dois registos no PCB. Só mudam se o CPU trocar a zona onde estão, e nesse caso atualiza os dados do PCB de acordo com a nova localização.
A tradução de endereços virtuais para endereços físicos ocorre dentro do CPU, onde há verificações de limites segundo a equação de cima e se não houver erro retorna o endereço físico. O circuito chama-se `MMU`, a Memory Management Unit. Gera o endereço no momento imediatamente anterior à saída do endereço.

### Custos da transição de memória virtual para memória física

Para cada processo:

- Guardar a base e o limite em registos (unsigned int ou unsigned long);
- Um teste;
- Uma soma;

## Divisão de processos

Para que possam exitir mais processos prontos a executar na memória, sem necessidade de 
Há duas formas:
- Segmentação;
- Paginação;

### 1. Técnica de Segmentação

Divide o processo numa perspectiva funcional. Todos os processos podem ser divido em:

1. Text - Binário do código do programa
2. Data - Binário das variáveis globais inicializadas (double x = 2.45;)
3. Bss - Binário das variáveis globais não inicializadas (double y;)
4. Heap - Zona de memória usada para alocar espaço (com malloc() por exemplo)
5. Stack - para guardar as chamadas de funções e variáveis a usar

1, 2 e 3 formam o ficheiro binário `a.out`, zona estática <br>
4 e 5 formam a zona dinâmica, só existe informação lá enquanto o programa está em execução <br>

Cada bloco é alocado na memória física por uma qualquer ordem. Cada bloco tem de guardar a sua base e o tamanho. Assim é necessário guardar, para N segmentos, 2N números para transformar os endereços virtuais em endereços físicos. <br>
Cada processo P pode ter N segmentos, e existe uma estrutura de dados (tabela de segmentos) que guarda todos os dados de cada segmento. A tabela está guardada na memória física associada ao kernel do sistema operativo. O processo deixa assim de guardar em PCB dois registos, um para a base e outro para o tamanho, e passa a guardar dois registos: um STBR (segment table base register, que aponta para a zona de memória física onde a sua tabela está) e um STLR (que indica o número de segmentos presentes na tabela).

| index | base | tamanho | valid | permissões |
| --- | --- | --- | --- | --- |
| 0 | b0 | t0 | 1 | R |
| 1 | ? | ? | 0 | ? |
| 2 | b2 | t2 | 1 | RW |
| N | ? | ? | ? | ? |

No código das funções, a permissão é só de leitura `R` (escrita em cima das instruções leva a erros). Na "data", no "bss" na "heap" e na "stack" já é possível ler e escrever `RW`. Isto garante uma camada de proteção à memória.

A tabela pode ser imaginada segundo esta estrutura de dados:

```c++
typedef unsigned long uint;
typedef struct {
    bool valid;
    uint base;
    uint tamanho;
    uint permissões;
} entry;
int number_segments;
entry segmentTable[number_segments];
```

### Tradução de endereços físicos na tabela para endereços virtuais no processo

Dada a configuração do sistema operativo com N bits que gera endereços virtuais de N bits, N-X bits determinam o número do segmento e X bits determinam o offset desse mesmo segmento. Assim o máximo número de bits de tamanho de um segmento é dado por 2^X.
- `Teste da linha na tabela` -> com o endereço da tabela na memória conhecido do processo e a primeira parte do endereço virtual. Erro não fatal, significa que o segmento não está na memória e nesse caso o CPU vai buscar;
- `Teste do offset` -> com o offset do segmento e a informação da base na tabela. Dá erro fatal caso o endereço seja fora do segmento;

#### Penalização desta técnica de segmentação:

- Ir buscar à tabela os dados de cada segmento de cada processo na memória alocada pelo kernel. Implica acessos à memória física;
- 2 testes;
- Adição;

### 2. Técnica de Paginação