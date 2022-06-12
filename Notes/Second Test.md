# Preparação para o segundo teste

## Tópicos:

0. Arquitetura de von Newmann;
1. Gestão de memória;
    1. Tradução de endereços;
    2. Espaço de endereçamentos;
    3. Segmentação;
    4. Paginação;
    5. Swapping;
2. Gestão de sistemas de ficheiros;
    1. Monolítico e microkernel;
    2. File System;
    3. Ficheiros;
    4. Directory Structure;
    5. Links;
    6. Manipulação de ficheiros;
    7. Localização de ficheiros;
3. Gestão de dispositivos I/O;
    1. Definições;
    2. Ligações entre dispositivos;
    3. Interações CPU / Dispositivos;
    4. Polling vs. Interrupts;
    5. DMA;

## 0 - Arquitetura de von Newmann

Todo o computador é constituido por CPU (dados voláteis), Memória (volátil, RAM) e Dispositivos (como discos, com dados persistentes, ou controladores I/O)

## 1 - Gestão de memória

### 1.1 - Tradução de endereços

Os endereços de memória são determinados pelo CPU em tempo de:
- `Compilação`, se a localização em memória já for conhecida. O endereço lógico é igual ao endereço físico;
- `Carregamento`, fazendo um código realocável. O endereço lógico é igual ao endereço físico;
- `Execução`, segundo um processo de tradução. Aqui o endereço lógico não é igual ao endereço físico e é chamado de endereço virtual;

