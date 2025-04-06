#include "matrix_mult.h"

int main() 
{
 
    CHECK_CREATE_ALLOC(matrix1);//Cоздаем массивы матриц
    CHECK_CREATE_ALLOC(matrix2);
    CHECK_CREATE_ALLOC(result);
    
    for (int x = 0; x < SIZE; x++) 
    {
        matrix1[x] = calloc(SIZE, sizeof(int));
        if (matrix1[x] == NULL)
        {
            perror("ERROR: memory not allocated");
            return EXIT_FAILURE;
        }
           
        matrix2[x] = calloc(SIZE, sizeof(int));
        if (matrix2[x] == NULL)
        {
            perror("ERROR: memory not allocated");
            return EXIT_FAILURE;
        }
        
        result[x]  = calloc(SIZE, sizeof(int));
        if (result[x] == NULL)
        {
            perror("ERROR: memory not allocated");
            return EXIT_FAILURE;
        }
    }

    random_nuber(matrix1, matrix2);//Заполняем массивы рандомными числами

    signal(SIGINT, handle_sigint_signal);
    calculate_matrix(matrix1, matrix2, result);

    return 0;
}

//Обработка сигналов 
void handle_sigint_signal()
{
    if (sigint_count == 0) 
    {
        fprintf(stdout,"\nCurrent indices: i=%d, j=%d\n", i, j);
        fflush(stdout);
        signal(SIGINT, SIG_DFL); 
        sigint_count++;
    }
}
//Заполняем массивы рандомными числами
void random_nuber(int** matrix1, int** matrix2)
{
    assert(matrix1);
    assert(matrix2);
    srand(time(NULL));
    for (int x = 0; x < SIZE; x++) 
    {
        for (int y = 0; y < SIZE; y++) 
        {
            matrix1[x][y] = rand() % 100;
            matrix2[x][y] = rand() % 100;
        }
    }
}

//Считаем матрицы
void calculate_matrix(int** matrix1, int** matrix2, int** result)
{
    assert(matrix1);
    assert(matrix2);
    assert(result);
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
}
