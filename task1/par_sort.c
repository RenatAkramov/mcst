#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Please, enter correct name of file\n");
        return EXIT_FAILURE;
    }
    
    FILE* input = fopen(argv[1], "r");
    if (!input) 
    {
        perror("Ошибка открытия файла");
        return EXIT_FAILURE;
    }

    pid_t pid = fork();
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
    fclose(input);
    if(pid == 0)
    {
        FILE* child_file = fopen("child_file.txt", "w");
        if (!child_file) 
        { 
            perror("Ошибка создания child_file.txt");
            exit(EXIT_FAILURE);
        }
        for(int i = 0; i < count; i++)
        {
            fprintf(child_file,"%s\n", lines[i]);
        }
        fclose(child_file);
        printf("child\n");
        exit(EXIT_SUCCESS);
    }
    else 
    {
        int status;
        waitpid(pid, &status, 0);
        FILE* parents_file = fopen("parents_file.txt", "w");
        for(int i = 0; i < count; i++)
        {
            fprintf(parents_file,"%s\n", lines[i]);
        }
        printf("parents\n");
        fclose(parents_file);
        return EXIT_SUCCESS;
    }
    
}    