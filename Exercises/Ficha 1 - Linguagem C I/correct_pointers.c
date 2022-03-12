#include <stdio.h>
#include <stdlib.h>

void f() {      // incorrecto. Não inicialização da variável e retorno de uma referência a uma variável temporária.
    int x;
    g(&x);
}

int* f() {      // incorrecto. Não inicialização da variável.
    int x;
    return &x;
}

int* f() {      // correcto. O pointer aloca memória para suportar o que retorna
    int* x = (int*)malloc(sizeof(int));
    return x;
}

int g(int (*h)(int), int y) { // correcto. Argumento de função bem passado.
    return h(y + 2);
}

int f(int x) {
    return x*x;
}

int main() {
    printf("value: %d\n", g(f,2)); // retorna f (2+2) = 4*4 = 16
    return 0;
}