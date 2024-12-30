#pragma once

void matrix_init(int ***matrix, int **sizes, int **capacities);
void matrix_push(int ***matrix, int *rows, int **sizes, int **capacities,
                 int row, int value);
void matrix_print(int **matrix, int rows, int *sizes);
void matrix_empty_row(int **matrix, int *sizes, int *capacities, int row);
void matrix_free(int **matrix, int *sizes, int *capacities, int rows);
