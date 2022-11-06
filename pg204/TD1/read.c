#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 500

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    ssize_t r ;
    char c[BUFFER_SIZE];
    do {
        r = read(STDIN_FILENO, c, sizeof(c));
        if (r == -1){
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (write(STDOUT_FILENO, c, r) == -1){
            perror("write");
            exit(EXIT_FAILURE);
        }
    } while( r > 0);

    return EXIT_SUCCESS;
}
