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