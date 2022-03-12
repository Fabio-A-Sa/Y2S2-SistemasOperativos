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

char complex_buf[100];

complex complex_new(double x, double y) {
    complex z;
    z.x = x;
    z.y = y;
    return z;
}

char*  complex_print(complex z) {
    if (z.y == 0)
        sprintf(complex_buf, "%f", z.x);
    else if (z.x == 0)
        sprintf(complex_buf, "%fi", z.y);
    else if (z.y > 0)
        sprintf(complex_buf, "%f+%fi", z.x, z.y);
    else
        sprintf(complex_buf, "%f%fi", z.x, z.y);
    return complex_buf;
}

complex complex_add(complex z, complex w){
    complex r;
    r.x = z.x + w.x;
    r.y = z.y + w.y;
    return r;
}

complex complex_sub(complex z, complex w) {
    complex r;
    r.x = z.x - w.x;
    r.y = z.y - w.y;
    return r;
}

complex complex_mul(complex z, complex w) {
    complex r;
    r.x = z.x * w.x - z.y * w.y;
    r.y = z.x * w.y + z.y * w.x;
    return r;
}

complex complex_div(complex z, complex w) {
    complex r;
    double d = w.x * w.x + w.y * w.y;
    r.x = (z.x * w.x + z.y * w.y) / d;
    r.y = (- z.x * w.y + z.y + w.x) / d;
    return r;
}

complex complex_conj(complex z){
    complex r;
    r.x = z.x;
    r.y = -z.y;
    return r;
}

double  complex_mod(complex z){
    return sqrt(z.x * z.x + z.y * z.y);
}

double  complex_arg(complex z){
    return atan2(z.y, z.x);
}

double  complex_re(complex z){
    return z.x;
}

double  complex_im(complex z){
    return z.y;
}

typedef struct {
    double x;
    double y;
} complex;

/* definition of the complex API */

complex complex_new(double, double);
char*  complex_print(complex);
complex complex_add(complex, complex);
complex complex_sub(complex, complex);
complex complex_mul(complex, complex);
complex complex_div(complex, complex);
complex complex_conj(complex);
double  complex_mod(complex);
double  complex_arg(complex);
double  complex_re(complex);
double  complex_im(complex);

/* implementation of the List API */

node* node_new(int val, node* p) {
    node* q = (node*)malloc(sizeof(node));
    q->val = val;
    q->next = p;
    return q;
}

list* list_new() {
    list* l = (list*) malloc(sizeof(list));
    l->size = 0;
    l->first = NULL;
    return l;
}

list* list_new_random(int size, int range) {
    list* l = list_new();
    int i;
    for(i = 0; i < size; i++)
        list_add_first(rand() % range, l);
    return l;
}

void  list_add_first(int val, list *l) {
    node* p = node_new(val, l->first);
    l->first = p;
    l->size++;
}

void  list_add_last(int val, list *l) {
    node* p = node_new(val, NULL);
    if (l->size == 0) {
        l->first = p;
    }else{
        node* q = l->first;
        while (q->next != NULL)
            q = q->next;
        q->next = p;
    }
    l->size++;
}

int list_get_first(list *l) {
    /* assumes list l is not empty */
    return l->first->val;
}

int list_get_last(list *l) {
    node *q = l->first;
    while (q->next != NULL) {
        q = q->next;
    }
    return q->val;
}

void  list_remove_first(list *l) {
    /* assumes list l is not empty */
    node* p = l->first;
    l->first = l->first->next;
    l->size--;
    /* free memory allocated for node p */
    free(p);
}

void list_remove_last(list *l) {
    node *q = l->first;
    node *qq = q->next;
    while (qq->next != NULL) {
        q = q->next;
        qq = qq->next;
    }
    q->next = NULL;
    free(qq);
    l->size--;
}

int list_size(list *l) {
    return l->size;
}

void list_print(list* l) {
    node *q = l->first;
    while (q->next != NULL) {
        printf("%d ", q->val);
        q = q->next;
    }
    printf("\n");
}

typedef struct {
    int val;
    struct anode* next;
} node;

typedef struct {
    int size;
    node* first;
} list;

/* definition of the list API */

node* node_new(int, node*);
list* list_new();
list* list_new_random(int, int);
void  list_add_first(int, list *);
void  list_add_last(int, list *);
int   list_get_first(list *);
int   list_get_last(list *);
void  list_remove_first(list *);
void  list_remove_last(list *);
int   list_size(list *);
void  list_print(list *);

/* implementation of the matrix API */

matrix* matrix_new(int n, int m) {
    matrix* u = (matrix*) malloc(sizeof(matrix));
    u->n = n;
    u->m = m;
    u->vals = (double*) malloc ((u->n * u->m) * sizeof(double));
    return u;
}

matrix* matrix_new_random(int n, int m, double min, double max) {
    matrix* u = (matrix*) malloc(sizeof(matrix));
    u->n = n;
    u->m = m;
    u->vals = (double*) malloc ((u->n * u->m) * sizeof(double));
    int i, j;
    double range = max - min;
    double div   = RAND_MAX / range;
    for(i = 0; i < u->n; i++)
        for(j = 0; j < u->m; j++)
            matrix_set(i, j, min + (rand() / div), u);
    return u;
}

void matrix_print(matrix* u) {
    for (int i = 0 ; i < u->m ; i++) {
        for (int j = 0 ; j < u->n ; j++) {
            printf("%f ", matrix_get(i, j, u));
        }
        printf("\n");
    }
}

double matrix_get(int i, int j, matrix* u){
    return *(u->vals + i * u->m + j);
}

