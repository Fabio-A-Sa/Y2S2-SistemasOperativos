#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

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