O programador nunca tem acesso aos endereços gerados pelo processo(endereços virtuais/lógicos), pelo que são traduzidos pelo CPU na MMU (*Memory Management Unit*) quando necessitam de aceder à memória física. Se o endereço virtual pertencer ao intervalo [base, base-limite[, então o endereço físico é igual à soma da base com o endereço virtual, senão dá um erro ao sistema operativo.

O custo da tradução está associada à memória adicional para acoplar dois registos no PCB (*Program Control Block*, para a base e o limite) de cada processo, uma verificação e uma soma.

### 1.2 - Espaço de endereçamentos

Para uma arquitetura de X bits, o endereço resultante em qualquer processo poderá ir de 0 até 2^X-1.

### 1.3 - Segmentação

Partir o processo em partes lógicas, sendo estas:

1. Text - Binário do código do programa
2. Data - Binário das variáveis globais inicializadas (double x = 2.45;)
3. Bss - Binário das variáveis globais não inicializadas (double y;)
4. Heap - Zona de memória usada para alocar espaço (com malloc() por exemplo)
5. Stack - para guardar as chamadas de funções e variáveis a usar

1, 2 e 3 formam o ficheiro binário `a.out`, zona estática e 4 e 5 formam a zona dinâmica, só existe informação lá enquanto o programa está em execução.

O PCB do processo guarda o STBR (segment table base register, que aponta para a zona de memória física onde a sua tabela está) e um STLR (que indica o número de segmentos presentes na tabela).
A tabela contém o index, base, tamanho, se é valido, as permissões e dirty para cada segmento.

#### Tradução

Os primeiros bits determinam o index do segmento, os restantes determinam o offset dentro desse segmento. Existe duas idas à memória: uma para ir buscar o segmento (erro não fatal) e outra para com o offset buscar a parte necessária (erro fatal se estiver fora do intervalo).

#### Vantagens

Forma natural de divisão, sem necessidade de ter o processo todo na memória, bom para caches pois as instruções estão na mesma zona.

#### Desvantagens

Implica dois acessos à memória, dois testes, uma soma. Fragmentação externa, necessário desfragmentação.

### 1.4 - Paginação

Separa a memória e o processo em tamanhos (páginas/blocos) de igual tamanho e numa potência de dois. Existe fragmentação interna. Quanto maior o tamanho da página, maior o desperdício e menor será o número de páginas em memória possível, mas assim evita troca frequente entre memória e disco (*swapping*)

#### Tradução

Cada processo tem uma tabela de páginas com 2^K entradas. Logo, para um endereço virtual de X bits dependendo da arquitetura, os primeiros K bits são para determinar o índex e os restantes, X-K, para determinar o offset dentro da página.

O PCB contém somente o Page-table base register (PTBR) e o Page-table length register (PTLR). Necessita de duas idas à memória: uma para determinar o índex da entrada e a segunda para calcular o offset, com a verificação tanto do limite como do bit de validade (caso contrário, tem de fazer uma instruction fetch ao disco).

#### Vantagens

A memória cache (Translation Lookaside Buffer) guarda a primeira parte do endereço virtual e o endereço retornado da memória, assim evita de ir ao disco buscar. 

#### Desvantagens

Necessita de dois acessos à memória e há desvantagens/vantagens em cada tamanho do bloco escolhido para a partição.

### 1.5 - Swapping

Troca de páginas / segmentos entre a memória e o disco, operação de evitar dada a latência. O disco tem uma parte de swap partition, que está partida com o mesmo número de bytes das páginas dos processos. Se dirty = 0, então faz swapping (a página desde que está na memória não foi reescrita, podemos usar) senão antes de tudo vai reescrever a página na memória para guardar as alterações.

#### Troca de páginas na memória:

1. Random (rápido, mas pode tirar uma página muito utilizada no sistema)
2. LRU Last Recently Used (menos rápido, resolve o problema do random, o SO guarda numa estrutura a ordem de utilização das páginas. Faz swapping com a página que foi usada à mais tempo)
3. LFU Least Frequently Used (parecido com a anterior, tem um contadore faz swapping com a que menos frequentemente é usada)

## 2 - Gestão de sistemas de ficheiros

## 2.1 - Sistemas Monolíticos e Microkernel

UNIX é um sistema monolítico (CPU, memória, file system e I/O devices), enquanto que o Darwin é de microkernel (CPU, memória, I/O devices) e o User Space contém o file system.

## 2.2 - File system

Para resguardar os ficheiros, temos Hard Disk Drive e Solid State Disks (com memórias Flash / NAND, constituido por partes semicondutoras e imóveis - os chips). Para implementar um é importante conhecer a distribuição dos ficheiros a armazenar (se são grandes ou não) e a forma de aceder ao conteúdo (se é sequencial ou não, como o caso das bases de dados).

O File System é constituído por ficheiros e uma estrutura de dados e algoritmos (árvore, uma DAG). Cada nó aponta para um ficheiro colocado em disco. Unix (ufs, Unix File System), Linux (ext3, ext4, jfs, reiserfs, xfs, zfs, suporta ficheiros enormes), macOS (APFS, apple file system), Windows (NTFS, FAT File Alocator Table, FAT3, exFAT, LVM, logical volume memory), CD/DVD (ISO 9660).

## 2.3 - Ficheiros

Os ficheiros (multimédia, documentos, executáveis, bibliotecas, arquivos) podem ser manipulados (criar, elimiar, abrir, procura sequencial ou não, ler, escrever, fechar, guardar) e são constituidos, de acordo com a *struct stat* em nome, tamanho, permissões, dono, tempo (datas de modificação, criação, execução), tipo, e a localização dos blocos que contém a informação do ficheiro. 

## 2.4 - Directory Structure

Constituido por 3 partes principais:

### 2.4.1 - Boot Control Block (BCB)

Boot Block em Unix, Partition Block em Windows. Contém informação sobre aqueles ficheiros, se existe uma imagem do kernel bootable. Se tiver, tem também um boot loader, com as instruções para o carregar na memória. No início, o SO é carregado através da BIOS (Basic I/O System) que depois transfere o controlo para o boot loader correspondente. Se tiver vários kernel, usar o GRUB.

### 2.4.2 - Volume Control Block (VCB)

Super Block em Unix, Master File Tables, em Windows NTFS. Estatísticas gerais do File System (tipo, bytes por bloco, capacidade máxima, número de blocos, número de blocos vazios, um map que contém a localização dos blocos livres)

### 2.4.3 - File Control Block (FCB)

Estruturas de dados e algoritmos que representam a informação de ficheiros e a relação entre eles. Uma árvore ou um DAG, de complexidade logarítimica para a pesquisa, remoção e inserção. 

## 2.5 - Links

Apontadores para um ficheiro existente. Podem ser soft/simbólicos, como atalhos, e hard, que são uma cópia do ficheiro em si e quando apagados (se existir somente um hard link) apagam o ficheiro também.

## 2.6 - Manipulação de ficheiros

O SO guarda a informação dos ficheiros abertos em tabelas. Estas podem ser:

### 2.6.1 - SWOFT (System Wide Open File Table)

Tem entrada para cada ficheiro aberto e uma cópia, em cada index, da struct stat. Só guarda as modificações do ficheiro no disco só quando é mesmo necessário, caso contrário só no fecho. Só existe uma tabela desta no sistema.

### 2.6.2 - PPOFT (Per Process Open File Table)

Para ficheiros manipulados em mais do que um processo, a informação da tabela SWOFT é insuficiente, pois há necessidade de guardar para cada processo como este está a usá-lo, a posição de leitura, permissões e um apontador para o ficheiro manipulado na SWOFT. As primeiras entradas são 0, stdin, 1, stdout, 2, stderror. A system call open() carrega a SWOFT e mais uma linha na PPOFT do processo.

## 2.7 - Localização de ficheiros

### 2.7.1 - Blocos contíguos

Aloca os blocos seguidos na memória. É só necessário saber a localização do primeiro bloco e o número de blocos. Por um lado é uma forma rápida em HDDs, para acesso sequencial e random. Mas por outro nem sempre há espaço seguido (usa a desfragmentação para combater a fragmentação externa) e o aumento do ficheiro provoca a alocação de todos os blocos desde o início.

### 2.7.2 - Lista de blocos

A struct star guarda um apontador para o primeiro bloco. Cada bloco aponta para o seguinte, até que no fim aponta para NULL. Pouco espaço de implementação, sem fragmentação externa e fácil de aumentar o tamanho ocupado pelo ficheiro. Por outro lado o acesso sequencial / random não é tão eficiente (em HDDs a cabeça é movida).

### 2.7.3 - Lista de blocos num array

Usado pelo FAT (File Allocator Table) da Microsoft. Blocos colocados de forma não sequencial sem apontadores. Existe um array, de tamanho igual à quantidade de blocos do ficheiro, que para cada entrada colocar a posição do próximo bloco. Por um lado só precisa saber o index do primeiro bloco, a complexidade temporal é boa, a informação é próxima. Por outro lado para ser ainda mais rápida colocar o array na memória RAM, se o ficheiro for grande necessita de vários blocos e um array também grande.

### 2.7.4 - Indexed Allocation

Usada nos UNIX File Systems. Na struct stat (inode), além dos parâmetros habituais há uma tabela de N entradas que contém apontadores para blocos não contínuos. Pode haver até 3 camadas (N^3 + N^2 + 2N blocos de um ficheiro, no máximo). Por um lado em ficheiros pequenos a complexidade de busca é pequena, se for grande é só criar outra tabela e as tabelas são copiadas para memória para melhor performence. Por outro lado as tabelas gastam muito espaço.

## 3 - Gestão de dispositivos I/O

## 3.1 - Definições

- Porta: encaixe que permite ligar dispositivos ao computador;
- Bus: Linhas de hardware por onde é transferida a informação. A largura é a quantidade de bytes de informação que são transferidos por unidade de tempo;
- Controlador: Circuito interno ou externo que controla as trocas de informação entre o dispositivo e o CPU e memórias;
- Device driver: Dispositivos que fornecem uma interface de interligação entre o CPU/kernel e dispositivos. Tradução de comandos;
- Dispositivos: podem ser de storage, networking (placas ethernet, wifi, bluethooth), de user interface (teclado, rato, monitor) e outros (sensores, estações meteorológicas, acessórios para jogos).

## 3.2 - Ligação entre dispositivos

A parte que liga o CPU à memória e memória cache é a mais rápida de todo o computador. O microprocessador `north bridge` controla a ligação entre o bus do processador e os dispositivos de entrada e saída, ligado por um Socket. Pode ser do tipo ISA, EISA, SCSI, PCI, PCI Express. Para dispositivos de mais baixa velocidade, existe o `south bridge`. Ao bus de dispositivos de entrada liga-se também um socket PCI Express que se conecta à placa gráfica e/ou ao monitor.

## 3.3 - Interações CPU / Dispositovos

## 3.4 - Polling vs. Interrupts

## 3.5 - DMA (Direct Memory Access)

