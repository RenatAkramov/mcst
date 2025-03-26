#include "stat.h"

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "File name not specified\n");
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        struct stat file_info;
        const char* file_name = argv[1];
        
        if (stat(file_name, &file_info) == -1)
        {
            fprintf(stderr, "Error stat with %s\n", file_name);
            return 1;
        }

        printf("File %s\n", file_name);
        printf("Type: ");

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

        printf("Size in byte: %ld\n", file_info.st_size);
        printf("Inode: %ld\n", file_info.st_ino);
        time_t c_time = file_info.st_ctime;
        time_t m_time = file_info.st_mtime;
        time_t a_time = file_info.st_atime;
        printf("The time the file was last modified: %s", ctime(&m_time));
        printf("File creation time: %s", ctime(&c_time));
        printf("Last access time of the file: %s", ctime(&a_time));
    }
    return 0;
}