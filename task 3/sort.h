#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char get_first_letter(const char *str1, const char *str2);
int is_empty_line(const char *line); 
int compare_alph(const void *a, const void *b); 
int compare_alph_d(const void *a, const void *b);
int compare_len(const void *a, const void *b);
int compare_len_reverse(const void *a, const void *b);