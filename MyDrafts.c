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

int main() {
    int i, j, *p, *q;
    i = 5;                      // i = 5
    p = &i;                     // p é a zona de memória onde está i = 5
    *p = 7;                     // na zona de p tem agora 7, logo i = 7
    j = 3;                      // j = 3
    p = &j;                     // p é a zona de memória onde está j = 3
    q = p;                      // q aponta para onde aponta p
    p = &i;                     // p é a zona de memória onde está i = 7
    *q = 2;                     // na zona de p tem agora 2, logo j = 2
    printf("i=%d, j=%d, p=%p, q=%p\n", i, j, p, q);
    return 0;
}

#include <execinfo.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXSYM 32

/*
 * Obtain a backtrace and print it to stdout. Adapted from:
 * https://www.gnu.org/software/libc/manual/html_node/Backtraces.html
 */

void print_trace(char *func) {
    printf("------------ BEGIN (%s) ---------------------\n", func);
    void *array[MAXSYM];
    char **strings;
    int size, i;
    size = backtrace(array, MAXSYM);
    strings = backtrace_symbols(array, size);
    if (strings != NULL) {
        printf("Obtained %d stack frames.\n", size);
        for (i = 0; i < size; i++)
            printf("%s\n", strings[i]);
    }
    free(strings);
    printf("------------ END (%s) ---------------------\n", func);
    return;
}

/* Threaded function calls to show the backtrace */

void f4(void) {
    print_trace("f4");
    return;
}

void f3(void) {
    f4();
    print_trace("f3");
    return;
}

void f2(void) {
    f3();
    print_trace("f2");
    return;
}

void f1(void) {
    f2();
    print_trace("f1");
    return;
}

int main() {
    f1();
    print_trace("main");
    return 0;
}

#include <stdio.h>
#include <math.h>

#define START     0
#define ONE_TURN  360

double cos_table[ONE_TURN];
double sin_table[ONE_TURN];

void build_tables() {
    int i;
    for (i = START; i < ONE_TURN; i++) {
        sin_table[i] = sin(M_PI * i / 180.0);
        cos_table[i] = cos(M_PI * i / 180.0);
    }
}

double sin_degrees(int angle) {
    return sin_table[angle % ONE_TURN];
}

double cos_degrees(int angle) {
    return cos_table[angle % ONE_TURN];
}

int main() {
    build_tables();
    printf("sin(20) = %f\n", sin_degrees(20));
    printf("cos(80) = %f\n", cos_degrees(425));
    printf("tan(60) = %f\n", sin_degrees(60) / cos_degrees(60));
    return 0;
}

/*
 * implementation of the Complex API
*/

complex* complex_new(double x, double y) {
    complex* z = (complex*) malloc(sizeof(complex));
    z->x = x;
    z->y = y;
    return z;
}

complex* complex_add(complex* z, complex* w){
    return complex_new(z->x + w->x, z->y + w->y);
}

complex* complex_sub(complex* z, complex* w){
    return complex_new(z->x - w->x, z->y - w->y);
}

complex* complex_mul(complex* z, complex* w){
    return complex_new(z->x * w->x - z->y * w->y,
                       z->x * w->y + z->y * w->x);
}

complex* complex_div(complex* z, complex* w){
    return complex_new(z->x / w->x - z->y / w->y,
                       z->x / w->y + z->y / w->x);
}

complex* complex_conj(complex* z){
    return complex_new(z->x , z->y);
}

double   complex_mod(complex* z){
    return fabs(z->x);
}

double   complex_arg(complex* z){
    return atan2(z->y,z->x);
}

double   complex_re(complex* z){
    return z->x;
}

double   complex_im(complex* z){
    return z->y;
}

typedef struct {
    double x;
    double y;
} complex;

/* definition of the complex API */

complex* complex_new(double, double);
complex* complex_add(complex *, complex *);
complex* complex_sub(complex *, complex *);
complex* complex_mul(complex *, complex *);
complex* complex_div(complex *, complex *);
complex* complex_conj(complex *);
double complex_mod(complex *);
double complex_arg(complex *);
double complex_re(complex *);
double complex_im(complex *);