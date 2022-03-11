# 1 - Unix Commands

### Topics:

1. Manipulação de Diretórios
2. Manipulação de Ficheiros
3. Manipulação do conteúdo de Ficheiros
4. Processos
5. Compilação de Programas em C

# Comandos

## 1 - Manipulação de Diretórios

```shell
$ cd | cd ~                // retorna ao root
$ cd ..                    // diretório imediatamente anterior
$ tree dirX                // mostra toda a árvore de diretórios a partir de dirX
$ rm -rf dir1/dir2         // elimina o diretório dir2
```

## 2 - Manipulação de Ficheiros

```shell
$ touch fileName.extension // cria no diretório atual um ficheiro vazio
$ ls -l                    // Para ver os ficheiros e as permissões no diretório atual
$ chmod 755 doit           // muda as permissões do ficheiro (em octal, u-rwx g-r-x o-r-x)
$ chmod u-wx               // muda as permissões do utilizador para -wx (3)
$ chmod go-rx doit         // remove as permissçoes r e x do grupo e others
```

## 3 - Manipulação do conteúdo de Ficheiros

```bash
$ cat > trees.txt                               // cria um ficheiro e permite inputs vários. Terminar com ^D
$ cat trees.txt                                 // mostra o conteúdo de todo o ficheiro
$ cat trees.txt | cut -d ':' -f 1,4             // conteúdo da primeira e quartas colunas quando separadas por ':'
$ cat trees.txt | cut -d ':' -f 1,4 | sort      // além disso, ordena por ordem alfabética as linhas do output
$ cat q1.txt | sed "s/Ring/Sword/g" > q2.txt    // search editor - procura a palavra "Ring" e substitui por "Sword"
                                                // em todo o conteúdo global "g" do ficheiro para q2.txt
$ cat q2.txt | grep Mordor                      // Retorna todas as linhas do ficheiro que contém "Mordor"
$ cat q2.txt | grep -v Mordor                   // Retorna todas as linhas do ficheiro que não contém "Mordor"
$ wc [-l -w -c] q2.txt                          // Retorna o número de linhas, colunas e caracteres do ficheiro
$ sed "s/half/two\ thirds/g" < f1.txt > f2.txt  // Apanha o conteúdo de f1 e retorna f2 com o resultado
$ diff f1.txt f2.txt                            // Mostra as linhas diferentes entre os dois ficheiros
$ sort -n < numbers1.txt > numbers2.txt         // Ordena os números por ordem crescente no ficheiro
$ sort -d < words1.txt > words2.txt             // Ordena as palavras por ordem alfabética no ficheiro
```

## 4 - Processos

````shell
$ ps -A | wc -l                                 // Retorna quantos processos estão ativos no processador
$ ps -A | grep clion                            // Retorna quantos processos de clion estão ativos
$ kill -9 [number]                              // Elimina o processo de número a ver no comando acima
````

## 5 - Compilação de programas em C

````bash
$ gcc -E hello.c                                // Pré-processador de C
$ gcc -S hello.c                                // Gera o código assembly do código
$ gcc hello.c                                   // Compila para um ficheiro a.out
$ gcc -o hello hello.c                          // O ficheiro compilado passa a ter o nome hello
$ gcc -Wall -o hello hello.c                    // Permite ativar todos os warnings da consola
````