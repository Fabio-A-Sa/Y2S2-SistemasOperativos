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

