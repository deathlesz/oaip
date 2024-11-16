#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

int get_int_in_bounds(const char *prompt, const int min, const int max);
int ask_input_method();
void input_matrix(int matrix[MAX_SIZE][MAX_SIZE], const int columns,
                  const int rows);
void fill_randomly(int matrix[MAX_SIZE][MAX_SIZE], const int columns,
                   const int rows);
int characteristic(int column[], const int size);
void print_matrix(const int matrix[MAX_SIZE][MAX_SIZE], const int columns,
                  const int rows);
void zero_array(int arr[], const int size);
void swap_arrays(int a[], int b[], int size);
void swap(int *a, int *b);
void clear_input();

int main() {
    int matrix[MAX_SIZE][MAX_SIZE];

    srand(time(NULL));

    const int rows = get_int_in_bounds(
        "Enter the number of rows in the matrix (%d <= r <= %d): ", 1,
        MAX_SIZE);
    const int columns = get_int_in_bounds(
        "Enter the number of columns in the matrix (%d <= c <= %d): ", 1,
        MAX_SIZE);

    const int method = ask_input_method();
    if (method == 1)
        input_matrix(matrix, columns, rows);
    else
        fill_randomly(matrix, columns, rows);

    puts("\nMatrix:");
    print_matrix(matrix, columns, rows);

    int characteristics[columns];
    for (int i = 0; i < columns; i++)
        characteristics[i] = characteristic(matrix[i], rows);

    int has_negative_elements[columns];
    zero_array(has_negative_elements, columns);

    for (int i = 0; i < columns; i++) {
        for (int j = i; j < columns; j++)
            if (characteristics[i] > characteristics[j]) {
                swap(&characteristics[i], &characteristics[j]);
                swap_arrays(matrix[i], matrix[j], rows);
            }

        for (int j = 0; j < rows; j++)
            if (matrix[i][j] < 0) {
                has_negative_elements[i] = 1;
                break;
            }
    }

    printf("\nMatrix after sorting columns in order of ascending "
           "characteristics:\n");
    print_matrix(matrix, columns, rows);

    printf("\nSum of elements in columns with at least 1 negative number:\n");
    for (int i = 0; i < columns; i++) {
        int sum = 0;
        if (has_negative_elements[i]) {
            for (int j = 0; j < rows; j++) sum += matrix[i][j];
            printf("   Column #%d: %d\n", i + 1, sum);
        }
    }
}

int ask_input_method() {
    puts("\nChoose input method:");
    puts("1. Enter numbers manually");
    puts("2. Fill the matrix with random numbers");

    const int method = get_int_in_bounds("Enter your choice (1 or 2): ", 1, 2);

    return method;
}

void input_matrix(int matrix[MAX_SIZE][MAX_SIZE], const int columns,
                  const int rows) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            if (scanf("%d", &matrix[j][i]) != 1) {
                puts("Invalid input! Please enter your row again.");
                clear_input();

                i--;
                break;
            }
}

void fill_randomly(int matrix[MAX_SIZE][MAX_SIZE], const int columns,
                   const int rows) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            matrix[j][i] = rand() % (2 * MAX_SIZE) - MAX_SIZE;
}

int characteristic(int column[], const int size) {
    int sum = 0;
    for (int i = 0; i < size; i++)
        if (column[i] < 0 && column[i] % 2)
            sum += -column[i];

    return sum;
}

void print_matrix(const int matrix[MAX_SIZE][MAX_SIZE], const int columns,
                  const int rows) {
    int widths[columns];
    zero_array(widths, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            // we're getting the width of the number as if it was printed
            const int width = snprintf(NULL, 0, "%d", matrix[j][i]);
            if (width > widths[j])
                widths[j] = width;
        }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%*d", widths[j] + 1, matrix[j][i]);
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

void swap_arrays(int a[], int b[], int size) {
    do swap(&a[size], &b[size]);
    while (size--);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void clear_input() {
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}
