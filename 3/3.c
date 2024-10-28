#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

int input_array(int arr[], bool is_ascending);
void quick_sort(int arr[], int lo, int hi, bool is_ascending);
int partition(int arr[], int lo, int hi, bool is_ascending);
void clear_input_buffer();

int main() {
    int arr1[MAX_SIZE], size1;
    int arr2[MAX_SIZE], size2;
    int arr3[2 * MAX_SIZE];

    srand(time(0));

    puts("--- For array #1: ");
    size1 = input_array(arr1, true);
    puts("\n--- For array #2: ");
    size2 = input_array(arr2, false);

    int i = size1 - 1;
    int j = 0;
    int k = 0;

    while (i >= 0 && j < size2) {
        if (arr1[i] > arr2[j])
            arr3[k++] = arr1[i--];
        else
            arr3[k++] = arr2[j++];
    }

    while (i >= 0) arr3[k++] = arr1[i--];
    while (j < size2) arr3[k++] = arr2[j++];

    printf("\nArray after merging 2 arrays in descending order:\n[ ");
    for (int i = 0; i < size1 + size2; i++) printf("%d ", arr3[i]);
    printf("]\n");
}

int input_array(int arr[], bool is_ascending) {
    int size;

    do {
        printf("Enter the number of elements in the array (max %d): ",
               MAX_SIZE);
        if (scanf("%d", &size) != 1 || size < 1 || size > MAX_SIZE) {
            printf("Invalid size! Please enter a valid integer between 1 and "
                   "%d.\n\n",
                   MAX_SIZE);
            clear_input_buffer();
        }
    } while (size < 1 || size > MAX_SIZE);

    int choice;
    do {
        printf("Choose input method:\n");
        printf("1. Enter numbers manually\n");
        printf("2. Fill the array with random numbers\n");
        printf("Enter your choice (1 or 2): ");
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            printf("Invalid choice! Please enter 1 or 2.\n\n");
            clear_input_buffer();
        }
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        printf("\nEnter %d elements:\n", size);
        for (int i = 0; i < size; i++) {
            while (1) {
                printf("Element [%d]: ", i + 1);
                if (scanf("%d", &arr[i]) != 1) {
                    printf("Invalid input! Please enter a valid number.\n\n");
                    clear_input_buffer();
                } else
                    break;
            }
        }

        quick_sort(arr, 0, size - 1, is_ascending);
    } else {
        for (int i = 0; i < size; i++)
            arr[i] =
                (int)((rand() / (RAND_MAX + 1.0)) * (2 * MAX_SIZE) - MAX_SIZE);

        quick_sort(arr, 0, size - 1, is_ascending);

        printf("\nArray filled with random numbers: \n[ ");
        for (int i = 0; i < size; i++) printf("%d ", arr[i]);
        printf("]\n");
    }

    return size;
}

void quick_sort(int arr[], int lo, int hi, bool is_ascending) {
    if (lo >= 0 && hi >= 0 && lo < hi) {
        int p = partition(arr, lo, hi, is_ascending);
        quick_sort(arr, lo, p, is_ascending);
        quick_sort(arr, p + 1, hi, is_ascending);
    }
}

int partition(int arr[], int lo, int hi, bool is_ascending) {
    int pivot = arr[lo];

    int i = lo - 1, j = hi + 1;

    int swap;
    while (1) {
        if (is_ascending) {
            do i++;
            while (arr[i] < pivot);

            do j--;
            while (arr[j] > pivot);
        } else {
            do i++;
            while (arr[i] > pivot);

            do j--;
            while (arr[j] < pivot);
        }

        if (i >= j)
            return j;

        swap = arr[i];
        arr[i] = arr[j];
        arr[j] = swap;
    }
}

void clear_input_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
