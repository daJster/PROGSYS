#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    size_t r;
    long x = 6921;
    r = write(STDOUT_FILENO, &x, sizeof(long));
    if (r == -1){
        perror("write :");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
