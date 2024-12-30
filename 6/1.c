#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
#include "utils.h"
#include "vec.h"

void task1(int *vec, int size, int capacity);
void input_array(int **vec, int *size, int *capacity);
void fill_array_randomly(int **vec, int *size, int *capacity, int rand_min,
                         int rand_max);
void selection_sort(int *vec, int size);

void menu1() {
    int input_method = 1;
    int rand_min = -100;
    int rand_max = 100;

    int *vec = malloc(sizeof(int));
    if (!vec)
        exit_oom();

    int size = 0, capacity = 1;

    int vec_filled = 0;
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
            printf("3. Input array [%c]\n", !vec_filled ? '-' : '+');
        if (vec_filled || input_method == 2)
            puts("9. Run\n");
        puts("0. Exit");
        puts("+~~~~~~~~~~~~~~~~~+\n");

        printf("> ");
        char *choice = mstrread();

        if (mstreql(choice, "1")) {
            puts("\nSort elements in ascending order using selection sort.");
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
            puts("\nEnter numbers one by one.\n  Type 'q' to finish "
                 "entering "
                 "the array.\n");
            input_array(&vec, &size, &capacity);

            vec_filled = 1;
        } else if (mstreql(choice, "9") && (vec_filled || input_method == 2)) {
            if (input_method == 2)
                fill_array_randomly(&vec, &size, &capacity, rand_min, rand_max);

            task1(vec, size, capacity);

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

void task1(int *vec, int size, int capacity) {
    puts("\nArray:");
    vec_print(vec, size);

    selection_sort(vec, size);

    puts("\nArray after sorting even elements:");
    vec_print(vec, size);

    free(vec);
}

void input_array(int **array, int *size, int *capacity) {
    char c;
    int d;

    while (1) {
        if (scanf("%d", &d)) {
            vec_push(array, size, capacity, d);

            continue;
        } else if (scanf("%c", &c) && c == 'q') {
            clear_input();
            if (*size == 0) {
                puts("Enter at least 1 number before stopping.");
                continue;
            }

            break;
        }

        puts("Invalid input! Please enter a valid number or 'q' to stop.");
        clear_input();
    }
}

void fill_array_randomly(int **vec, int *size, int *capacity, int rand_min,
                         int rand_max) {
    int nsize = rand() % 10 + 5;

    for (int i = 0; i < nsize; i++)
        vec_push(vec, size, capacity,
                 rand() % (rand_max - rand_min) + rand_min);
}

void selection_sort(int *vec, int size) {
    int temp;
    for (int i = 0; i < size - 1; i++)
        for (int j = i + 1; j < size; j++)
            if (vec[i] > vec[j] && vec[i] % 2 == 0 && vec[j] % 2 == 0) {
                temp = vec[i];
                vec[i] = vec[j];
                vec[j] = temp;
            }
}
