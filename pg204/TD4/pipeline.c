#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
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

int main(int argc, char *argv[]){

    int p[2];
    int i;
    int rd;
    int fd_son;
    char buffer[BUFFER_SIZE];

    char  *ls[] = { "ls", "-l", NULL};
    char  *tr[] = { "tr", "-d", "[:blank:]", NULL};
    char **commandes[] = { ls, tr };
    int nb_commandes = sizeof(commandes) / sizeof(char*);
    printf("%d\n", nb_commandes);

    int fd_pip = pipe(p);
    if (fd_pip == -1){
        perror("pipe");
        return EXIT_FAILURE;
    }

    fd_son = fork();
    if (fd_son == -1){
        perror("fork");
        return EXIT_FAILURE;
    }

    if (fd_son == 0 /*fils*/){
        close(p[1]); // no need
       
       
        do {
            if ((rd = read(p[0], buffer, BUFFER_SIZE)) == -1){
                perror("read");
                return EXIT_FAILURE;
            }  

            for (int j = 0; j < rd; j++){
                buffer[j] = toupper(buffer[j]);
            }

            if (write(STDOUT_FILENO, buffer, rd) == -1){
                perror("write");
                return EXIT_FAILURE;
            };
            
            if (write(STDERR_FILENO, MSG_SON, strlen(MSG_SON) + 1) == -1){
                perror("write");
                return EXIT_FAILURE;
            };

        } while(rd > 0);
    } else /*père*/ {
        close(p[0]); // no need
        //sleep(1);
        for( i = 0; i < N; i++ ){
            if (write(p[1], MSG, strlen(MSG)) == -1){
                perror("write");
                return EXIT_FAILURE;
            }

        }
        write(STDERR_FILENO, ERR, strlen(ERR) + 1);
        dup2(p[1], 1);
        close(p[1]);
        execlp("ps","",NULL);
        perror("ps");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}