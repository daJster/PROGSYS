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
#include "signal.h"

struct sigaction old;

void usr1_handler(int s){
    printf("j'ai reçu le signal %d\n", s);
    sigaction(SIGUSR1,&old, NULL);
    printf("ancien gestionnaire restaure\n"); 
}

int main(int argc, char **argv){

    pid_t p;
    
    p = getpid();
    fprintf(stdout, "%d\n", p);

    struct sigaction act;
    sigset_t mask;
    act.sa_handler = usr1_handler;
    sigemptyset(&(act.sa_mask));
    act.sa_flags = 0;
    sigaction(SIGUSR1, &act, &old);

    printf("mon pid est %d\n", getpid());
    sigemptyset(&mask);
    while(1){
        sigsuspend(&mask);
    }
    return EXIT_SUCCESS;
}