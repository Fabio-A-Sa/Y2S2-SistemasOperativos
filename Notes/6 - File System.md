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

A parte dos ficheiros é dividida em blocos com o mesmo tamanho (parecido com a técnica de paginação), normalmente 4kB. Se o ficheiro tiver tamanho maior que um bloco, há parte do seguinte que é desperdiçado: fragmentação interna, como a paginação.

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

- Tamanho, geralmente em bytes;
- Permissões, em formato RWX. Pode ser modificado com o comando `chmod`;
- Informação de tempo (data de criação, data da última modificação, data do último acesso), desde 1 de janeiro de 1970;
- Dono. Pode ser modificado com o comando `chown`;
- Tipo, o formato do ficheiro;


