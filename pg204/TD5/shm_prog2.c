#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h> 
#include <semaphore.h>

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h> // toupper

#include "utils.h"
#include "signal.h"



int main(int argc, char ** argv){
    int fils = 0;
    
    key_t k = ftok("test_shm", 1);
    if (k == -1){
        perror("ftok");
        return EXIT_FAILURE;
    }

    int id = shmget(k, BUFFER_SIZE, IPC_CREAT | 0644);
    if ( id == -1){
        perror("shmget");
        return EXIT_FAILURE;
    }

    sem_t *sem = sem_open("sem", O_CREAT, 0666, 1);
    if( sem == SEM_FAILED){
        perror("sem_open");
        return EXIT_FAILURE;
    }

    void * addr = shmat(id, NULL, SHM_RND);
    if (addr == NULL){
        perror("shmat");
        return EXIT_FAILURE;
    }

    printf("pointer of the virtual space : %p\n", addr);

    int * tab = addr;
    for (int j = 0; j < 2; j++){
        if (fork() == 0){
            fils = 1;
            printf("pid fils: %d\n", getpid());
            tab[tab[0] + 1] = getpid();
            tab[0]++;
            sem_post(sem);
        }

    }
    if (fils == 1){return EXIT_SUCCESS;}
    while(wait(NULL) != -1);
    sleep(1);
    printf("il y a %d processus\n", tab[0]);
    for (int i = 0; i <tab[0]; i++){
        printf("- pid : %d\n", tab[i + 1]);
    }

    int dt = shmdt(addr);
    if (dt == -1){
        perror("shmdt");
        return EXIT_FAILURE;
    }

    sem_close(sem);
    sem_unlink("sem");
    return EXIT_SUCCESS;
}