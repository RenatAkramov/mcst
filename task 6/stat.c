#include "stat.h"

int main(int argc, char* argv[])
{
    if (argc < 2)//Обработка ситуации, когда не ввели названия файлов
    {
        fprintf(stderr, "File name not specified\n");
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        struct stat file_info = {0};
        const char* file_name = argv[i];
        
        if (stat(file_name, &file_info) == -1)
        {
            fprintf(stderr, "ERROR: stat with \"%s\"\n", file_name);
            return 1;
        }

        printf("File: %s\n", file_name);
        printf("Type: ");//Вывод типа файла

        if (S_ISREG(file_info.st_mode))
        {
            printf("regular file\n");
        }
        else if (S_ISDIR(file_info.st_mode))
        {
            printf("directory\n");
        }
        else if (S_ISCHR(file_info.st_mode))
        {
            printf("Character device (byte-oriented)\n");
        }
        else if (S_ISBLK(file_info.st_mode)) 
        {
            printf("Block device (block-oriented)\n");
        } 
        else if (S_ISFIFO(file_info.st_mode))
        {
            printf("FIFO (channel)\n");
        } 
        else if (S_ISLNK(file_info.st_mode)) 
        {
            printf("Symbolic link\n");
        } 
        else 
        {
            printf("Unknown type\n");
        }

        printf("Size in byte: %ld\n Inode: %ld\n The time the file was last modified: %sFile creation time: %s Last access time of the file: %s\n\n\n",
              file_info.st_size, file_info.st_ino, ctime(&file_info.st_mtime), ctime(&file_info.st_ctime), ctime(&file_info.st_atime));//Вывод осталбных данных
    }
    return 0;
}