#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LENGTH 100

void print_array(int arr[], int length);
void clear_input();

int main() {
    int arr[MAX_LENGTH], length;

    srand(time(0));

    do {
        printf("Enter the number of elements in the array (max %d): ",
               MAX_LENGTH);
        if (scanf("%d", &length) != 1 || length < 1 || length > MAX_LENGTH) {
            printf("Invalid size! Please enter a valid integer between 1 and "
                   "%d.\n\n",
                   MAX_LENGTH);
            clear_input();
        }
    } while (length < 1 || length > MAX_LENGTH);

    int choice;
    do {
        puts("Choose input method:");
        puts("1. Enter numbers manually");
        puts("2. Fill the array with random numbers");
        printf("Enter your choice (1 or 2): ");
        if (scanf("%d", &choice) != 1 || (choice != 1 && choice != 2)) {
            puts("Invalid choice! Please enter 1 or 2.\n");
            clear_input();
        }
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        printf("\nEnter %d elements:\n", length);
        for (int i = 0; i < length; i++) {
            while (1) {
                printf("Element [%d]: ", i + 1);
                if (scanf("%d", &arr[i]) != 1) {
                    puts("Invalid input! Please enter a valid number.\n");
                    clear_input();
                } else
                    break;
            }
        }
    } else {
        for (int i = 0; i < length; i++) {
            arr[i] = arr[i] = rand() % (2 * MAX_LENGTH) - MAX_LENGTH;
        }
    }

    puts("\nArray:");
    print_array(arr, length);

    int last_even_idx = -1;
    for (int i = 0; i < length; i++)
        if (arr[i] % 2 == 0)
            last_even_idx = i;

    if (last_even_idx != -1)
        length = last_even_idx + 1;

    puts("\nArray after deleting elements after the last even one:");
    print_array(arr, length);
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
