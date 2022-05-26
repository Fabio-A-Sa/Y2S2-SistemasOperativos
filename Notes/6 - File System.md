# 6 - File System

## Sistemas monolíticos e microkernel

Constituição básica de um computador:
- CPU;
- Memory;
- File system;
- I/O devices;

Em sistemas monolíticos (UNIX, por exemplo), as quatro partes constituem o Kernel. Em sistemas microKernel (MacOS usando Darwin, por exemplo), o Kernel mode contém CPU, Memory e I/O Devices e o User space contém o file system. 

## File System

Composto por ficheiros (data, programs) e uma estrutura de diretórios, pastas, com estruturas de dados capazes de manipular os ficheiros pelos discos de memória. A organização dos ficheiros em sistemas Unix corresponde a uma árvore. Cada nó aponta para a informação colocada em disco e para os subdiretórios. O disco contém estas duas partes: a primeira com os algoritmos e a segunda, que é maior, com os ficheiros.

A parte dos ficheiros é dividida em blocos com o mesmo tamanho (parecido com a técnica de paginação), normalmente 4kB. Se o ficheiro tiver tamanho maior que um bloco, há parte do seguinte que é desperdiçado: fragmentação interna, como a paginação. Um tamanho menor nos blocos por um lado diminui o desperdicio de memória mas aumenta o tempo de busca de todas as porções pelo disco.

## Discos

1. `HDD (Hard Dish Drive)` - Discos rígidos que rodam em torno de um eixo comum, em que há cabeças de leitura por cima e por baixo de cada um que percorrem pistas e secções de memória. 

2. `SSD (Solid State Disk)` - Constuído por partes semicondutoras e imóveis (chips), memórias Flash / NAND memory. Cada um tem uma parte de estruras de dados e outra para os ficheiros.

## Operações com ficheiros

- Criar e Eliminar;
- Abrir/Procurar/Executar e Fechar/Guardar;
- Ler e Escrever;
- Procurar dentro de um ficheiro (procura não sequencial, base de dados por exemplo);

## Tipos de ficheiros

- Multimédia (.jpg, .png, .mp3);
- Documentos (.txt, .pdf, .epub, .docx, .pptx);
- Executáveis (.out, .exe, .app, .sh, .py);
- Bibliotecas (.a, .so, .o, .dll, .dynlib);
- Arquivos (.zip, .tar, .rar, .tgz, .dmg);

Os ficheiros multimédia e as bibliotecas ocupam a maior parte do disco. O sistema de ficheiros deve ser adaptado / construído com base nos ficheiros que vão ser manipulados.

## Constituição de um ficheiro

- Nome. Pode ou não ter extensão;
- Tamanho, geralmente em bytes;
- Permissões, em formato RWX. Pode ser modificado com o comando `chmod`;
- Informação de tempo (data de criação, data da última modificação, data do último acesso), desde 1 de janeiro de 1970;
- Dono. Pode ser modificado com o comando `chown`;
- Tipo, o formato do ficheiro. Não necessariamente de acordo com a extensão;
- Localização dos blocos que contêm a informação do ficheiro;

### File Control Block / Inode

A system call `stat` retorna uma estrutura de dados `struct stat` que contém todas as informações acima.

## Exemplos de File System

- Unix:
    - ufs, Unix File System, o original;
- Linux:
    - ext3;
    - ext4, o mais usado;
    - jfs (journaled file system, como um diário, parecido com o git);
    - reiserfs;
    - xfs, mais para datacenters;
    - zfs, suporta ficheiros enormes;
- macOS:
    - APFS, Apple File System
- Windows
    - NTFS 
    - FAT, File Allocation Table, forma eficiente para localizar ficheiros;
    - FAT3;
    - exFAT;
    - LVM, Logical Volume Memory;
- CD / DVD:
    - ISO 9660;

## Directory Structure

### 1 - Boot Control Block (BCB)

