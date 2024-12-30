#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mstring.h"
#include "utils.h"

extern void menu1();
extern void menu2();
extern void menu3();

int main() {
    while (1) {
        clrscr();

        puts("Choose a task to run (1 - 3)");
        int choice = get_int_in_bounds("> ", 1, 3);

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
        case 3:
            menu3();
            break;
        }

        int running = 1;
        while (running) {
            printf("\nRun another task? (yes/no): ");

            char *choice2 = NULL;
            mstrread(&choice2, false);
            mstrlwr(choice2);
            if (mstreql(choice2, "n") || mstreql(choice2, "no")) {
                free(choice2);
                exit(0);
            } else if (mstreql(choice2, "y") || mstreql(choice2, "yes")) {
                running = 0;
            }

            free(choice2);
        }
    }
}
