#include "par_copy.h"

int main(int argc, char* argv[]) 
{
    if (argc != 2)//Проверка на наличие название файла 
    {
        fprintf(stderr, "Please, enter correct name of file\n");
        return EXIT_FAILURE;
    }
    
    FILE* input = fopen(argv[1], "r");//Открытие файла и обработка ошибок
    if (!input) 
    {
        perror("ERROR: memory not allocated");
        return EXIT_FAILURE;
    }

    char** lines = NULL;
    size_t count = 0;
    char* line = NULL;
    size_t len = 0;
    int read;

    while ((read = getline(&line, &len, input)) != -1)//Запись строк из файла в массив 
    {
        if (read > 0 && line[read-1] == '\n') 
        {
            line[read-1] = '\0';
        }
        char* line_copy = strdup(line);
        if (!line_copy) 
        {
            perror("ERROR: memory not allocated");
            return EXIT_FAILURE;
        }
        lines = realloc(lines, sizeof(char*) * (count + 1));
        if (!lines) 
        {
            perror("ERROR: memory not allocated");
            return EXIT_FAILURE;
        }
        lines[count++] = line_copy;
    }
    free(line);
    fclose(input);

    pid_t pid = fork();//Рождение дочернего процесса
    if (pid == -1) 
    {
        perror("ERROR: fork failed");
        return EXIT_FAILURE;
    }

    char* output_file;
    if (pid == 0)//Выбор файла в зависимости от процесса 
    {
        output_file = "child_file.txt";
    } 
    else 
    {
        output_file = "parents_file.txt";
    }

    FILE* file_out = fopen(output_file, "w");//Открытие выходного файла и обработка ошибок
    if (!file_out) 
    {
        perror("ERROR: doesn't open file_out");
        for (size_t i = 0; i < count; i++)
        {
            free(lines[i]);
        }
        free(lines);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < count; i++)//Запись данных в файл 
    {
        fprintf(file_out, "%s\n", lines[i]);
    }
    fclose(file_out);

    for (size_t i = 0; i < count; i++)
    {
        free(lines[i]);
    }    
    free(lines);

    if (pid == 0)//Вывод дочернего процесса 
    {
        int result = print_after_file(output_file, pid);
        if(result == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    } 
    else//Вывод родительского процесса 
    {
        int status;
        waitpid(pid, &status, 0);
        int result = print_after_file(output_file, pid);
        if(result == EXIT_FAILURE)
        {
            return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
    }
}

//Вывод в командную строку данных из созданных файлов
int print_after_file(char* output_file, pid_t pid)
{
    FILE* file_out = fopen(output_file, "r");
    int read = -1;
    if (!file_out)
    {
        perror("ERROR:  doesn't open file_out");
        return EXIT_FAILURE;
    }
    if (pid == 0)
    {
        fprintf(stdout,"child:\n-----------------\n");
    }
    else
    {
        fprintf(stdout,"parent:\n----------------\n");
    }
    char* line = NULL;
    size_t len = 0;
    while ((read = getline(&line, &len, file_out)) != -1) 
    {
        fprintf(stdout,"%s",line);
    }
    fprintf(stdout,"----------------\n");
    return EXIT_SUCCESS;
}
   
    
    