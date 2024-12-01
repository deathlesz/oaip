#pragma once

void matrix_init(double ***matrix, int **sizes, int **capacities);
void matrix_push(double ***matrix, int *rows, int **sizes, int **capacities,
                 int row, double value);
void matrix_insert(double ***matrix, int *rows, int **sizes, int **capacities,
                   int row, int column, double value);
void matrix_remove(double **matrix, int *sizes, int row, int column);
void matrix_print(double **matrix, int rows, int *sizes, const char *fmtc,
                  const char *fmtp);
void matrix_empty_row(double **matrix, int *sizes, int *capacities, int row);
void matrix_free(double **matrix, int *sizes, int *capacities, int rows);
