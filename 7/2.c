#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
#include "utils.h"

void task2(char ch, char **string1, char *string2);
int split(char *string, char ***words, bool (*splitter)(char));
void generate_string(char **str, int words_min, int words_max);

void menu2() {
    int input_method = 1; // 1 - manually, 2 - randomly
    int words_min = 3;
    int words_max = 10;

    char ch = '\0';
    char *string1 = NULL;
    char *string2 = NULL;

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
            printf("3. Input character [%c]", !ch ? '-' : '+');
            if (ch)
                printf(" : %c\n", ch);
            else
                printf("\n");
            printf("4. Input string S [%c]\n", !string1 ? '-' : '+');
            if (string1)
                puts("  4.1. Print string S");
            printf("5. Input string S0 [%c]\n", !string2 ? '-' : '+');
            if (string2)
                puts("  5.1. Print string S0");
        } else {
            printf("3. Generate inputs [%c]\n",
                   (!ch || !string1 || !string2) ? '-' : '+');
            if (ch && string1 && string2)
                puts("  3.1. Print generated inputs");
        }
        if (ch && string1 && string2)
            puts("9. Run\n");
        puts("0. Exit");
        puts("+~~~~~~~~~~~~~~~~~+\n");

        printf("> ");
        char *choice = NULL;
        mstrread(&choice, false);

        if (mstreql(choice, "1")) {
            puts("\nGiven a character and strings S and S0, delete all the "
                 "words beginning with given character\nin string S if they "
                 "don't exist in string S0");
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
                printf("> ");
                ch = getchar();
            } else {
                generate_string(&string1, words_min, words_max);
                generate_string(&string2, words_min, words_max);
                ch = rand() % 26 + 'a';
            }
        } else if (mstreql(choice, "3.1") && input_method == 2 && ch &&
                   string1 && string2) {
            printf("\nCharacter:\n%c", ch);
            printf("\nString S:\n%s", string1);
            printf("\nString S0:\n%s", string2);
            getchar();
        } else if (mstreql(choice, "4") && input_method == 1)
            input_string(&string1, false);
        else if (mstreql(choice, "4.1") && input_method == 1) {
            printf("\nString S:\n%s", string1);
            getchar();
        } else if (mstreql(choice, "5") && input_method == 1)
            input_string(&string2, true);
        else if (mstreql(choice, "5.1") && input_method == 1) {
            printf("\nString S0:\n%s", string2);
            getchar();
        } else if (mstreql(choice, "9") && ch && string1 && string2) {
            task2(ch, &string1, string2);
            running = 0;
        } else if (mstreql(choice, "0"))
            running = 0;

        free(choice);
    }
}

void task2(char ch, char **string1, char *string2) {
    int length = mstrlen(*string1);
    mstrlwr(string2);

    char **words = malloc(sizeof(char *));
    int nwords = split(string2, &words, is_non_letter);

    int last_separator_idx = 0;
    bool found_or_skipped = false;

    for (int i = 0; (*string1)[i] != '\0'; i++) {
        if (is_non_letter((*string1)[i]) || (*string1)[i + 1] == '\0') {
            int word_length =
                i - last_separator_idx + ((*string1)[i + 1] == '\0' ? 1 : 0);

            if (word_length > 0) {
                while (last_separator_idx < i &&
                       is_non_letter((*string1)[last_separator_idx])) {
                    last_separator_idx++;
                    word_length--;
                }

                if (word_length > 0) {
                    char *word = malloc(word_length + 1);
                    mstrcpy(&((*string1)[last_separator_idx]), word_length,
                            word);
                    mstrlwr(word);

                    if (word[word_length - 1] == '\n') {
                        word[word_length - 1] = '\0';
                    }

                    if (word[0] == ch) {
                        for (int j = 0; j < nwords && !found_or_skipped; j++)
                            if (mstreql(word, words[j]))
                                found_or_skipped = true;

                        if (!found_or_skipped) {
                            int j = last_separator_idx;
                            for (; j < length; j++)
                                (*string1)[j] = (*string1)[j + word_length + 1];

                            length -= (word_length +
                                       ((*string1)[i + 1] == '\0' ? 0 : 1));
                            char *string = realloc(*string1, length + 1);

                            if (!string)
                                exit_oom();

                            *string1 = string;
                            i = last_separator_idx - 1;
                        }
                    }

                    free(word);
                }
            }

            found_or_skipped = false;
            last_separator_idx = i + 1;
        }
    }

    printf("Resulting string: %s", *string1);

    free(*string1);
    free(string2);
}

int split(char *string, char ***words, bool (*splitter)(char)) {
    int last_separtor_idx = 0;
    int word_count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (splitter(string[i])) {
            if (last_separtor_idx != 0)
                last_separtor_idx++;
            int word_length = i - last_separtor_idx;

            if (word_length >= 1) {
                char *word = malloc(word_length + 1);
                mstrcpy(&(string[last_separtor_idx]), word_length, word);

                (*words)[word_count] = word;

                word_count++;
                char **new_words =
                    realloc(*words, (word_count + 1) * sizeof(char *));

                if (!new_words)
                    exit_oom();

                *words = new_words;
            }

            last_separtor_idx = i;
        }
    }

    return word_count;
}
