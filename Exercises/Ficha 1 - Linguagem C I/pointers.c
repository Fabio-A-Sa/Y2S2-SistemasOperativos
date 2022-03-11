#include <stdio.h>

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