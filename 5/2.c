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
        puts("\nEnter numbers one by one. \n  Type 's' to finish entering a "
             "row.\n  Type 'q' to finish entering the matrix.\n");
        input_matrix(&matrix, &rows, &sizes, &capacities);
    } else
        fill_randomly(&matrix, &rows, &sizes, &capacities);

    puts("\nMatrix:");
    matrix_print(matrix, rows, sizes, "%.2lf", "%*.2lf ");

    for (int i = 0; i < rows; i++) {
        if (i < sizes[i])
            matrix_remove(&matrix, sizes, i, sizes[i] - i - 1);
    }

    puts("\nMatrix after deleting elements on antidiagonal:");
    matrix_print(matrix, rows, sizes, "%.2lf", "%*.2lf ");

    matrix_free(matrix, sizes, capacities, rows);
}

void input_matrix(double ***matrix, int *rows, int **sizes, int **capacities) {
    char c;
    double d;

    int row = 0;
    while (1) {
        if (scanf("%lf", &d))
            matrix_push(matrix, rows, sizes, capacities, row, d);
        else if (scanf("%c", &c)) {
            clear_input();
            if (c == 's') {
                if ((*sizes)[row] == 0) {
                    puts("Enter at least 1 number before finalizing the row.");
                    continue;
                } else if (row != 0 && (*sizes)[row] != (*sizes)[row - 1]) {
                    printf("Please enter %d elements in a row.\n",
                           (*sizes)[row - 1]);
                    matrix_empty_row(*matrix, *sizes, *capacities, row);
                    continue;
                }

                row++;
            } else if (c == 'q') {
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
    int columns = rand() % 5 + 3;

    for (int i = 0; i < nrows; i++) {
        for (int j = 0; j < columns; j++) {
            double value = ((double)rand() / (double)RAND_MAX) * 200 - 100;

            matrix_push(matrix, rows, sizes, capacities, i, value);
        }
    }
}
