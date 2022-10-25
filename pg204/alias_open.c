#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUFFER_SIZE 500


#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    char c[BUFFER_SIZE];
    int fd = open("donnees.txt", O_RDWR);
    if (fd == -1){
        perror("open ");
        return EXIT_FAILURE;
    }
    int rd = read(fd, c, 4);
    if (rd == -1){
        perror("read ");
        return EXIT_FAILURE;
    }
    int wr = write(STDOUT_FILENO, c, 4);
    if (wr == -1){
        perror("write ");
        return EXIT_FAILURE;
    }

    fd = open("donnees.txt", O_RDWR);
    rd = read(fd, c, 4);
    wr = write(STDOUT_FILENO, c, 4);
    close(fd);
    return EXIT_SUCCESS;
}
