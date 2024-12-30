#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "vec.h"

void vec_push(int **vec, int *length, int *capacity, double value) {
    if (*length == *capacity) {
        int new_capacity = *capacity + 1;
        int *new_vec = realloc(*vec, new_capacity * sizeof(int));

        if (!new_vec) {
            exit_oom();
        }

        *vec = new_vec;
        *capacity = new_capacity;
    }

    (*vec)[(*length)++] = value;
}

void vec_pop(int **vec, int *length, int index) {
    for (int i = index; i < *length - 1; i++) (*vec)[i] = (*vec)[i + 1];

    (*length)--;
    if (*length != 0) {
        int *new_vec = realloc(*vec, *length);

        if (!new_vec) {
            exit_oom();
        }

        *vec = new_vec;
    }
}

void vec_print(const int *vec, int length) {
    printf("[ ");
    for (int i = 0; i < length; i++) { printf("%d ", vec[i]); }
    puts("]");
}
