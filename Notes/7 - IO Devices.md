# 7 - I/O Devices

Atualmente existe uma vasta gama de disposivos de entrada e saída, ou por interface física (cabos) ou por rede. É uma tendência crescente o aumento da variadade. É necessário um maior suporte ao nível do sistema operativo para controlar todos. Standardização de sistemas, usar software e harware que permitem suportar e construir dispositivo sem muito esforço.  

### Porta

Encaixe que permite ligar dispositivos ao computador. A porta pode ser externa (USB por exemplo) ou pode ser interna (numa motherboard, por exemplo).

### Bus

Linhas de harware onde é transferida informação. A largura de banda do bus é a quantidade de bytes que são passados por unidade de tempo.

### Controlador

Circuito interno ou externo que controla as trocas de informação entre o dispositivo e o CPU e memórias. 

## Device driver

Dispositivos são fornecidos com componentes de software que encapsulam a complexidade de interação entre o kernel e o dispositivo. O kernel é auxiliado pelo device driver, que traduz os comandos para que seja compreendido pelo controller do dispositivo.

## Tipos de dispositivos

- `Storage`: discos, DVD, Blue Ray, tapes, pen drives, ...
- `Networking`: placas ethernet, placa Wifi, bluethooth, zigbee, xbee, ...
- `User interface`: teclado, rato, monitor, placa gráfica, joy stick, webcam, audio, ...
- `Outros dispositivos`: sensores, estações meteorológicas, acessórios para jogos, ...

## Ligações entre dispositivos

A parte mais rápida do computador (mais bytes mandados por unidade de tempo) é a que liga o CPU à memória física e à memória cache. 

O microprocessador `North Bridge` controla a ligação / controla o tráfego de informação entre o Bus do processador e o Bus dos dispositivos de entrada e saída. Este último pode ser do tipo:
- ISA;
- EISA;
- SCSI;
- PCI;
- PCI Express;

Ao Bus dos dispositivos de entrada e saída está ligado um `socket` PCI Express, à qual está ligada a placa gráfica que se conecta com o monitor. Também pode haver um socket para controlar os discos SATA ou SCSI.

Para dispositivos de mais baixa velocidade (ligados por USB, ratos e teclados), existe o controlador `South Bridge`.

## Interação CPU / Dispositivos

### Tipos de interação

1. Comandos diretos com o device driver

O kernel envia comandos diretamente para o device driver para que possa traduzir a comunicação com o dispositivo.

2. Memory-mapped I/O

O input e o output são mapeados em memória. Há uma parte da memória física (alguns endereços) que está reservada para a interação entre dispositivos, assim como em LCOM. Escrever/ler para determinados endereços significa escrever/ler do dispositivo.<br>
Vantagem: além das operações, dá para saber o estado do dispositivo (buffer cheio, se está disponível, se há erros de paridade...). É mais rápido por este método do que por comandos diretos.

### Funcionamento

Numa primeira fase, a fase de sincronização (`hand shaking`) onde têm a ateção um do outro, é necessária antes de qualquer comunicação. Pode ser de dois tipos:

1. `Polling`: o CPU monitoriza o estado do dispositivo periodicamente e quando este estiver disponível manda a informação. Desvantagem: *busy waiting*, gasta ciclos de relógio, principalmente em dispositivos de baixa frequência de utilização.

2. `Interrupt`: é o dispositivo que inicia a interação, quando este estiver disponível, enviando-lhe um sinal (um booleano por exemplo) através das `interrupt request lines`, linhas do Bus entre a motherboard e o CPU, assim como um número identificador: identifica tanto quem enviou a interrupção como o que exatamente aconteceu (origem e causa do interrupt).

#### Tratamento de interrupções

Quando o CPU recebe uma interrupção, suspende o tratamento do processo que estava a calcular e guarda o seu estado em registos, sem o retirar do CPU. Só há um interrupt que retirar o processo corrente no CPU: o que indica final do tempo de execução. Passa de user para kernel mode. Depois, com o hook_id encontrado, vai a uma tabela do kernel, a `interrupt vector`, em que cada entrada da tabela corresponde a uma função que deve ser invocada para tratar do dispositivo (o `input handler`). 

#### DMA

Existe interrupção excessiva do CPU para transferência de ficheiros em disco. Uma solução é usar um controlador de DMA (Direct Memory Access). Está entre disco e o CPU. O CPU ao receber uma interrupção para transferência de bytes, ativa o DMA com os dados necessários (localização inicial, localização final, quantidade de informação a enviar) e deixa de ser interrompido. O DMA gera os endereços físicos, retorna os dados necessários do disco e retorna uma interrupção para notificar o CPU que a operação foi realizada com sucesso ou com erros.

## Sistemas multitasking

- Fazem uso intensivo de interrupções de dispositivos, com input e output;

- Os interrupts, em certas circunstâncias, podem ser ignorados temporariamente: quando este está a executar código crítico / em kernel mode. Nesse caso, depois de regressar a user mode, trata do handler desse interrupt;

- O CPU tem de determinar rapidamente a origem e a causa da interrupção;

- Algumas interrupções têm prioridade sobre outros (`maskable interrupts`, dos dispositivos, e `unmaskable interrupts`, do sistema operativo). As interrupções gerados pelo sistema operativo têm prioridade face às interrupções geradas por interações com utilizadores, pois são necessárias para a integridade de todo o sistema. Existe uma linha de interrupts (*interrupt request lines*) para cada prioridade do sistema, implementados como fila de prioridades.