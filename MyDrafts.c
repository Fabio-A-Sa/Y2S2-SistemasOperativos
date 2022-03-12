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

/* Alguns erros frequentes na utilização de apontadores
 *
 * char *p1 = NULL;
 * char c1 = *p1;               --> O apontador NULL não é válido em runtime
 *
 * char *p2;
 * char c2 = *p2;               --> O apontador não inicializado não é válido em runtime
 *
 * char *p3 = (char*) malloc (sizeof(int));
 * free(p3);
 * char c3 = *p3;               --> O apontador já vazio não é válido em runtime
 */

void swap(int *p1, int *p2) {
    int temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}

int main() {
    int n1 = 1;
    int n2 = 2;
    swap(&n1, &n2);
    printf("n1: %d n2: %d\n", n1, n2);
    return 0;
}

void swap(int n1, int n2) {
    int temp = n1;
    n1 = n2;
    n2 = temp;
}

int main() {
    int n1 = 1;
    int n2 = 2;
    swap(n1, n2);
    printf("n1: %d n2: %d\n", n1, n2);
    return 0;
}

int main() {
    int i;
    char msg[] = "Hello World"; // Cada char é um byte
    for (i = 0; i < sizeof(msg); i++) {
        printf("%c <--> %c\n", msg[i], *(msg + i));
    }
    return 0;
}

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

int* get_int() {
    int* p = (int*)malloc(sizeof(int));
    *p =2;
    return p;
}

int main() {
    int* p = get_int();
    printf("integer = %d\n", *p);
    return 0;
}

int main() {
    printf("Hello World!\n");
    return 0;
}

int main() {
    int i;
    int primes[] = {2, 3, 5, 7, 11}; // cada int tem 4 bytes
    for (i = 0; i < sizeof(primes)/sizeof(int); i++) {
        printf("%d <--> %d\n", primes[i], *(primes + i));
    }
    return 0;
}

