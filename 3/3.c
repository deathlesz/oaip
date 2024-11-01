#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 100

void print_array(int arr[], int length);

int input_array(int arr[], int max_length, bool ascending);
int ask_array_length(int max_length);
int input_method();
void fill_manual(int arr[], int length);
void fill_random(int arr[], int length, int bound);

void sort(int arr[], int length, bool ascending);
void swap(int *a, int *b);

void clear_input();

int main() {
    int arr1[MAX_LENGTH], length1;
    int arr2[MAX_LENGTH], length2;
    int arr3[2 * MAX_LENGTH];

    srand(time(0));

    puts("--- For array #1: ");
    length1 = input_array(arr1, MAX_LENGTH, true);
    puts("\n--- For array #2: ");
    length2 = input_array(arr2, MAX_LENGTH, false);

    int i = length1 - 1;
    int j = 0;
    int k = 0;

    while (i >= 0 && j < length2) {
        if (arr1[i] > arr2[j])
            arr3[k++] = arr1[i--];
        else
            arr3[k++] = arr2[j++];
    }

    while (i >= 0) arr3[k++] = arr1[i--];
    while (j < length2) arr3[k++] = arr2[j++];

    puts("\nResult of merging 2 arrays in descending order:");
    print_array(arr3, length1 + length2);
}

int input_array(int arr[], int max_length, bool is_ascending) {
    int length = ask_array_length(max_length);
    int method = input_method();
    if (method == 1) {
        fill_manual(arr, length);
    } else {
        fill_random(arr, length, 100);
    }

    sort(arr, length, is_ascending);

    puts("\nArray:");
    print_array(arr, length);

    return length;
}

int ask_array_length(int max_length) {
    int size = 0;

    do {
        printf("Enter the number of elements in the array (max %d): ",
               max_length);
        if (scanf("%d", &size) != 1 || size < 1 || size > MAX_LENGTH) {
            printf("Invalid size! Please enter a valid integer between 1 and "
                   "%d.\n\n",
                   max_length);
            clear_input();
        }
    } while (size < 1 || size > max_length);

    return size;
}

int input_method() {
    int method;
    do {
        puts("Choose input method:");
        puts("1. Enter numbers manually");
        puts("2. Fill the array with random numbers");
        printf("Enter your choice (1 or 2): ");
        if (scanf("%d", &method) != 1 || (method != 1 && method != 2)) {
            puts("Invalid choice! Please enter 1 or 2.\n");
            clear_input();
        }
    } while (method != 1 && method != 2);

    return method;
}

void fill_manual(int arr[], int length) {
    printf("\nEnter %d elements:\n", length);
    for (int i = 0; i < length; i++) {
        while (1) {
            printf("Element [%d]: ", i + 1);
            if (scanf("%d", &arr[i]) != 1) {
                puts("Invalid input! Please enter a valid integer.\n");
                clear_input();
            } else
                break;
        }
    }
}

void fill_random(int arr[], int length, int bound) {
    for (int i = 0; i < length; i++) arr[i] = rand() % (2 * bound) - bound;
}

void sort(int arr[], int length, bool ascending) {
    for (int i = 0; i < length; i++)
        for (int j = i; j < length; j++)
            if (ascending && arr[i] > arr[j])
                swap(&arr[i], &arr[j]);
            else if (!ascending && arr[j] > arr[i])
                swap(&arr[i], &arr[j]);
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void print_array(int arr[], int length) {
    printf("[ ");
    for (int i = 0; i < length; i++) printf("%d ", arr[i]);
    printf("]\n");
}

void clear_input() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
