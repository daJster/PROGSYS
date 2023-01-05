#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 500

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "utils.h"



int main(int argc, char **argv){
    int fd;
    pid_t f;
    int s;
    fd = open(argv[1], O_WRONLY|O_CREAT, 0600); // to write and create :=)
    if (fd == -1){
        perror(argv[1]);
        return EXIT_FAILURE;
    }
    write(fd, argv[2], strlen(argv[2]));

    f = fork();
    if (f == -1){
        perror("fork"); 
        return EXIT_FAILURE;
    }

    if (f == 0 /*fils*/){
        dup2(fd, 1);
        // close(fd);
        execvp(argv[2], argv+2);
        perror(argv[2]);
        return EXIT_FAILURE;
    }

    close(fd);

    if (wait(&s) == -1){
        perror("wait");
        return EXIT_FAILURE;
    }
    if (WIFEXITED(s)){
        printf("%s return %d\n", argv[2], WEXITSTATUS(s)); 
    } else {
        if (WIFSIGNALED(s)){
            printf("%s end with signal %d\n", argv[2], WTERMSIG(s)); // si segfault signal = 11; voir table des signaux
        }
    }

    return EXIT_SUCCESS;
}