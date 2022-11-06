#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER_SIZE 500

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    ssize_t c1, c2, l;
    struct nopad np;
    do {
        c1 = read(STDIN_FILENO, &np.c1, sizeof(char));
        l = read(STDIN_FILENO, &np.l, sizeof(long));
        c2 = read(STDIN_FILENO, &np.c2, sizeof(char));

        if (c1 == -1 || c2 == -1 || l == -1){
            perror("read");
            exit(EXIT_FAILURE);
        }

        if (write(STDOUT_FILENO, &np.c1, c1) == -1 || write(STDOUT_FILENO, &np.l, l) == -1 || write(STDOUT_FILENO, &np.c2, c2) == -1){
            perror("write");
            exit(EXIT_FAILURE);
        }
    } while( c1 > 0 && c2 > 0 && l > 0);

    return EXIT_SUCCESS;
}
