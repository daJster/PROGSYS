#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 500
#define MSG "hello World"
#define ERR "Je suis le pere et je quitte\n"
#define MSG_SON "Je suis le fils et je quitte\n"
#define N 10

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h> // toupper

#include "utils.h"

int main(int argc, char *argv[]){
    int pipe_fd[2];
    char buff[BUFFER_SIZE];
    int i, wr, rd;
    char  *ls[] = { "ls", "-l", NULL};
    char  *tr[] = { "tr", "-d", "[:blank:]", NULL};
    char **commandes[] = { ls, tr };
    int nb_commandes = sizeof(commandes) / sizeof(char*);
    
    int r = pipe(pipe_fd);
    if (r == -1){
        perror("pipe");
        return EXIT_FAILURE;
    }

    int fpid = fork();
    if (fpid == 0 ) { // son
        close(pipe_fd[1]);
        rd = read(pipe_fd[0], buff, BUFFER_SIZE);
        if (rd == -1){
            perror("read");
            return EXIT_FAILURE;
        }

        for (i = 0; i < rd; i++){
            buff[i] = toupper(buff[i]);
        }

        wr = write(STDOUT_FILENO, buff, rd);
        if (wr == -1){
            perror("write");
            return EXIT_FAILURE;
        }

        wr = write(STDERR_FILENO, MSG_SON, strlen(MSG_SON));
        if (wr == -1){
            perror("write");
            return EXIT_FAILURE;
        }

    } else if (fpid > 0) { //father
        close(pipe_fd[0]);
        for (i = 0; i < N; i++){
            wr = write(pipe_fd[1], MSG, strlen(MSG));
            if (wr == -1){
                perror("write");
                return EXIT_FAILURE;
            }
        }
        wr = write(STDERR_FILENO, ERR, strlen(ERR));
        if (wr == -1){
            perror("write");
            return EXIT_FAILURE;
        }

        dup2(pipe_fd[1], 1);
        close(pipe_fd[1]);
        execlp("ps", "", NULL);
        perror("execlp");
        return EXIT_FAILURE;
    } else { // error
        perror("fork");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}