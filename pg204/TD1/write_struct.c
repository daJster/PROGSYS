#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include "utils.h"


int main(int argc, char *argv[])
{
    size_t r;
    struct nopad np;
    np.c1 = 'a';
    np.l = 5;
    np.c2 = 'b';
    printf("size of struct nopad : %ld\n",  sizeof(struct nopad) );
    r = write(STDOUT_FILENO, &np.c1, sizeof(char));
    r = write(STDOUT_FILENO, &np.l, sizeof(long));
    r = write(STDOUT_FILENO, &np.c2, sizeof(char));
    if (r == -1){
        perror("write :");
        exit(EXIT_FAILURE);
    }
    printf("\n");
    return EXIT_SUCCESS;
}
