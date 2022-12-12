
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define BUFFER_SIZE 500
#define MSG "hello World"
#define ERR "Je suis le pere et je quitte\n"
#define MSG_SON "Je suis le fils et je quitte\n"
#define N 100

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h> // toupper

#include "utils.h"


char  *ls[] = { "ls", "-l", NULL};
char  *tr[] = { "tr", "-d", "[:blank:]", NULL};
char  *wc[] = { "wc", "-j", "[:blank:]", NULL};
char **commandes[] = { ls, tr, wc };
int nb_commandes = sizeof(commandes) / sizeof(char*);



int main(int argc, char **argv){
    int i,s;
    pid_t f;

    int fd_pipes[(nb_commandes-1)*2];

    for (i = 0; i< nb_commandes-1; i++){
        if(pipe(fd_pipes+2*i) == -1){
            perror("pipe");
            return EXIT_FAILURE;
        }
    }

    for (i = 0; i<nb_commandes-1; i++){
        if ( (f = fork()) == -1 ){
            perror("fork");
            return EXIT_FAILURE;
        }

        if (f == 0){
            if (i > 0){
                dup2(fd_pipes[2*(i-1)], 0);
            }
            if ( i < (nb_commandes-1)*2){
                dup2(fd_pipes[2*(i+1)], 1);
            }
            for (i = 0; i < (nb_commandes-1)*2; i++){
                close(fd_pipes[i]);
            }
            execvp(commandes[i][0], commandes[i]);
            perror(commandes[i][0]);
            return EXIT_FAILURE;
        }
    }

    for ( i = 0; i<(nb_commandes-1)*2; i++){
        close(fd_pipes[i]);
    }

    if ( waitpid(f, &s, 0) == -1 ){
        perror("wait for last command");
        return EXIT_FAILURE;
    }

    if(WIFEXITED(s)) return WEXITSTATUS(s);

    fprintf(stderr, "%s ends with signal %d\n", commandes[nb_commandes-1][0], WTERMSIG(s));

    return EXIT_SUCCESS;
}