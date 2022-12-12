#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define BUFFER_SIZE 500

#include <unistd.h>
#include <fcntl.h>

#include "utils.h"



#ifndef CHAINE1 
    #define CHAINE1 "hello\n"
    // bufferisation par ligne, si il rencontre un \n il envoie le buffer dans la sortie souhaitée
    // la sortie d'erreur est faite d'une façon que le message soit immédiat *** ./buffer | cat ne montre pas le message d'erreur avec _exit
#endif

#ifndef CHAINE2 
    #define CHAINE2 "world !"
#endif



//libc vs syscalls
int main(int argc, char *argv[]){
    FILE * exit1 = stdout, * exit2 = stdout;
    int fd1 = 1, fd2 = 1;
    
    #ifdef UTILISER_SORTIE_ERREUR1
        exit1 = stderr;
        fd1 = 2;
    #endif

    #ifdef UTILISER_PRINTF1
        fprintf(exit1, "%s", CHAINE1) ;
    #else 
        write(fd1, CHAINE1, strlen(CHAINE1));
    #endif

    sleep(3);

    #ifdef UTILISER_SORTIE_ERREUR2
        exit2 = stderr;
        fd2 = 2;
    #endif

    #ifdef UTILISER_PRINTF2
        fprintf(exit2, "%s", CHAINE2);
    #else 
        write(fd2, CHAINE2, strlen(CHAINE2));
    #endif

    #ifdef UTILISER_EXIT
        _exit(0);
    #else
        exit(0);
    #endif

    return 0;
}