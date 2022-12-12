#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h> // toupper

#include "utils.h"
#include "signal.h"

#define BUFFER_SIZE 2048

int main(){

    int (*ptr_add)(int, int);
    int fd = open("libadd.a", O_RDONLY);
    if ( fd == -1){
        perror("open");
        return EXIT_FAILURE;
    }

    void * m = mmap(NULL, BUFFER_SIZE, PROT_EXEC, MAP_SHARED, fd, 0);
    if (m == MAP_FAILED){
        perror("mmap");
        return EXIT_FAILURE;
    }

    ptr_add = m;

    printf("result is : %d\n", ptr_add(10,13));

    munmap(m, BUFFER_SIZE);
    return EXIT_SUCCESS;
}
