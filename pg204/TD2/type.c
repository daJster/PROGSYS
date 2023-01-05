#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    int i;
    size_t r;

    if (argc != 2) {
        printf("Usage: fstat <file>\n");
        return 1;
    }

    const char *filename = argv[1];
    struct stat file_stat;
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        return 1;
    }

    printf("file type : ");
    switch (file_stat.st_mode & S_IFMT)
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


    printf("statBuff is : %d\n", file_stat.st_mode);
    return EXIT_SUCCESS;
}
