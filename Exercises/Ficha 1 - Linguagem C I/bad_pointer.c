#include <stdio.h>

int* get_int() {
    int i = 2;  // não aloca memória para o inteiro.
    return &i;  // Ao retornar a referência para i nada garante que no final da chamada aquela memória
                // não é ocupada com outra coisa
}

int main() {
    int* p = get_int();
    printf("integer = %d\n", *p);
    return 0;
}