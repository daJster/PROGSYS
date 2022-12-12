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

#include "utils.h"
#include "signal.h"



int main(int argc, char ** argv){
    
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

    void * addr = shmat(id, NULL, SHM_RND);
    if (addr == NULL){
        perror("shmat");
        return EXIT_FAILURE;
    }

    printf("pointer of the virtual space : %p\n", addr);

    int * tab = addr;
    printf("tab[0] = %d\n", tab[0]++);
    printf("tab[0] = %d\n", tab[0]);

    int dt = shmdt(addr);
    if (dt == -1){
        perror("shmdt");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}