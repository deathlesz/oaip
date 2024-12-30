#pragma once

#include <stdbool.h>

void mstrread(char **str, bool include_newstr);
int mstreql(const char *str1, const char *str2);
int mstrlen(const char *str);
void mstrlwr(char *str);
void mstrcat(char **dst, const char *src);
void mstrcpy(const char *src, int bytes, char *dst);
