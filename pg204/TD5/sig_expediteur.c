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
    int fd = open("mysignal", O_RDWR);
    int fdsize;
    // pid_t *area;
    void *mmap_addr;
    struct stat fd_infos;
    // sigset_t mask;

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

    if ((mmap_addr = mmap(NULL, fdsize, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED){
        perror("mmap");
        return EXIT_FAILURE;
    }

    // the following part is different

    // encodage
    pid_t receveur_pid = atoi(mmap_addr);  //cas ascii
    // receveur_pid = *(pid_t*)mmap_addr; // cas binaire

    printf("Expediteur reading stdout\n");
    int rd = read(STDIN_FILENO, mmap_addr, fdsize);
    if (rd == -1){
        perror("read");
        return EXIT_FAILURE;
    }

    int i = 0;
    while(1){
        printf("%d\n", i);
        ((char *)mmap_addr)[i++] = 10;
    } 
    kill(receveur_pid, SIGUSR1);
    munmap(mmap_addr, fdsize);

    return EXIT_SUCCESS;
}
