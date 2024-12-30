#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix.h"
#include "utils.h"

void input_matrix(double ***matrix, int *rows, int **sizes, int **capacities);
void fill_randomly(double ***matrix, int *rows, int **sizes, int **capacities);

int main() {
    srand(time(NULL));

    double **matrix;
    int *sizes, *capacities, rows = 1;

    matrix_init(&matrix, &sizes, &capacities);

    int method = ask_input_method();
    if (method == 1) {
        puts("\nEnter numbers one by one. \n  Type '-100' to finish entering a "
             "row.\n  Type 'q' to finish entering the matrix.\n");
        input_matrix(&matrix, &rows, &sizes, &capacities);
    } else
        fill_randomly(&matrix, &rows, &sizes, &capacities);

    puts("\nMatrix:");
    matrix_print(matrix, rows, sizes, "%.lf", "%*.lf ");

    for (int i = 1; i < rows; i += 2) {
        for (int j = 0; j < sizes[i]; j++) {
            if ((int)matrix[i][j] % 2 != 0) {
                matrix_insert(&matrix, &rows, &sizes, &capacities, i, j,
                              matrix[i][j]);
                j++;
            }
        }
    }

    puts("\nMatrix after duplicating odd elements in even-numbered rows:");
    matrix_print(matrix, rows, sizes, "%.lf", "%*.lf ");

    matrix_free(matrix, sizes, capacities, rows);
}

void input_matrix(double ***matrix, int *rows, int **sizes, int **capacities) {
    char c;
    int d;

    int row = 0;
    while (1) {
        if (scanf("%d", &d)) {
            if (d == -100) {
                if ((*sizes)[row] == 0) {
                    puts("Enter at least 1 number before finalizing the row.");
                    continue;
                }

                row++;
                continue;
            }

            matrix_push(matrix, rows, sizes, capacities, row, d);
        } else if (scanf("%c", &c)) {
            clear_input();
            if (c == 'q') {
                if (row == 0) {
                    puts("Please enter at least 1 row before finalizing the "
                         "matrix.");
                    continue;
                }

                break;
            } else {
                puts("Invalid input! Please re-enter last row or type 'q' to "
                     "stop.");
                matrix_empty_row(*matrix, *sizes, *capacities, row);
            }
        }
    }
}

void fill_randomly(double ***matrix, int *rows, int **sizes, int **capacities) {
    int nrows = rand() % 5 + 3;

    for (int i = 0; i < nrows; i++) {
        int columns = rand() % 5 + 3;
        for (int j = 0; j < columns; j++) {
            int value = rand() % 200 - 100;

            matrix_push(matrix, rows, sizes, capacities, i, value);
        }
    }
}
