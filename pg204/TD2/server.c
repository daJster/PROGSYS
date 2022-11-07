#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <unistd.h>
#include <fcntl.h>

#include "utils.h"

#define BUFFER_SIZE 256

void transfer( int fd_in, int fd_out ) {
    char buffer[BUFFER_SIZE];
    ssize_t len_read, wrote, rc;
    while( 1 ) {
	    printf("check fd_in : %d\n", fd_in);
        len_read = read( fd_in, buffer, BUFFER_SIZE );
        exit_if( len_read == -1, "read" );

        if ( len_read == 0 ) {
            /* EOF*/
            return;
        }
        
        wrote = 0;
        /*
         * Si jamais write n'écrit pas assez, on doit boucler pour
         * tout écrire avant de repasser à read
         */
        do{
            rc = write( fd_out, buffer + wrote, len_read - wrote );
            exit_if( rc == -1, "write" );
            wrote += rc;
        } while( wrote < len_read );
    }
}

int main(int argc, char *argv[])
{
    char *fifo = "versserveur";
    int mkf = mknod(fifo, 0666, 0);
    
    if (mkf == -1){
        perror("mknod");
        return EXIT_FAILURE;
    }

    int fd_in = open(fifo, O_WRONLY);
    exit_if(fd_in == -1, "open");
    transfer(fd_in, STDOUT_FILENO);
    close(fd_in);
    return EXIT_SUCCESS;
}
