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

#define KBYTE 1024


int main(int argc, char ** argv){
    
    key_t key = ftok("mysignal.txt", 0);

    int shm_id = shmget(key, KBYTE, IPC_CREAT | 0644);

    int *block = shmat(shm_id, NULL, 0);

    (*block)++;

    printf("first int in block : %d\n", *block);

    int shm_dt = shmdt(block);

    return EXIT_SUCCESS;
}