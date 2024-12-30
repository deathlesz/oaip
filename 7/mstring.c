#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
#include "utils.h"

void mstrread(char **str, bool include_newstr) {
    if (!*str)
        *str = malloc(1);
    int length = 0;
    int capacity = 1;

    char c;
    while ((c = getchar()) != '\0') {
        if (!include_newstr && c == '\n')
            break;

        if (length == capacity) {
            int new_capacity = capacity + 1;

            char *new_string = realloc(*str, new_capacity);
            if (!new_string)
                exit_oom();

            *str = new_string;
            capacity = new_capacity;
        }

        (*str)[length++] = c;

        if (c == '\n')
            break;
    }

    char *final_string = realloc(*str, length + 1);
    if (!final_string)
        exit_oom();

    *str = final_string;
    (*str)[length] = '\0';
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

void mstrlwr(char *str) {
    for (int i = 0; str[i] != '\0'; i++)
        if (str[i] >= 'A' && str[i] <= 'Z')
            str[i] += 'a' - 'A';
}

void mstrcat(char **dst, const char *src) {
    int dst_length = mstrlen(*dst);
    int src_length = mstrlen(src);

    int length = dst_length + src_length + 1;
    char *new_dst = realloc(*dst, length);
    if (!new_dst)
        exit_oom();

    *dst = new_dst;

    for (int i = 0; src[i] != '\0'; i++) (*dst)[dst_length + i] = src[i];
    (*dst)[length - 1] = '\0';
}

void mstrcpy(const char *src, int bytes, char *dst) {
    for (int i = 0; i < bytes; i++) {
        /* printf("src[%d] = %c (%d)\n", i, src[i], src[i]); */
        dst[i] = src[i];
        /* printf("dst[%d] = %c (%d)\n", i, dst[i], dst[i]); */
    }
    dst[bytes] = '\0';
}
