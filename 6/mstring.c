#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
#include "utils.h"

char *mstrread() {
    char *str = malloc(1);
    int length = 0;
    int capacity = 1;

    char c;
    while ((c = getchar()) != '\0' && c != '\n') {
        if (length == capacity) {
            int new_capacity = capacity * 2;

            char *new_string = realloc(str, new_capacity);
            if (!new_string)
                exit_oom();

            str = new_string;
            capacity = new_capacity;
        }

        str[length++] = c;
    }

    char *final_string = realloc(str, length + 1);
    if (!final_string)
        exit_oom();

    final_string[length] = '\0';

    return final_string;
}

int mstreql(const char *str1, const char *str2) {
    int i = 0;
    for (; str1[i] && str2[i] && str1[i] == str2[i]; i++);

    if (!str1[i] && !str2[i])
        return 1;

    return 0;
}

int mstrlen(const char *str) {
    int length = 0;
    for (; str[length] != '\0'; length++);

    return length;
}
