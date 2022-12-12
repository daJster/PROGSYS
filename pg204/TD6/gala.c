#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h> // toupper
#include <pthread.h> 
#include <fcntl.h> // intptr_t 

#include "utils.h"
#include "signal.h"

int g = 0;

void * start(void * p){
    printf("le processus : %d\n", *(int *)p);
    int l = 0; // testing the change in l and g
    l++;
    g++;
    printf("%d , %d", l, g);
    return NULL;
}



int main(int argc, char ** argv){
    pthread_t t[8];
    int rc, i;
    pid_t x = getpid();

    printf("main program : %d\n", getpid());
    for (i = 1 ; i <= 8; i++){
        if ( (rc = pthread_create(&t[i-1], NULL, start, &x)) == -1){
            perror("pthread_create");
            return EXIT_FAILURE;
        }
        // printf("[%d] - ", i);
    }

    for (i = 0 ; i < 8; i++){
        pthread_join(t[i], NULL);
    }
    
    return EXIT_SUCCESS;
}