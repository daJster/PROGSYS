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

int add (int i, int j){
    return i + j;
    // printf("hi"); // this causes a segfault
}

int main(){
    int fd = open("libadd.a", O_CREAT|O_RDWR);
    if (fd == -1){
        perror("open");
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];

    int wr = write (fd, buffer, BUFFER_SIZE);
    if (wr == -1){
        perror("write");
        return EXIT_SUCCESS;
    }
    
    void *m = mmap(NULL, BUFFER_SIZE, PROT_EXEC|PROT_WRITE, MAP_SHARED, fd, 0);
    if ( m == MAP_FAILED){
        perror("mmap");
        return EXIT_FAILURE;
    }

    memcpy(m, (void *)add, BUFFER_SIZE);

    munmap(m, BUFFER_SIZE);
    return EXIT_SUCCESS;
}
