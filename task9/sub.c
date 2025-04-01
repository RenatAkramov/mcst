#include "sub.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Invalid file name");
        return 1;
    }
    char* file_name = argv[1]; 
    FILE* file = fopen(file_name, "r");
    if (!file)
    {
        perror("Error opening file");
        return 1;
    }

    int* numbers = NULL;
    int count = 0;    
    numbers = read_array(file, &count);
    if (numbers == NULL)
    {
        fprintf(stderr, "Error creating array\n");
    }
    for (int i = 0; i < count; i++)
    {
        printf("%d\n",numbers[i]);
    }

    int start = 0;  // Начало максимальной последовательности
    int end   = 0;  // Конец максимальной последовательности

    find_max_sequence(numbers, count, &start, &end);

    for (int i = start; i < end + 1; i++)
    {
        printf("%d ", numbers[i]);
    }
    return 1;
}

int* read_array(FILE* file, int* count)
{
    int* numbers = NULL;    
    int num;

    while (fscanf(file, "%d", &num) == 1) 
    {
        int *temp = realloc(numbers, (*count + 1) * sizeof(int));
        if (temp == NULL) 
        {
            perror("Memory allocation error\n");
            free(numbers);
            fclose(file);
            return NULL;
        }
        numbers = temp;
        numbers[(*count)++] = num;
    }    
    return numbers;
}

void find_max_sequence(int* arr, int count, int *start, int *end) 
{
    if (count == 0) // Проверка ситуации если массив пустой
    {
        *start = 0;
        *end = -1; 
        return;
    }

    int max_sum = arr[0];     // Максимальная сумма
    int current_sum = arr[0]; // Текущая сумма
    int current_start = 0;    // Начало текущей последовательности

    for (int i = 1; i < count; ++i) 
    {
        if (arr[i] > arr[i - 1]) 
        {
            current_sum += arr[i];
        } 
        else 
        {
            // Проверяем, является ли текущая последовательность максимальной
            if (current_sum > max_sum) 
            {
                max_sum = current_sum;
                *start = current_start;
                *end = i - 1;
            }
            // Начинаем новую последовательность с текущего элемента
            current_start = i;
            current_sum = arr[i];
        }
    }

    // Проверяем последнюю последовательность
    if (current_sum > max_sum) 
    {
        *start = current_start;
        *end = count - 1;
    }
}