void matrix_set(int i, int j, double val, matrix* u){
    *(u->vals + i * u->m + j) = val;
}

matrix* matrix_add(matrix* u, matrix* v){
    int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) + matrix_get(i, j, v), w);
    return w;
}

matrix* matrix_sub(matrix* u, matrix* v) {
    int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) - matrix_get(i, j, v), w);
    return w;
}

matrix* matrix_mul(matrix* u, matrix* v){
    int i, j;
    matrix* w = matrix_new(u->n, u->m);
    for (i = 0; i < u->n; i++ )
        for (j = 0; j < u->m; j++ )
            matrix_set(i, j, matrix_get(i, j, u) * matrix_get(i, j, v), w);
    return w;
}

matrix* matrix_trans(matrix* u){
    matrix* m = matrix_new(u->m, u->n);
    for (int i = 0 ; i < u->n ; i++) {
        for (int j = 0 ; j < u->m ; j++) {
            matrix_set(j, i, matrix_get(i, j, u), m);
        }
    }
    return m;
}

typedef struct {
    int n;
    int m;
    double* vals;
} matrix;

/* definition of the matrix API */

matrix* matrix_new(int, int);
matrix* matrix_new_random(int, int, double, double);
void    matrix_print(matrix*);
double  matrix_get(int, int, matrix*);
void    matrix_set(int, int, double, matrix*);
matrix* matrix_add(matrix *, matrix *);
matrix* matrix_sub(matrix *, matrix *);
matrix* matrix_mul(matrix *, matrix *);
matrix* matrix_trans(matrix *);

int main(int argc, char** argv) {

    complex* z1 = complex_new(-2.16793, 5.23394);
    complex* z2 = complex_new( 1.12227, 2.52236);
    complex* z3 = complex_add(z1, z2);
    complex* z4 = complex_sub(z1, z2);
    complex* z5 = complex_mul(z1, z2);
    complex* z6 = complex_div(z1, z2);

    double  x1 = complex_mod(z1);
    double  x2 = complex_re(z1);
    double  x3 = complex_im(z3);

    printf("z1 = %f + %fi\n", z1->x, z1->y);
    printf("z2 = %f + %fi\n", z2->x, z2->y);
    printf("z3 = %f + %fi\n", z3->x, z3->y);
    printf("z4 = %f + %fi\n", z4->x, z4->y);
    printf("z5 = %f + %fi\n", z5->x, z5->y);
    printf("z6 = %f + %fi\n", z6->x, z6->y);
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
    printf("x3 = %f\n", x3);

    return 0;
}

int main(int argc, char** argv) {
    complex z1 = complex_new(-2.16793, 5.23394);
    complex z2 = complex_new( 2.16793, -2.52236);
    complex z3 = complex_add(z1, z2);
    complex z4 = complex_sub(z1, z2);
    complex z5 = complex_mul(z1, z2);
    complex z6 = complex_div(z1, z2);
    double  x1 = complex_mod(z1);
    double  x2 = complex_re(z1);
    double  x3 = complex_im(z3);
    printf("z1 = %s\n", complex_print(z1));
    printf("z2 = %s\n", complex_print(z2));
    printf("z3 = %s\n", complex_print(z3));
    printf("z4 = %s\n", complex_print(z4));
    printf("z5 = %s\n", complex_print(z5));
    printf("z6 = %s\n", complex_print(z6));
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);
    printf("x3 = %f\n", x3);
    return 0;
}

int main(int argc, char** argv) {

    list* l = list_new_random(20, 100);
    list_print(l);

    printf("First: %d\n", list_get_first(l));
    printf("Last: %d\n", list_get_last(l));

    printf("Remove first: ");
    list_remove_first(l); list_print(l);
    printf("Remove last: ");
    list_remove_last(l); list_print(l);

    return 0;
}

int main(int argc, char** argv) {

    matrix *m1 = matrix_new_random(3, 5, 0, 20);
    matrix_print(m1); printf("\n");
    matrix_print(matrix_trans(m1)); printf("\n");

    matrix *m2 = matrix_new_random(3, 5, 0, 20);
    matrix_print(m2); printf("\n");
    matrix_print(matrix_trans(m2)); printf("\n");

    matrix_print(matrix_add(m1, m2)); printf("\n");
    matrix_print(matrix_sub(m1, m2)); printf("\n");
    matrix_print(matrix_mul(m1, m2)); printf("\n");

    return 0;
}

int main(int argc, char** argv) {

    vector* v1 = vector_new(-5.1, 2.3, 3.6);
    vector* v2 = vector_new( 1.6, 7.6, -4.2);
    vector* v3 = vector_add(v1, v2);
    vector* v4 = vector_sub(v1, v2);
    vector* v5 = vector_scale(-9.2, v2);
    vector* v6 = vector_vprod(v1,v2);

    double  x1 = vector_sprod(v1, v2);
    double  x2 = vector_mod(v6);

    printf("v1 = (%f, %f, %f)\n", v1->x, v1->y, v1->z);
    printf("v2 = (%f, %f, %f)\n", v2->x, v2->y, v2->z);
    printf("v3 = (%f, %f, %f)\n", v3->x, v3->y, v3->z);
    printf("v4 = (%f, %f, %f)\n", v4->x, v4->y, v4->z);
    printf("v5 = (%f, %f, %f)\n", v5->x, v5->y, v5->z);
    printf("v6 = (%f, %f, %f)\n", v6->x, v6->y, v6->z);
    printf("x1 = %f\n", x1);
    printf("x2 = %f\n", x2);

    return 0;
}

