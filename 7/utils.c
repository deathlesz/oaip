#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
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

void input_string(char **string, bool keep_newline) {
    mstrread(string, true);

    char *tmp = NULL;
    mstrread(&tmp, true);

    while (!mstreql(tmp, "\n")) {
        mstrcat(string, tmp);
        mstrread(&tmp, keep_newline);
    }

    free(tmp);
}

void generate_string(char **str, int words_min, int words_max) {
    const char *words[30] = {
        "door ",  "handle ",  "book ",       "laptop ",  "keyboard ",
        "mouse ", "wheel ",   "hello ",      "goodbye ", "ice-cream ",
        "house ", "home ",    "university ", "school ",  "duck ",
        "goose ", "chicken ", "hen ",        "insert ",  "a ",
        "the ",   "at ",      "who ",        "when ",    "why ",
        "where ", "zero ",    "one ",        "two ",     "hammer "};

    if (!*str)
        *str = malloc(1);
    (*str)[0] = '\0';

    int nwords = rand() % (words_max - words_min) + words_min;
    while (nwords--) {
        int word_idx = rand() % 30;

        mstrcat(str, words[word_idx]);
    }
}

bool is_non_letter(char ch) {
    return !((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

void exit_oom() {
    puts("\nIt looks like you're out of memory. Free up some memory and try "
         "again.");

    exit(1);
}
