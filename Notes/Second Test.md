# Preparação para o segundo teste

## Tópicos:

1. Gestão de memória;
    1. Tradução de endereços;
    2. Espaço de endereçamentos;
2. Gestão de sistemas de ficheiros;
3. Gestão de dispositivos I/O;

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

## 2 - Gestão de sistemas de ficheiros

## 3 - Gestão de dispositivos I/O
