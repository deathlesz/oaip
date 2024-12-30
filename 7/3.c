#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
#include "utils.h"

void task3(char **strings, int length);
void generate_string(char **str, int words_min, int words_max);
void print_array(char **strings, int length);
void merge_sort(char **arr, int left, int right);

void menu3() {
    int input_method = 1; // 1 - manually, 2 - randomly
    int words_min = 3;
    int words_max = 10;

    char **strings = NULL;
    int length = 0;

    int running = 1;
    while (running) {
        clrscr();

        puts("+~~~~~~~~~~~~~~~~~+");
        puts("1. Read problem");
        printf("2. Input method [%s]\n",
               input_method == 1 ? "Manually" : "Randomly");
        if (input_method == 2) {
            printf("  2.1. Minimal # of words [%d]\n", words_min);
            printf("  2.2. Maximal # of words [%d]\n", words_max);
        }
        if (input_method == 1) {
            printf("3. Input array [%c]\n", !strings ? '-' : '+');
            if (strings)
                puts("  3.1. Print array");
        } else {
            printf("3. Generate array [%c]\n", !strings ? '-' : '+');
            if (strings)
                puts("  3.1. Print generated array");
        }
        if (strings)
            puts("4. Run\n");
        puts("0. Exit");
        puts("+~~~~~~~~~~~~~~~~~+\n");

        printf("> ");
        char *choice = NULL;
        mstrread(&choice, false);

        if (mstreql(choice, "1")) {
            puts("\nSort an array of strings in ascending order of number "
                 "of "
                 "words using merge sort.");
            getchar();
        } else if (mstreql(choice, "2"))
            input_method = input_method == 1 ? 2 : 1;
        else if (mstreql(choice, "2.1") && input_method == 2) {
            printf("> ");

            int tmp;
            if (!scanf("%d", &tmp))
                clear_input();

            if (tmp > 0)
                words_min = tmp;

        } else if (mstreql(choice, "2.2") && input_method == 2) {
            printf("> ");

            int tmp;
            if (!scanf("%d", &tmp))
                clear_input();

            if (tmp > 0)
                words_max = tmp;
        } else if (mstreql(choice, "3")) {
            if (input_method == 1) {
                if (!strings)
                    strings = malloc(sizeof(char *));

                char *tmp = NULL;
                mstrread(&tmp, true);
                while (!mstreql(tmp, "\n")) {
                    strings[length++] = tmp;
                    tmp = NULL;
                    mstrread(&tmp, true);
                    strings = realloc(strings, length + 1);
                }
            } else {
                length = rand() % 8 + 3;
                if (!strings)
                    strings = malloc(length * sizeof(char *));
                else
                    strings = realloc(strings, length * sizeof(char *));

                for (int i = 0; i < length; i++)
                    generate_string(&strings[i], words_min, words_max);
            }
        } else if (mstreql(choice, "3.1") && strings) {
            print_array(strings, length);
            getchar();
        } else if (mstreql(choice, "4") && strings) {
            task3(strings, length);
            running = 0;
        } else if (mstreql(choice, "0"))
            running = 0;

        free(choice);
    }
}

void task3(char **strings, int length) {
    char **words = malloc(sizeof(char *));
    if (!words)
        exit_oom();

    int *counts = malloc(sizeof(int));
    if (!counts)
        exit_oom();

    merge_sort(strings, 0, length - 1);
    print_array(strings, length);
}

int count_words(const char *str) {
    int count = 0;
    int in_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (is_non_letter(str[i])) {
            in_word = 0;
        } else if (!in_word) {
            in_word = 1;
            count++;
        }
    }
    return count;
}

void merge(char **arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    char **left_arr = malloc(n1 * sizeof(char *));
    char **right_arr = malloc(n2 * sizeof(char *));

    for (int i = 0; i < n1; i++) { left_arr[i] = arr[left + i]; }
    for (int i = 0; i < n2; i++) { right_arr[i] = arr[mid + 1 + i]; }

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (count_words(left_arr[i]) <= count_words(right_arr[j])) {
            arr[k++] = left_arr[i++];
        } else {
            arr[k++] = right_arr[j++];
        }
    }

    while (i < n1) { arr[k++] = left_arr[i++]; }
    while (j < n2) { arr[k++] = right_arr[j++]; }

    free(left_arr);
    free(right_arr);
}

void merge_sort(char **arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

void print_array(char **strings, int length) {
    printf("Your array: [\n");
    for (int i = 0; i < length; i++) printf("%s\n", strings[i]);
    printf("]\n");
}
