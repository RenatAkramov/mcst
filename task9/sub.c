#include "sub.h"

int main(int argc, char* argv[])
{
    if (argc != 2) // Проверка количества аргументов командной строки
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
    } // Открытие и проверка файла

    int* numbers = NULL; // Массив чисел
    int count = 0;       // Количество чисел
    numbers = read_array(file, &count);

    if (numbers == NULL)
    {
        fprintf(stderr, "Error creating array\n");
    }
    int start   = 0; // Начало максимальной последовательности
    int end     = 0; // Конец  максимальной последовательности
    int max_sum = 0; // Сумма  максимальной последовательности

    find_max_sequence(numbers, count, &start, &end, &max_sum);

    for (int i = start; i < end + 1; i++) // Вывод данных в консоль
    {
        printf("%d ", numbers[i]);
    }
    printf("\n max_sum = %d\n", max_sum);
    return 1;
}

// Считывание данных с файла
int* read_array(FILE* file, int* count) 
{
    int* numbers = NULL; // Массив чисел   
    int num;             // Считываемое число

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

// Нахождение максимальной последовательности
void find_max_sequence(int* arr, int count, int *start, int *end, int* max_sum) 
{
    if (count == 0) // Проверка ситуации если массив пустой
    {
        *start = 0;
        *end = -1; 
        return;
    }

    *max_sum = arr[0];     // Максимальная сумма
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
            if (current_sum > *max_sum) 
            {
                *max_sum = current_sum;
                *start = current_start;
                *end = i - 1;
            }
            // Начинаем новую последовательность с текущего элемента
            current_start = i;
            current_sum = arr[i];
        }
    }

    // Проверяем последнюю последовательность
    if (current_sum > *max_sum) 
    {
        *max_sum = current_sum;
        *start = current_start;
        *end = count - 1;
    }
}