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
        perror("ERROR: memory not allocated");
        return EXIT_FAILURE;
    }

    char **lines = NULL;
    size_t count = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;


    while ((read = getline(&line, &len, input)) != -1) 
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

    pid_t pid = fork();
    if (pid == -1) 
    {
        perror("fork failed");
        return EXIT_FAILURE;
    }

    const char* output_file;
    if (pid == 0) {
        output_file = "child_file.txt";
    } else {
        output_file = "parents_file.txt";
    }

    FILE* file_out = fopen(output_file, "w");
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

    for (size_t i = 0; i < count; i++) 
    {
        fprintf(file_out, "%s\n", lines[i]);
    }
    fclose(file_out);

    for (size_t i = 0; i < count; i++)
    {
        free(lines[i]);
    }    
    free(lines);

    if (pid == 0) 
    {
        return EXIT_SUCCESS;
    } 
    else 
    {
        int status;
        waitpid(pid, &status, 0);
        return EXIT_SUCCESS;
    }
}

   
    
    