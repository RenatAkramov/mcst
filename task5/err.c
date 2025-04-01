#include "err.h"

int main(int argc, char* argv[])
{
    errno = 0;     //Обнулил errno
    if (argc == 1) //Нет названия файла
    {
        printf("No file name\n");
        return 1;
    }

    int file = open(argv[1], O_RDONLY); //Открываем файл
    if (file != -1) //Проверка если файл открылся
    {
        printf("File open\n");
        close(file);
        return 1;
    }

    printf("1. errno = %d\n", errno);
    perror("2. perror");
    printf("3. strerror: %s\n", strerror(errno));
    
    /*extern const char *const sys_errlist[];
    extern int sys_nerr;

    if (errno >= 0 && errno < sys_nerr) 
    {
        printf("sys_errlist: %s\n", sys_errlist[errno]);
    }*/
   
    return 0;
}