#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

int get_int_in_bounds(const char *prompt, int min, int max);
int ask_input_method();
void input_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size);
void fill_randomly(double matrix[MAX_SIZE][MAX_SIZE], int size);
void print_matrix(const double matrix[MAX_SIZE][MAX_SIZE], int size);
void zero_array(int arr[], int size);
void clear_input();

int main() {
    double matrix[MAX_SIZE][MAX_SIZE];

    srand(time(NULL));

    int size = get_int_in_bounds(
        "Enter size of the matrix (%d <= s <= %d): ", 1, MAX_SIZE);

    int method = ask_input_method();
    if (method == 1)
        input_matrix(matrix, size);
    else
        fill_randomly(matrix, size);

    puts("\nMatrix:");
    print_matrix(matrix, size);

    int bound = size % 2 == 0 ? size / 2 : (size + 1) / 2;

    double sum = 0;
    for (int i = 0; i < bound; i++)
        for (int j = size / 2; j < size; j++) sum += matrix[i][j];

    printf("\nSum of 2nd quadrant = %.3lf\n", sum);
}

int ask_input_method() {
    puts("\nChoose input method:");
    puts("1. Enter numbers manually");
    puts("2. Fill the matrix with random numbers");

    int method = get_int_in_bounds("Enter your choice (1 or 2): ", 1, 2);

    return method;
}

void input_matrix(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            if (scanf("%lf", &matrix[i][j]) != 1) {
                puts("Invalid input! Please enter your row again.");
                clear_input();

                i--;
                break;
            }
}

void fill_randomly(double matrix[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            matrix[i][j] =
                (rand() / (RAND_MAX + 1.0)) * (2 * MAX_SIZE) - MAX_SIZE;
}

void print_matrix(const double matrix[MAX_SIZE][MAX_SIZE], int size) {
    int widths[size];
    zero_array(widths, size);

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            // we're getting the width of the number as if it was printed
            int width = snprintf(NULL, 0, "%.3lf", matrix[i][j]);
            if (width > widths[j])
                widths[j] = width;
        }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%*.3lf", widths[j] + 1, matrix[i][j]);
        printf("\n");
    }
}

int get_int_in_bounds(const char *prompt, int min, int max) {
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

void zero_array(int arr[], int size) {
    for (int i = 0; i < size; i++) arr[i] = 0;
}

void clear_input() {
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}
