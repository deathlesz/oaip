#include <stdio.h>
#include <stdlib.h>

#include "matrix.h"
#include "mstring.h"
#include "utils.h"

void task2(int **matrix, int rows, int *sizes, int *capacities);
void input_matrix(int ***matrix, int *rows, int **sizes, int **capacities);
void fill_matrix_randomly(int ***matrix, int *rows, int **sizes,
                          int **capacities, int rand_min, int rand_max);

int sum_even_in_row(int *row, int size);
void merge(int ***matrix, int size, int begin, int middle, int end, int *sizes);
void merge_sort(int ***matrix, int size, int begin, int end, int *sizes);

void menu2() {
    int input_method = 1;
    int rand_min = -100;
    int rand_max = 100;

    int **matrix;
    int *sizes, *capacities, rows = 1;
    matrix_init(&matrix, &sizes, &capacities);

    int matrix_filled = 0;
    while (1) {
        clrscr();

        puts("+~~~~~~~~~~~~~~~~~+");
        puts("1. Read problem");
        printf("2. Input method [%s]\n",
               input_method == 1 ? "Manually" : "Randomly");
        if (input_method == 2) {
            printf("  2.1. Minimal random value [%d]\n", rand_min);
            printf("  2.2. Maximal random value [%d]\n", rand_max);
        }
        if (input_method == 1)
            printf("3. Input matrix [%c]\n", !matrix_filled ? '-' : '+');
        if (matrix_filled || input_method == 2)
            puts("9. Run\n");
        puts("0. Exit");
        puts("+~~~~~~~~~~~~~~~~~+\n");

        printf("> ");
        char *choice = mstrread();

        if (mstreql(choice, "1")) {
            puts("\nSort rows in matrix NxM in ascending order of sum of even "
                 "elements");
            getchar();
        } else if (mstreql(choice, "2"))
            input_method = input_method == 1 ? 2 : 1;
        else if (mstreql(choice, "2.1") && input_method == 2) {
            printf("> ");
            scanf("%d", &rand_min);
            clear_input();
        } else if (mstreql(choice, "2.2") && input_method == 2) {
            printf("> ");
            scanf("%d", &rand_max);
            clear_input();
        } else if (mstreql(choice, "3") && input_method == 1) {
            puts("\nEnter numbers one by one. \n  Type 's' to finish entering "
                 "a row.\n  Type 'q' to finish entering the matrix.\n");
            input_matrix(&matrix, &rows, &sizes, &capacities);

            matrix_filled = 1;
        } else if (mstreql(choice, "9") &&
                   (matrix_filled || input_method == 2)) {
            if (input_method == 2)
                fill_matrix_randomly(&matrix, &rows, &sizes, &capacities,
                                     rand_min, rand_max);

            task2(matrix, rows, sizes, capacities);

            puts("\nRun again? (1 - yes, 2 - no)");

            if (get_int_in_bounds("> ", 1, 2) == 2) {
                clear_input();
                break;
            }
        } else if (mstreql(choice, "0"))
            return;

        free(choice);
    }
}

void task2(int **matrix, int rows, int *sizes, int *capacities) {
    puts("\nMatrix:");
    matrix_print(matrix, rows, sizes);

    merge_sort(&matrix, rows, 0, rows, sizes);

    puts("\nMatrix after sorting rows in ascending order based on the "
         "sum of even elements:");
    matrix_print(matrix, rows, sizes);

    matrix_free(matrix, sizes, capacities, rows);
}

void input_matrix(int ***matrix, int *rows, int **sizes, int **capacities) {
    char c;
    int d;

    int row = 0;
    while (1) {
        if (scanf("%d", &d))
            matrix_push(matrix, rows, sizes, capacities, row, d);
        else if (scanf("%c", &c)) {
            clear_input();
            if (c == 's') {
                if ((*sizes)[row] == 0) {
                    puts("Enter at least 1 number before finalizing "
                         "the row.");
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

void fill_matrix_randomly(int ***matrix, int *rows, int **sizes,
                          int **capacities, int rand_min, int rand_max) {
    int nrows = rand() % 5 + 3;
    int ncolumns = rand() % 5 + 3;

    for (int i = 0; i < nrows; i++)
        for (int j = 0; j < ncolumns; j++)
            matrix_push(matrix, rows, sizes, capacities, i,
                        rand() % (rand_max - rand_min) + rand_min);
}

int sum_even_in_row(int *row, int size) {
    int sum = 0;

    for (int i = 0; i < size; i++)
        if (row[i] % 2 == 0)
            sum += row[i];

    return sum;
}

void merge(int ***matrix, int size, int begin, int middle, int end,
           int *sizes) {
    int left_size = middle - begin;
    int right_size = end - middle;

    // Add space for temporary rows in `matrix`
    *matrix = realloc(*matrix, (size + left_size + right_size) * sizeof(int *));
    if (!*matrix)
        exit_oom();

    // Use temporary rows for `left` and `right`
    int **left = &(*matrix)[size];
    int **right = &(*matrix)[size + left_size];

    for (int i = 0; i < left_size; i++) left[i] = (*matrix)[begin + i];
    for (int i = 0; i < right_size; i++) right[i] = (*matrix)[middle + i];

    int i = 0, j = 0, k = begin;

    while (i < left_size && j < right_size) {
        if (sum_even_in_row(left[i], sizes[begin + i]) <=
            sum_even_in_row(right[j], sizes[middle + j])) {
            (*matrix)[k++] = left[i++];
        } else {
            (*matrix)[k++] = right[j++];
        }
    }

    while (i < left_size) (*matrix)[k++] = left[i++];
    while (j < right_size) (*matrix)[k++] = right[j++];

    *matrix = realloc(*matrix, size * sizeof(int *));
    if (!*matrix)
        exit_oom();
}

void merge_sort(int ***matrix, int size, int begin, int end, int *sizes) {
    if (end - begin <= 1)
        return;

    int middle = (begin + end) / 2;

    merge_sort(matrix, size, begin, middle, sizes);
    merge_sort(matrix, size, middle, end, sizes);

    merge(matrix, size, begin, middle, end, sizes);
}
