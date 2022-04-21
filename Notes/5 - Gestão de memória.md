# 6 - Kernel - Gestão de Memória

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
    - Erro

```c++
char *p;
int x = *p; // erro -> endereço virtual fora do espaço de endereçamento
```

A base e o limite são fixos, e são guardados em dois registos no PCB.
A tradução de endereços virtuais para endereços físicos ocorre dentro do CPU, onde há verificações de limites segundo a equação de cima e se não houver erro retorna o endereço físico. O circuito chama-se `MMU`, a Memory Management Unit. Gera o endereço no momento imediatamente anterior à saída do endereço.