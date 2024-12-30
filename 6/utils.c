#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void clrscr() {
    if (system("clear"))
        system("cls");
}

int get_int_in_bounds(const char *prompt, const int min, const int max) {
    int result = 0;

    do {
        printf(prompt, min, max);
        if (scanf("%d", &result) != 1 || (result < min || result > max)) {
            printf(
                "Invalid! Please enter a valid integer between %d and %d.\n\n",
                min, max);
            clear_input();
        }
    } while (result < min || result > max);

    return result;
}

void clear_input() {
    char c;

    while ((c = getchar()) != '\n' && c != EOF);
}

void exit_oom() {
    puts("\nIt looks like you're out of memory. Free up some memory and try "
         "again.");

    exit(1);
}
