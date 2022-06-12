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
3. Gestão de dispositivos I/O;

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

Para resguardar os ficheiros, temos Hard Disk Drive e Solid State Disks (com memórias Flash / NAND, constituido por partes semicondutoras e imóveis - os chips).

O File System é constituído por ficheiros e uma estrutura de dados e algoritmos (árvore, uma DAG). Cada nó aponta para um ficheiro colocado em disco. Unix (ufs, Unix File System), Linux (ext3, ext4, jfs, reiserfs, xfs, zfs, suporta ficheiros enormes), macOS (APFS, apple file system), Windows (NTFS, FAT File Alocator Table, FAT3, exFAT, LVM, logical volume memory), CD/DVD (ISO 9660).

## 2.3 - Ficheiros

Os ficheiros (multimédia, documentos, executáveis, bibliotecas, arquivos) podem ser manipulados (criar, elimiar, abrir, procura sequencial ou não, ler, escrever, fechar, guardar) e são constituidos, de acordo com a *struct stat* em nome, tamanho, permissões, dono, tempo (datas de modificação, criação, execução), tipo, e a localização dos blocos que contém a informação do ficheiro. 

## 2.4 - Directory Structure

Constituido por 3 partes principais:

### 2.4.1 - Boot Control Block (BCB)



### 2.4.2 - Volume Control Block (VCB)



### 2.4.3 - Directory Structure (DS)



## 3 - Gestão de dispositivos I/O
