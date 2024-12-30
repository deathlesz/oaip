#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "vec.h"

void vec_push(double **vec, int *length, int *capacity, double value) {
    if (*length == *capacity) {
        int new_capacity = *capacity * 2;
        double *new_vec = realloc(*vec, new_capacity * sizeof(double));

        if (!new_vec) {
            exit_oom();
        }

        *vec = new_vec;
        *capacity = new_capacity;
    }

    (*vec)[(*length)++] = value;
}

void vec_pop(double **vector, int *length, int index) {
    for (int i = index; i < *length - 1; i++) (*vector)[i] = (*vector)[i + 1];

    (*length)--;
    if (*length != 0) {
        double *new_vec = realloc(*vector, *length);

        if (!new_vec) {
            exit_oom();
        }

        *vector = new_vec;
    }
}

void vec_print(const double *vector, int length) {
    printf("[ ");
    for (int i = 0; i < length; i++) { printf("%lf ", vector[i]); }
    puts("]");
}
