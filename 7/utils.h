#pragma once

void clrscr();
int get_int_in_bounds(const char *prompt, int min, int max);
void input_string(char **string, bool keep_newline);
void generate_string(char **str, int words_min, int words_max);
bool is_non_letter(char ch);
void clear_input();
void exit_oom();
