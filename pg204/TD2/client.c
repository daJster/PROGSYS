#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 500

#include <unistd.h>
#include <fcntl.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    char *fifo = "versserveur";
    char c[BUFFER_SIZE];

    int mkf = mknod(fifo, 0666, 0);
    
    if (mkf == -1){
        perror("mknod");
        return EXIT_FAILURE;
    }

    while (1){
        int fd = open(fifo, O_WRONLY);

        if (fd == -1){
            perror("open ");
            return EXIT_FAILURE;
        }

        int r = read(STDIN_FILENO, c, BUFFER_SIZE);

        if (r == -1){
            perror("read ");
            return EXIT_FAILURE;
        }
        
        int w = write(fd, c, r);

        if (w == -1){
            perror("write ");
            return EXIT_FAILURE;
        }
        
        close(fd);
    }
    return EXIT_SUCCESS;
}
