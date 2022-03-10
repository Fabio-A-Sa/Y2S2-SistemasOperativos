# 1 - Unix Commands

Topics:

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

```