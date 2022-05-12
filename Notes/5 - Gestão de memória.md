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

| index | base | tamanho | valid | permissões | dirty |
| --- | --- | --- | --- | --- | --- |
| 0 | b0 | t0 | 1 | R | 0 |
| 1 | ? | ? | 0 | ? | 1 |
| 2 | b2 | t2 | 1 | RW | 1 |
| N | ? | ? | ? | ? | 1 |

No código das funções, a permissão é só de leitura `R` (escrita em cima das instruções leva a erros). Na "data", no "bss" na "heap" e na "stack" já é possível ler e escrever `RW`. Isto garante uma camada de proteção à memória.

Dirty bit está a zero se depois de copiado o segmento para memória não sofreu alterações (não precisa de ser novamente copiado - uma instrução pesada, que é de evitar).

A tabela pode ser imaginada segundo esta estrutura de dados:

```c++
typedef unsigned long uint;
typedef struct {
    bool valid;
    uint base;
    uint tamanho;
    uint permissões;
    uint dirty;
} entry;
int number_segments;
entry segmentTable[number_segments];
```

### Tradução de endereços físicos na tabela para endereços virtuais no processo

Dada a configuração do sistema operativo com N bits que gera endereços virtuais de N bits, N-X bits determinam o número do segmento e X bits determinam o offset desse mesmo segmento. Assim o máximo número de bits de tamanho de um segmento é dado por 2^X.
- `Teste da linha na tabela` -> com o endereço da tabela na memória conhecido do processo e a primeira parte do endereço virtual. Erro não fatal, significa que o segmento não está na memória e nesse caso o CPU vai buscar;
- `Teste do offset` -> com o offset do segmento e a informação da base na tabela. Dá erro fatal caso o endereço seja fora do segmento;

#### Vantagens:

- É uma forma natural de dividir o processo;
- Não é necessário ter o processo todo colocado na memória ao mesmo tempo;
- Preserva a localidade de referência espacial (bom para a memória cache -> as instruções estão na mesma zona de memória);

#### Desvantagens:

- Ir buscar à tabela os dados de cada segmento de cada processo na memória alocada pelo kernel. Implica dois acessos à memória;
- 2 testes;
- Adição;
- Mais espaço para guardar toda a localização dos segmentos por registos;
- O tamanho dos segmentos é diferente: a memória fica fragmentada (`Fragmentação externa`) em pouco tempo. Temos espaço suficiente para colocar um novo segmento, mas esse espaço está disperso. Solução: desfragmentar a memória: ir a todas as tabelas, alterar os apontadores e copiar todos os segmentos para ficarem mais próximos entre si;

### 2. Técnica de Paginação

Separa o espaço de endereçamento em blocos/páginas de tamanho igual. O número de páginas é sempre uma potências de dois, porque o tamanho é dado por 2^k (com k muito inferior a n, n = número de bits de endereçamento).

Pode haver `Fragmentação interna`: o tamanho do processo pode não ser múltiplo do tamanho de cada página, nesse caso arredonda para cima. Na generalidade, os sistema operativos usam o tamanho de (4, 16, 32) kb. No pior dos casos, desperdiçamos (tamanho da página - 1) bytes, e este espaço não pode ser usado por outro process. Desperdiça na ordem de 1% da memória toda, pelo que ainda é melhor do que a fragmentação externa da segmentação. 

Quanto maior o tamanho da página, maior será o desperdício e menor será o número de páginas em memória possível, mas assim evita troca frequente entre memória e disco (*swapping*).

A memória física tem slots, de tamanho exatamente iguais aos das páginas do proceso. Assim nunca há problemas de fragmentação externa.

#### Tabela de páginas

Cdaa processo tem uma tabela de páginas associada. A tabela tem 2^(n-k), com n = número de bits da arquitetura e k o número de bits da página, ou seja, o número de páginas do processo. Contém 3 entradas:

- Base associada à página na memória física;
- Bit de validade, se a página está carregada em memória
- Dirty bit, se a página foi escrita enquanto estava na memória. Para instruções do programa (página 0, em .text), bit = 0 pois nunca se muda;

Esta tabela não tem o limite pois as páginas têm todas o mesmo tamanho e qualquer endereço virtual gerado é válido (nunca ultrapassa a própria página). Também não tem permissões, porque não é uma divisão a nível funcional, pelo que é possível haver páginas que contenham código Read-Only e Read-Write.

Para uma arquitetura de 8 bits (n = 8) e com k = 5 (número de páginas), se virtual address = 10001101 (X1 + X2), então 100 representa o número da página e 01101 o offset dentro da página. Está localizado na página 4 a uma distância de 13 bytes do início.

Com os primeiros X1 bits sabe o índex da tabela, consulta a tabela:
- Se v = 0, retorna um page fault erro;
- Se v = 1, retorna o endereço base dessa página e soma o offset contido em X2;

O PCB do processo contém um registo com o endereço base da tabela: o PTBR.

##### Desvantagens:

- 2 acessos à memória (ir à tabela de páginas e depois ir ao endereço calculado) por cada N;
- divisão do processo: nem pouco nem exagerado (ver acima);

#### Otimização

De modo a não aceder à memória para consultar a tabela de páginas. Guardar em "cache" o X1 dos endereços virtuais. Se nas próximas instruções tiverem na mesma página, então o X1 já é conhecido e escusa de ir à memória. No limite, o número de acessos à memória é exatamente igual ao número de páginas existentes no processo + acesso para cada instrução físico. A cache dentro do CPU é a Translation Lookaside Buffer -> fully associative cache, funciona como uma tabela em que se coloca o X1 e o endereço base retornado na memória.


#### Swapping

Troca de páginas na memória física. Se dirty = 0, então faz swaping (a página, desde que está em memória, não foi modificada, alterada, reescrita), se dirty = 1, então antes de fazer swapping tem de reescrever a página na memória, para guardar as alterações. Swapping troca páginas entre a memória física e o disco (na parte de swap partition, que também está partida com o mesmo tamanho das páginas).

1. Random:
    - Rápido
    - Pode tirar uma página muito utilizada no sistema

2. LRU Last Recently Used:
    - Menos rápido;
    - Resolve o problema do `random`;
    - O SO tem de guardar, numa estrutura de dados adequada, a ordem das páginas menos frequentemente usadas. Faz swapping com aquela página que foi usada à mais tempo;

3. LFU Least Frequently Used:
    - Menos rápido;
    - Resolve o probela do `random` e parecido com o LRU;
    - Incrementa um contador em cada página em cada vez que ela é utilizada. Escolhe a página com menor quantidade para fazer swapping;

