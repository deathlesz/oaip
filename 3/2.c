#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

void clear_input_buffer();

int main() {
    int arr[MAX_SIZE], size;

    srand(time(0));

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
    } else {
        printf("\nArray filled with random numbers: \n[ ");
        for (int i = 0; i < size; i++) {
            arr[i] =
                (int)((rand() / (RAND_MAX + 1.0)) * (2 * MAX_SIZE) - MAX_SIZE);
            printf("%d ", arr[i]);
        }
        printf("]\n");
    }

    int last_even_idx = -1;
    for (int i = 0; i < size; i++)
        if (arr[i] % 2 == 0)
            last_even_idx = i;

    if (last_even_idx != -1)
        size = last_even_idx + 1;

    printf("\nArray after deleting elements after the last even one:\n[ ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    printf("]\n");
}

void clear_input_buffer() {
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}
