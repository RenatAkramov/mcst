#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "sort.h"


int main(int argc, char *argv[]) 
{
    if (argc != 4) 
    {
        fprintf(stderr, "Использование: %s входной_файл выходной_файл [asc|desc|len|len_d]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    const char *sort_method = argv[3];

    int (*compare)(const void*, const void*);
    if (strcmp(sort_method, "asc") == 0) 
    {
        compare = compare_asc;
    }    
    else if (strcmp(sort_method, "desc") == 0)
    {
        compare = compare_desc;
    }    
    else if (strcmp(sort_method, "len") == 0) 
    {
        compare = compare_len_asc;
    }
    else if (strcmp(sort_method, "len_d") == 0) 
    {
        compare = compare_len_desc;
    }    
    else 
    {
        fprintf(stderr, "Неверный метод сортировки!\n");
        return EXIT_FAILURE;
    }


    FILE *input = fopen(input_filename, "r");
    if (!input) 
    {
        fprintf(stderr, "Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    char **lines = NULL;
    size_t count = 0;
    char *line = NULL;
    size_t len = 0;
    size_t read;

    while ((read = getline(&line, &len, input)) != (size_t) -1) 
    {
        if (read > 0 && line[read-1] == '\n') 
        {
            line[read-1] = '\0';
        }
        if (is_empty_line(line)) 
        {
            continue;
        }
        char *line_copy = calloc(strlen(line) + 1, sizeof(char));
        strcpy(line_copy, line);
        

        if (!line_copy) 
        {
            fprintf(stderr,"Ошибка выделения памяти");
            break;
        }

        lines = realloc(lines, sizeof(char*) * (count + 1));
        if (!lines) 
        {
            fprintf(stderr, "Ошибка выделения памяти");
            break;
        }

        lines[count++] = line_copy;
    }
    free(line);
    fclose(input);

    qsort(lines, count, sizeof(char*), compare);

 
    FILE *output = fopen(output_filename, "w");
    if (!output) 
    {
        fprintf(stderr, "Ошибка создания файла");
        for (size_t i = 0; i < count; i++) free(lines[i]);
        free(lines);
        return EXIT_FAILURE;
    }

    printf("Отсортированные строки:\n");
    for (size_t i = 0; i < count; i++) 
    {
        fprintf(output, "%s\n", lines[i]);
        printf("%s\n", lines[i]);
        free(lines[i]);
    }

    free(lines);
    fclose(output);
    return EXIT_SUCCESS;
}

char get_first_letter(const char *str1, const char *str2) 
{
    while (*str1 && *str2) 
    {
        if (isalpha((unsigned char)*str1) && isalpha((unsigned char)*str2))
        {
            if (tolower((unsigned char)*str1) != tolower((unsigned char) *str2))
            {
                return tolower((unsigned char)*str1) - tolower((unsigned char)*str2);
            }
        }
        str1++;
        str2++;
    }
    return 0; 
}



int is_empty_line(const char *line) 
{
    while (*line != '\0') 
    {
        if (!isspace((unsigned char)*line)) 
        {
            return 0;
        }    
        line++;
    }
    return 1;
}


int compare_asc(const void *a, const void *b) 
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    return get_first_letter(str1, str2);
   
}
int compare_desc(const void *a, const void *b) 
{
    return -compare_asc(a, b);
}

int compare_len_asc(const void *a, const void *b) 
{
    size_t len_a = strlen(*(const char **)a);
    size_t len_b = strlen(*(const char **)b);
    return (len_a > len_b) - (len_a < len_b);
}

int compare_len_desc(const void *a, const void *b) 
{
    return -compare_len_asc(a, b);
}


