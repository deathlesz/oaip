#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

int get_int_in_bounds(const char *prompt, const int min, const int max);
int ask_input_method();
void input_matrix(double matrix[MAX_SIZE][MAX_SIZE], const int rows,
                  const int columns);
void fill_randomly(double matrix[MAX_SIZE][MAX_SIZE], const int rows,
                   const int columns);
int check_rows(const double matrix[MAX_SIZE][MAX_SIZE], const int rows,
               const int columns);
void print_matrix(const double matrix[MAX_SIZE][MAX_SIZE], const int rows,
                  const int columns);
void zero_array(int arr[], const int size);
void clear_input();

int main() {
    double matrix[MAX_SIZE][MAX_SIZE];

    srand(time(NULL));

    const int rows = get_int_in_bounds(
        "Enter the number of rows in the matrix (%d <= r <= %d): ", 1,
        MAX_SIZE);
    const int columns = get_int_in_bounds(
        "Enter the number of columns in the matrix (%d <= c <= %d): ", 1,
        MAX_SIZE);

    const int method = ask_input_method();
    if (method == 1)
        input_matrix(matrix, rows, columns);
    else
        fill_randomly(matrix, rows, columns);

    puts("\nMatrix:");
    print_matrix(matrix, rows, columns);

    if (check_rows(matrix, rows, columns)) {
        puts("\nAll rows contain at least 1 positive number. Inverted "
             "matrix:");
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++) matrix[i][j] = -matrix[i][j];
        print_matrix(matrix, rows, columns);
    } else
        puts("\nNot all rows contain at least 1 positive number.");
}

int ask_input_method() {
    puts("\nChoose input method:");
    puts("1. Enter numbers manually");
    puts("2. Fill the matrix with random numbers");

    const int method = get_int_in_bounds("Enter your choice (1 or 2): ", 1, 2);

    return method;
}

void input_matrix(double matrix[MAX_SIZE][MAX_SIZE], const int rows,
                  const int columns) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) {
                puts("Invalid input! Please enter your row again.");
                clear_input();

                i--;
                break;
            }
}

void fill_randomly(double matrix[MAX_SIZE][MAX_SIZE], const int rows,
                   const int columns) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[i][j] =
                (rand() / (RAND_MAX + 1.0)) * (2 * MAX_SIZE) - MAX_SIZE;
}

int check_rows(const double matrix[MAX_SIZE][MAX_SIZE], const int rows,
               const int columns) {
    int rows_contain_positive[rows];
    zero_array(rows_contain_positive, rows);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (matrix[i][j] > 0) {
                rows_contain_positive[i] = 1;
                break;
            }

    for (int i = 0; i < rows; i++)
        if (!rows_contain_positive[i])
            return 0;

    return 1;
}

void print_matrix(const double matrix[MAX_SIZE][MAX_SIZE], const int rows,
                  const int columns) {
    int widths[columns];
    zero_array(widths, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            // we're getting the width of the number as if it was printed
            const int width = snprintf(NULL, 0, "%.2lf", matrix[i][j]);
            if (width > widths[j])
                widths[j] = width;
        }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%*.2lf", widths[j] + 1, matrix[i][j]);
        printf("\n");
    }
}

int get_int_in_bounds(const char *prompt, const int min, const int max) {
    int result = 0;

    do {
        printf(prompt, min, max);
        if (scanf("%d", &result) != 1 || (result < min || result > max)) {
            printf("Invalid! Please enter a valid integer between %d and "
                   "%d.\n\n",
                   min, max);
            clear_input();
        }
    } while (result < min || result > max);

    return result;
}

void zero_array(int arr[], const int size) {
    for (int i = 0; i < size; i++) arr[i] = 0;
}

void clear_input() {
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}
