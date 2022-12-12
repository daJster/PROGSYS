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


void handler(int s){}

int main(){
    void *p = mmap(NULL, sizeof(int), PROT, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    fprintf(stderr, "pointer : %p, pointer value : %d\n", p, *(int*)p);
    *(int*)p = 42;
    fprintf(stderr, "pointer : %p, pointer value : %d\n", p, *(int*)p);
    return EXIT_SUCCESS;
}
