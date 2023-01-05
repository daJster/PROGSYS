#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#include <unistd.h>
#include <fcntl.h>
#include <ctype.h> // toupper

#include "utils.h"
#include "signal.h"

void handler(int s){}

int main(){
    int fd = open("mysignal.txt", O_RDWR);
    int fdsize;
    pid_t *area;
    void *mmap_addr;
    struct stat fd_infos;
    sigset_t mask;

    if (fd == -1){
        perror("mysignal");
        return EXIT_FAILURE;
    }

    fdsize = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    // ou

    if (fstat(fd, &fd_infos) == -1) {
        perror("mysignal");
        return EXIT_FAILURE;
    }

    fdsize = fd_infos.st_size;

    if ((mmap_addr = mmap(NULL, fdsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        perror("mmap");
        return EXIT_FAILURE;
    }

    // encodage
    snprintf(mmap_addr+1, fdsize, "%d\n", getpid()); // cas ascii
    // *(pid_t*) mmap_addr = getpid(); // cas binaire
    area = mmap_addr+1;
    area[0] = getpid();
    printf("pid %d ecrit en binaire dans la memoire mmap\n", getpid());
    signal(SIGUSR1, handler);
    sigemptyset(&mask);
    printf("En attente d'un signal ...");
    sigsuspend(&mask);

    printf("les premiers caractères de la mémoire mmap sont : %s\n", (char*)mmap_addr);
    munmap(mmap_addr, fdsize);

    return EXIT_SUCCESS;
}