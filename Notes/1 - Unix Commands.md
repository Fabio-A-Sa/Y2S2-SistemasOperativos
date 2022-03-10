# 1 - Unix Commands

### Topics:

1. Manipulação de Diretórios
2. Manipulação de Ficheiros
3. Manipulação do conteúdo de Ficheiros

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
$ cat trees.txt | cut -d ':' -f 1,4             // mostra o conteúdo da primeira e quartas colunas quando separadas por ':'
$ cat trees.txt | cut -d ':' -f 1,4 | sort      // além disso, ordena por ordem alfabética as linhas do output
$ cat q1.txt | sed "s/Ring/Sword/g" > q2.txt    // search editor - procura a palavra "Ring" e substitui por "Sword"
                                                // em todo o conteúdo global "g" do ficheiro para q2.txt
```

