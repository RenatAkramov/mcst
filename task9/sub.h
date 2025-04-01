#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

int* read_array(FILE* file, int* count);
void find_max_sequence(int arr[], int count, int *start, int *end);