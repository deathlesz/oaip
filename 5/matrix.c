#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "utils.h"
#include "vec.h"

void matrix_init(double ***matrix, int **sizes, int **capacities) {
    double **new_matrix = malloc(sizeof(double *));
    int *new_sizes = malloc(sizeof(int));
    int *new_capacities = malloc(sizeof(int));

    if (!new_matrix || !new_sizes || !new_capacities) {
        exit_oom();
    }

    double *row = malloc(sizeof(double));
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

void matrix_push(double ***matrix, int *rows, int **sizes, int **capacities,
                 int row, double value) {
    if (row >= *rows && (row != 0)) {
        int new_rows = row + 1;

        double **new_matrix = realloc(*matrix, new_rows * sizeof(double *));
        int *new_sizes = realloc(*sizes, new_rows * sizeof(int));
        int *new_capacities =
            (int *)realloc(*capacities, new_rows * sizeof(int));

        if (!new_matrix || !new_sizes || !new_capacities) {
            exit_oom();
        }

        for (int i = *rows; i < new_rows; ++i) {
            double *row = malloc(sizeof(double));
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

void matrix_insert(double ***matrix, int *rows, int **sizes, int **capacities,
                   int row, int column, double value) {
    if (column >= (*sizes)[row])
        return;

    /* double element = (*matrix)[row][column]; */
    /* (*matrix)[row][column] = value; */
    /**/
    /* double temp; */
    /* for (int i = column + 1; i < (*sizes)[row] - 1; i++) { */
    /*     temp = (*matrix)[row][i]; */
    /*     (*matrix)[row][i] = element; */
    /*     element = temp; */
    /* } */

    matrix_push(matrix, rows, sizes, capacities, row, 0);
    for (int i = (*sizes)[row]; i > column; --i) {
        (*matrix)[row][i] = (*matrix)[row][i - 1];
    }
    (*matrix)[row][column] = value;
}

void matrix_remove(double ***matrix, int *sizes, int row, int column) {
    for (int i = column; i < sizes[row] - 1; i++) {
        matrix[row][i] = matrix[row][i + 1];
    }

    sizes[row]--;
    if (sizes[row] != 0) {
        double **new_matrix = realloc(*matrix, sizeof(double *));

        if (!new_matrix)
            exit_oom();

        *matrix = new_matrix;
    }
}

void matrix_print(double **matrix, int rows, int *sizes, const char *fmtc,
                  const char *fmtp) {
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
            int width = snprintf(NULL, 0, fmtc, matrix[i][j]);
            if (width > widths[j])
                widths[j] = width;
        }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < max_size; j++)
            if (j < sizes[i])
                printf(fmtp, widths[j], matrix[i][j]);
        printf("\n");
    }

    free(widths);
}

void matrix_empty_row(double **matrix, int *sizes, int *capacities, int row) {
    free(matrix[row]);

    double *new_row = malloc(sizeof(double));
    if (!new_row) {
        exit_oom();
    }

    matrix[row] = new_row;
    sizes[row] = 0;
    capacities[row] = 1;
}

void matrix_free(double **matrix, int *sizes, int *capacities, int rows) {
    for (int i = 0; i < rows; ++i) { free(matrix[i]); }

    free(matrix);
    free(sizes);
    free(capacities);
}
