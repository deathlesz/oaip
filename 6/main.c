#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "utils.h"

extern void menu1();
extern void menu2();

int main() {
    while (1) {
        clrscr();

        puts("Choose a task to run (1 or 2)");
        int choice = get_int_in_bounds("> ", 1, 2);

        srand(time(NULL));

        clrscr();
        clear_input();
        switch (choice) {
        case 1:
            menu1();
            break;
        case 2:
            menu2();
            break;
        }

        puts("\nRun another task? (1 - yes, 2 - no)");

        if (get_int_in_bounds("> ", 1, 2) == 2)
            break;
    }
}
