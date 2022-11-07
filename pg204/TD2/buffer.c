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
    #define CHAINE1 "hello"
#endif
#ifndef CHAINE2 
    #define CHAINE2 "world !"
#endif




int main(int argc, char *argv[]){
    FILE * exit1 = stdout, * exit2 = stdout;
    int fd1 = 1, fd2 = 1;
    
    #ifdef UTILISER_SORTIE_ERREUR1
        exit1 = stderr;
        fd1 = 2;
    #endif

    #ifdef UTILISER_SORTIE_ERREUR2
        exit2 = stderr;
        fd2 = 2;
    #endif

    #ifdef UTILISER_PRINTF
        fprintf(exit1, "%s", CHAINE1);
    #else 
        write(fd1, CHAINE1, strlen(CHAINE1));
    #endif
    sleep(3);


    return 0;
}