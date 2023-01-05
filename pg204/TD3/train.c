#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include <unistd.h>

#define HELLO "hello"
#define WORLD "world!"

int main(int argc, char *argv[]){

    fprintf(stdout, HELLO);
    sleep(3);
    fprintf(stdout, WORLD);

    return EXIT_SUCCESS;
}