#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "utils.h"
#include "vec.h"

void matrix_init(int ***matrix, int **sizes, int **capacities) {
    int **new_matrix = malloc(sizeof(int *));
    int *new_sizes = malloc(sizeof(int));
    int *new_capacities = malloc(sizeof(int));

    if (!new_matrix || !new_sizes || !new_capacities) {
        exit_oom();
    }

    int *row = malloc(sizeof(int));
    if (!row) {
        exit_oom();
    }

    new_matrix[0] = row;
    new_sizes[0] = 0;
    new_capacities[0] = 1;

    *matrix = new_matrix;
    *sizes = new_sizes;
    *capacities = new_capacities;
}

void matrix_push(int ***matrix, int *rows, int **sizes, int **capacities,
                 int row, int value) {
    if (row >= *rows && (row != 0)) {
        int new_rows = row + 1;

        int **new_matrix = realloc(*matrix, new_rows * sizeof(int *));
        int *new_sizes = realloc(*sizes, new_rows * sizeof(int));
        int *new_capacities =
            (int *)realloc(*capacities, new_rows * sizeof(int));

        if (!new_matrix || !new_sizes || !new_capacities) {
            exit_oom();
        }

        for (int i = *rows; i < new_rows; ++i) {
            int *row = malloc(sizeof(int));
            if (!row) {
                exit_oom();
            }

            new_matrix[i] = row;
            new_sizes[i] = 0;
            new_capacities[i] = 1;
        }

        *matrix = new_matrix;
        *sizes = new_sizes;
        *capacities = new_capacities;
        *rows = new_rows;
    }

    vec_push(&(*matrix)[row], &(*sizes)[row], &(*capacities)[row], value);
}

void matrix_print(int **matrix, int rows, int *sizes) {
    int max_size = 0;
    for (int i = 0; i < rows; i++)
        if (sizes[i] > max_size)
            max_size = sizes[i];

    int *widths = calloc(max_size, sizeof(int));
    if (!widths) {
        exit_oom();
    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < sizes[i]; j++) {
            int width = snprintf(NULL, 0, "%d", matrix[i][j]);
            if (width > widths[j])
                widths[j] = width;
        }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < max_size; j++)
            if (j < sizes[i])
                printf("%*d ", widths[j], matrix[i][j]);
        printf("\n");
    }

    free(widths);
}

void matrix_empty_row(int **matrix, int *sizes, int *capacities, int row) {
    free(matrix[row]);

    int *new_row = malloc(sizeof(int));
    if (!new_row) {
        exit_oom();
    }

    matrix[row] = new_row;
    sizes[row] = 0;
    capacities[row] = 1;
}

void matrix_free(int **matrix, int *sizes, int *capacities, int rows) {
    for (int i = 0; i < rows; ++i) { free(matrix[i]); }

    free(matrix);
    free(sizes);
    free(capacities);
}
