#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    int i;
    size_t r;

    struct stat statBuff;
    int type = fstat(STDIN_FILENO, &statBuff);

    if (type == -1){
        perror("type :");
        return EXIT_FAILURE;
    }

    switch (statBuff.st_mode & S_IFMT)
    {
    case S_IFBLK:
        printf("block device \n");
        break;

    case S_IFCHR:
        printf("character device \n");
        break;

    case S_IFDIR:
        printf("directory \n");
        break;

    case S_IFIFO:
        printf("FIFO/pipe \n");
        break;

    case S_IFLNK:
        printf("symlink \n");
        break;

    case S_IFREG:
        printf("regular file \n");
        break;

    case S_IFSOCK:
        printf("socket \n");
        break;

    default:
        printf("unknown ? \n");
        break;
    }

    for (i = 1; i < argc; i++){
        r = write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if (r == -1){
            perror("write :");
            exit(EXIT_FAILURE);
        }
        printf("\n");
    }


    printf("statBuff is : %d\n", statBuff.st_mode);
    return EXIT_SUCCESS;
}
