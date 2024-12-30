#include <stdio.h>
#include <stdlib.h>

#include "mstring.h"
#include "utils.h"

void task1(char *string);
void generate_string(char **str, int words_min, int words_max);
int split_and_count_words(char *string, char ***words, int **counts,
                          bool (*splitter)(char));
int word_find(char **words, int word_count, char *word);

void menu1() {
    int input_method = 1; // 1 - manually, 2 - randomly
    int words_min = 3;
    int words_max = 10;

    char *string = NULL;

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
            printf("3. Input string [%c]\n", !string ? '-' : '+');
            if (string)
                puts("  3.1. Print input string");
        } else {
            printf("3. Generate string [%c]\n", !string ? '-' : '+');
            if (string)
                puts("  3.1. Print generated string");
        }
        if (string)
            puts("4. Run\n");
        puts("0. Exit");
        puts("+~~~~~~~~~~~~~~~~~+\n");

        printf("> ");
        char *choice = NULL;
        mstrread(&choice, false);

        if (mstreql(choice, "1")) {
            puts("\nGiven a string, find the most frequent word in it.");
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
            if (input_method == 1)
                input_string(&string, true);
            else
                generate_string(&string, words_min, words_max);
        } else if (mstreql(choice, "3.1") && string) {
            printf("\nYour string:\n%s", string);
            getchar();
        } else if (mstreql(choice, "4") && string) {
            task1(string);
            running = 0;
        } else if (mstreql(choice, "0"))
            running = 0;

        free(choice);
    }
}

void task1(char *string) {
    char **words = malloc(sizeof(char *));
    if (!words)
        exit_oom();

    int *counts = malloc(sizeof(int));
    if (!counts)
        exit_oom();

    int word_count =
        split_and_count_words(string, &words, &counts, is_non_letter);

    int idx = 0;
    int count = counts[0];
    int count_eql = 0;
    for (int i = 0; i < word_count; i++)
        if (counts[i] > count) {
            count = counts[i];
            idx = i;
            count_eql = 0;
        } else if (counts[i] == count)
            count_eql++;

    if (count_eql > 1) {
        printf("\nThere're multiple words that appear %d time(-s):\n", count);
        for (int i = 0; i < word_count; i++)
            if (counts[i] == count)
                printf("  %s\n", words[i]);

    } else
        printf("\nMost frequent word is \"%s\", which shows up a total of %d "
               "times\n",
               words[idx], count);

    for (int i = 0; i < word_count; i++) free(words[i]);

    free(words);
    free(counts);
    free(string);
}

int split_and_count_words(char *string, char ***words, int **counts,
                          bool (*splitter)(char)) {
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

                int idx;
                if ((idx = word_find(*words, word_count, word)) == -1) {
                    (*words)[word_count] = word;
                    (*counts)[word_count] = 1;

                    word_count++;
                    char **new_words =
                        realloc(*words, (word_count + 1) * sizeof(char *));
                    int *new_counts =
                        realloc(*counts, (word_count + 1) * sizeof(int));

                    if (!new_words || !new_counts)
                        exit_oom();

                    *words = new_words;
                    *counts = new_counts;
                } else {
                    free(word);
                    (*counts)[idx]++;
                }
            }

            last_separtor_idx = i;
        }
    }

    return word_count;
}

int word_find(char **words, int word_count, char *word) {
    if (!word_count)
        return -1;

    for (int i = 0; i < word_count; i++)
        if (mstreql(words[i], word))
            return i;

    return -1;
}
