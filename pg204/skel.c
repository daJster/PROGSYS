#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "utils.h"

int main(int argc, char *argv[])
{
    int i;
    size_t r;

    for (i = 1; i < argc; i++){
        r = write(STDOUT_FILEND, argv[i], strlen(argv[i]));
        if (r == -1){
            perror("write :");
            exit(EXIT_FAILURE);
        }
        printf("\n");
    }
    return EXIT_SUCCESS;
}
