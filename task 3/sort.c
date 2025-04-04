#include "sort.h"


int main(int argc, char *argv[]) 
{
    if (argc != 4) 
    {
        fprintf(stderr, "Использование: %s входной_файл выходной_файл [alph|alph_r|len|len_r]\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *input_filename = argv[1];
    const char *output_filename = argv[2];
    const char *sort_method = argv[3];

    int (*compare)(const void*, const void*);//Выбор компоратора
    if (strcmp(sort_method, "alph") == 0) 
    {
        compare = compare_alph;
    }    
    else if (strcmp(sort_method, "alph_r") == 0)
    {
        compare = compare_alph_d;
    }    
    else if (strcmp(sort_method, "len") == 0) 
    {
        compare = compare_len;
    }
    else if (strcmp(sort_method, "len_r") == 0) 
    {
        compare = compare_len_reverse;
    }    
    else 
    {
        fprintf(stderr, "Неверный метод сортировки!\n");
        return EXIT_FAILURE;
    }


    FILE *input = fopen(input_filename, "r");
    if (!input) 
    {
        perror("Ошибка открытия файла");
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
        char* line_copy = calloc(strlen(line) + 1, sizeof(char));
        if (!line_copy) 
        {
            perror("Ошибка выделения памяти");
            return EXIT_FAILURE;
        }
        strcpy(line_copy, line);        

        lines = realloc(lines, sizeof(char*) * (count + 1));
        if (!lines) 
        {
            perror( "Ошибка выделения памяти");
            return EXIT_FAILURE;
        }

        lines[count++] = line_copy;
    }
    free(line);
    fclose(input);

    qsort(lines, count, sizeof(char*), compare);

 
    FILE *output = fopen(output_filename, "w");
    if (!output) 
    {
        perror("Ошибка создания файла");
        for (size_t i = 0; i < count; i++) 
        {
            free(lines[i]);
        }    
        free(lines);
        return EXIT_FAILURE;
    }

    fprintf(stdin,"Отсортированные строки:\n");
    for (size_t i = 0; i < count; i++) 
    {
        fprintf(output, "%s\n", lines[i]);
        fprintf(stdout, "%s\n", lines[i]);
        free(lines[i]);
    }

    free(lines);
    fclose(output);
    return EXIT_SUCCESS;
}

char get_first_letter(const char *str1, const char *str2)//Выбрать первые две неодинаковые буквы 
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



int is_empty_line(const char *line)//Проверка на пустую строку 
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


int compare_alph(const void *a, const void *b)//Компоратор в алфавитном порядке 
{
    const char *str1 = *(const char **)a;
    const char *str2 = *(const char **)b;

    return get_first_letter(str1, str2);
   
}
int compare_alph_d(const void *a, const void *b)//Компоратор в обратном алфавитном порядке 
{
    return -compare_alph(a, b);
}

int compare_len(const void *a, const void *b)//Компоратор по длине строк от короткой к длинной
{
    size_t len_a = strlen(*(const char **)a);
    size_t len_b = strlen(*(const char **)b);
    return (len_a > len_b) - (len_a < len_b);
}

int compare_len_reverse(const void *a, const void *b)//Компоратор по длине строк от длинной к короткой
{
    return -compare_len(a, b);
}


