#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#define SIZE 1000

volatile sig_atomic_t i = 0;
volatile sig_atomic_t j = 0;
volatile sig_atomic_t sigint_count = 0;

void handle_sigint_signal() 
{
    if (sigint_count == 0) 
    {
        printf("\nCurrent indices: i=%d, j=%d\n", i, j);
        fflush(stdout);
        signal(SIGINT, SIG_DFL); 
        sigint_count++;
    }
}

int main() 
{
 
    int** matrix1 = calloc(SIZE, sizeof(int*));
    int** matrix2 = calloc(SIZE, sizeof(int*));
    int** result  = calloc(SIZE, sizeof(int*));
    for (int x = 0; x < SIZE; x++) 
    {
        matrix1[x] = calloc(SIZE, sizeof(int));
        matrix2[x] = calloc(SIZE, sizeof(int));
        result[x]  = calloc(SIZE, sizeof(int));
    }

    srand(time(NULL));
    for (int x = 0; x < SIZE; x++) 
    {
        for (int y = 0; y < SIZE; y++) 
        {
            matrix1[x][y] = rand() % 100;
            matrix2[x][y] = rand() % 100;
        }
    }


    signal(SIGINT, handle_sigint_signal);

    
    for (i = 0; i < SIZE; i++) 
    {
        for (j = 0; j < SIZE; j++) 
        {
            for (int k = 0; k < SIZE; k++) 
            {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            sleep(1);
        }
    }


    for (int x = 0; x < SIZE; x++) 
    {
        free(matrix1[x]);
        free(matrix2[x]);
        free(result[x]);
    }
    free(matrix1);
    free(matrix2);
    free(result);

    return 0;
}