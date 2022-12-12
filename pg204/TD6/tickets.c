#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>

#include "utils.h"

#define POOL 8

int nbtickets = 1000;

void *vendeur( void * id )
{
    int nbtickets_vendus = 0;
    
    while ( nbtickets > 0 ) { // une lecture
	nbtickets_vendus++; // lecture; op; ecrituref
	sched_yield(); /* Do not touch this line */
	nbtickets--;
    }
    
    printf( "[%d] J'ai vendu %d tickets \n",
	    (int) (intptr_t) id, nbtickets_vendus );
    
    return (void *) (intptr_t) nbtickets_vendus;
}

int main( int argc, char *argv[] ) {
    int nbtickets_vendus = 0;
    int i, rc;
    pthread_t t[8];
    void *r;

    if ( argc >= 2 ) {
	    nbtickets = atoi( argv[1] );
    }

    // nbtickets_vendus = (int) (intptr_t) vendeur(0); // main program
    
    for (i = 0 ; i < POOL; i++){
        if ( (rc = pthread_create(&t[i-1], NULL, vendeur, (void *) (intptr_t)i)) == -1){
            perror("pthread_create");
            return EXIT_FAILURE;
        }
        // printf("[%d] - ", i);
    }

    for (i  = 0; i < POOL; i++){
        pthread_join(t[i], &r);
        nbtickets_vendus += (int) (intptr_t) r;
    }

    printf( "%d tickets ont été vendus (nbtickets = %d)\n", nbtickets_vendus, nbtickets);
    
    return EXIT_SUCCESS;
}