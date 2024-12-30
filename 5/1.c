#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"
#include "vec.h"

void input_matrix(double **vec, int *size, int *capacity);
void fill_randomly(double **vec, int *size, int *capacity);

int main() {
    srand(time(NULL));

    double *vec = malloc(sizeof(double));
    if (!vec)
        exit_oom();

    int size = 0, capacity = 1;

    int method = ask_input_method();
    if (method == 1)
        input_matrix(&vec, &size, &capacity);
    else
        fill_randomly(&vec, &size, &capacity);

    puts("\nArray:");
    vec_print(vec, size);

    for (int i = 0; i < size; i++) {
        if (vec[i] - (int)vec[i] == 0) {
            vec_pop(&vec, &size, i);
            i--;
        }
    }

    puts("\nArray after deleting whole elements:");
    vec_print(vec, size);

    free(vec);
}

void input_matrix(double **array, int *size, int *capacity) {
    char c;
    double d;

    while (1) {
        if (scanf("%lf", &d)) {
            vec_push(array, size, capacity, d);

            continue;
        } else if (scanf("%c", &c) && c == 'q') {
            clear_input();
            if (*size == 0) {
                puts("Enter at least 1 number before stopping.");
                continue;
            }

            break;
        }

        puts("Invalid input! Please enter a valid number or 'q' to stop.");
    }
}

void fill_randomly(double **vec, int *size, int *capacity) {
    int nsize = (rand() % 15) + 1;

    for (int i = 0; i < nsize; i++) {
        double value = ((double)rand() / (double)RAND_MAX) * 200 - 100;
        vec_push(vec, size, capacity, value);
    }
}
