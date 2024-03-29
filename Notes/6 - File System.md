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

## Localização de ficheiros

Para implementar um file system é importante conhecer:

1. A forma de aceder aos ficheiros:
    - `Modo sequencial`: abrir o ficheiro, ler o ficheiro até ao fim. O mais comum;
    - `Modo random`: como nas bases de dados, com índices internos;

2. A distribuição do tamanho dos ficheiros, através de um histograma;

## Métodos para localizar os blocos dos ficheiros

### 1. Blocos contíguos

Depois de saber o número de blocos necessários para alocar os X bytes do ficheiro (N = math.ceil(X / 4kb)), alocar os blocos seguidos.
Assim é só necessário saber a localização do primeiro bloco e o tamanho do ficheiro. A struct stat só precisa de alocar dois inteiros. 

#### Vantagens

- É uma forma rápida de aceder ao ficheiro em HDDs, porque os sectores a ler são contínuos e estão na mesma pista, a cabeça mecânica praticamente não mexe;
- Bom tanto para acesso sequencial como para acesso random;

#### Desvantagens

- Nem sempre há a quantidade necessária de blocos contínuos para alocar o ficheiro todo, devido à fragmentação externa. Uma solução é a desfragmentação, ou seja, organizar os blocos alocados no início do ficheiro para que os vazios fiquem juntos;
- Mais difícil de encontrar um espaço para alocar todos os blocos do ficheiro. No pior cenário, procurar por todo o disco;
- O aumento do ficheiro, e consequentemente do número de blocos necessários, provoca uma necessidade contínua de alocar outro local da memória e copiar tudo o que estava nas anteriores posições;

### 2. Lista de blocos

A struct stat só guarda um apontador para o primeiro bloco. Cada bloco possui, no final, um apontador para o bloco seguinte. O último poderá apontar para NULL. Semelhante a uma lista ligada.

#### Vantangens

- Necessita apenas de guardar o endereço do primeiro bloco;
- Não há fragmentação externa;
- Fácil de aumentar o tamanho do ficheiro;

#### Desvantagens

- Acesso sequencial não é tão eficiente, em HDDs a cabeça mecânica terá de ser movida;
- Acesso random é comprometido: por ser uma linked list, é necessário fazer sempre uma pesquisa sequencial até encontrar o bloco pretendido;

### 3. Lista de blocos num array 

FAT - File Allocation Table, idealizado pela Microsoft. Os blocos são colocados de forma não sequencial no disco, tal como no caso anterior, mas não existem apontadores. O array, com o mesmo número de blocos do disco, é colocado também no Directory Structure do File System. Em cada posição i do array, colocar a localização do próximo bloco.

#### Vantagens

- A struct stat só precisa de saber o índex do primeiro bloco;
- A informação na lista de blocos é colocada próxima, mais fácil de ler o conteúdo do array; 
- A complexidade temporal da operação é O(n), com n = número de blocos dp fichero;

#### Desvantagens

- Para ser mais rápido, poderia colocar o array na RAM;
- Se o ficheiro for grande, então necessitará de vários blocos e um array também grande;

### 4. Indexed Allotation

Usada originalmente na implementação dos Unix File Systems. Na struct stat (também chamada de inode em sistemas Unix ou FCB - File Control Block), além dos parâmetros habituais há uma zona (com N entradas) que contém apontadores directos para os blocos (não contínuos) usados pelo ficheiro na zona de memória.

- Se o ficheiro não couber em N blocos (tamanho do ficheiro em bytes > 4kb * N), então a posição N da tabela em stat contém um apontador para outra tabela com N entradas. O tamanho do ficheiro poderá ser agora 2N.
- Se o ficheiro não couber em 2N blocos (precisar de mais de 2N entradas para apontadores), então a posição N + 1 da tabela stat contém um apontador para uma tabela que tem N apontadores para tabelas de N entradas. O tamanho do ficheiro poderá ser agora N^2 + 2N.
- Se o ficheiro não couber em N^2 + 2N blocos (precisar de mais de 2N + N^2 entradas para apontadores), então a posição N + 2 da tabela stat contém um apontador para uma tabela que tem N apontadores para tabelas que contém N entradas que contém apontadores para tabelas de N entradas. O tamanho do ficheiro poderá ser agora N^3 + N^2 + 2N. Este é o máximo tamanho que um ficheiro poderá ter.

#### Vantagens

- Para ficheiros pequenos a complexidade de aceder a um bloco é O(1) pois o apontador é direto;
- Se o tamanho do ficheiro for grande, é só criar tabelas extra de N elementos;
- As tabelas são normalmente copiadas também para memória, o que garante melhor performence;

#### Desvantagens

- Consumo de espaço extra para as tabelas;