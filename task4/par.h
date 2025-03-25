#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <stdbool.h>

const char *valid_elbrus[] = {"1c+", "2c+", "2c3", "4c", "8c", "16c"};

const int amount_elbrus_arg = 6;


struct Options 
{
    int m, c, s, t;
    char **elbrus_values;
    int elbrus_count;
    char **non_options;
    int non_count;
};

int is_valid_elbrus(const char *value) ;

#define error free(opts.elbrus_values);\
              free(opts.non_options);\
              printf("Options are incorrect.\n");\
              return 1