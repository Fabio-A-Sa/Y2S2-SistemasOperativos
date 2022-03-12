#include <stdlib.h>
#include <math.h>
#include "vector.h"

vector* vector_new(double x, double y, double z) {
    vector* result = (vector*) malloc (sizeof(vector));
    result->x = x;
    result->y = y;
    result->z = z;
    return result;
}

vector* vector_add(vector* a, vector* b) {
    return vector_new(a->x + b->x, a->y + b->y, a->z + b->z);
}

vector* vector_sub(vector* a, vector* b) {
    return vector_new(a->x - b->x, a->y - b->y, a->z - b->z);
}

vector* vector_scale(double a, vector* b) {
    return vector_new(a * b->x, a * b->y, a * b->z);
}

vector* vector_vprod(vector* a, vector* b) {
    return vector_new(a->x * b->x, a->y * b->y, a->z * b->z);
}

double  vector_sprod(vector* a, vector* b) {
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

double  vector_mod(vector* a) {
    return sqrt(pow(a->x, 2) + pow(a->y, 2) + pow(a->z, 2));
}