No Unix original, chamava-se Boot Block, no Windows NT (NTFS) chamava-se Partition Boot Section. Contém informação sobre aquele sistema de ficheiros, nomeadamente indicação se aquela parte contém uma imagem do Kernel que seja bootable. Se tiver, então tem de ter também um boot loader, que sabe a localização do Kernel no file system e tem as instruções necessárias para carregá-lo na memória.
No início, o sistema operativo é carregado na memória através da BIOS (Basic I/O System) que descobre quais são os Kernels presentes e transfere o controlo para o boot loader correspondente. Se tiver vários, o GRUB apresenta uma lista dos Kernels disponíveis. 

### 2 - Volume Control Block (VCB)

Contém as estatísticas gerais do file system (o tipo de file system, os bytes por bloco, capacidade máxima, número de blocos, quantos blocos estão a ser usados no momento ou livres, uma estrutura de dados (mapa por exemplo) que contém os endereços/localização dos blocos livres).
No Unix original, chamava-se Super Block, no NTFS (file system do Windows NT) ao conjunto do VCB e Directory Structure chamava-se Master File Tables.

### 3 - Directory Struture (DS)

Conjunto de estruturas de dados e algoritmos que representam a informação de ficheiros individuais e a relação entre eles, ou seja, a sua organização. Uma árvore, por exemplo, com complexidade logarítmica para inserção, remoção e pesquisa, ou DAGS (Directed Acyclic Graphs).
A system call `stat` retorna uma estrutura de dados `struct stat` que contém as informações sobre um ficheiro:
- Tamanho de blocos;
- Datas (de modificação, de última alteração, de execução);
- Owner;
- Permissões (RWX);
- Tipo (ficheiro, diretório, link...);
- Localização do ficheiro (apontadores para os blocos em memória);

## DAGS e Links

Os sistemas operativos na generalidade usam grafos dirigidos e acíclicos para representar as estruturas de ficheiros com base em `links`. Os links podem ser de dois tipos:

### Links simbólicos

Ficheiro que contém o caminho para o programa (atalhos no Desktop em Windows, por exemplo). Em Unix, usar o comando:

```bash
$ ln -s ./usr/fabio/Desktop/game game_shortcut      // para criar
$ ls -l game_shortcut                               // para executar
```

### Hard Links 

Quando há duas referências a apontar para o mesmo ficheiro em duas localizações distintas. Não há cópia. Em Unix, usar o comando:

```bash
$ ln ./usr/fabio/Desktop/game game_hard             // para criar
$ rm game                                           // elimina o link, mas não o ficheiro
$ rm game_hard                                      // elimina o link. Se for o último, remove também o ficheiro
```

## Manipulação de ficheiros pelo sistema operativo

Guarda a informação sobre os ficheiros abertos na memória, os ficheiros que estão a ser usados pelos processo ativos naquele momento. Usa dois tipos de tabela:

### SWOFT - System Wide Open File Table

Tabela que tem uma entrada para cada ficheiro aberto. Cada index tem uma cópia da `struct stat` que guarda as informações gerais de cada ficheiro. Só é guardado no disco quando é mesmo necessário, senão só no fecho do ficheiro.
Só existe uma tabela desta no sistema.

### PPOFT - Per Process Open File Table

Em ficheiros manipulados por mais do que um processo, a informação na tabela SWOFT é insuficiente. Cada processo precisa de guardar a informação específica de como está a usá-los. Por exemplo, pode ter diferentes permissões para abrir os ficheiros, a posição de leitura dos dados.
Cada processo tem uma PPOFT, que guarda as permissões, a posição de leitura e um link/apontador para a entrada de tabela correspondente na SWOFT. As primeiras 3 entradas da PPOFT são:
- 0: stdin;
- 1: stdout;
- 2: stderror;

A chamada `open` do kernel faz com que o sistema operativo descarregue para a memória a informação no disco correspondente ao ficheiro, adicione mais uma entrada na tabela SWOFT e mais uma entrada na PPOFT do processo que chamou a system call.

