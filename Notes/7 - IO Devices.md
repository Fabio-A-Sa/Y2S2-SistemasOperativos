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

1. Polling: o CPU monitoriza o estado do dispositivo periodicamente e quando este estiver disponível manda a informação. Desvantagem: *busy waiting*, gasta ciclos de relógio, principalmente em dispositivos de baixa frequência de utilização.

2. Interrupt: é o dispositivo que inicia a interação, quando este estiver disponível, enviando-lhe um sinal (um booleano por exemplo) através das `interrupt request lines`, linhas do Bus entre a motherboard e o CPU, assim como um número identificador: identifica tanto quem enviou a interrupção como o que exatamente aconteceu.