#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <assert.h>

#define SIZE 1000
#define CHECK_CREATE_ALLOC(ptr) \
        int** (ptr) = calloc(SIZE, sizeof(int*));\
        if ((ptr) == NULL) \
        { \
            perror("ERROR: memory not allocated"); \
            return EXIT_FAILURE; \
        } \

#define CHECK_CREATE_ALLOC_(ptr) \
int* (ptr) = calloc(SIZE, sizeof(int*));\
if ((ptr) == NULL) \
{ \
    perror("ERROR: memory not allocated"); \
    return EXIT_FAILURE; \
} \        


volatile sig_atomic_t i = 0;
volatile sig_atomic_t j = 0;
volatile sig_atomic_t sigint_count = 0;

void handle_sigint_signal();
void random_nuber(int** matrix1, int** matrix2);
void calculate_matrix(int** matrix1, int** matrix2, int** result);