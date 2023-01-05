#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <unistd.h>

int main(int argc, char *argv[]){

    // pid_t pid = getpid();
    // printf("pid is : %d\n", pid);
    // pid_t pid_s = fork();
    // suspendre l'execution -> go to kernel if OK -> creates a clone (deux entités séparés) 
    // of the processus with all the pointers pointing to the same things  (une vrai copie)
    // after fork they're both executed at the same time, reprend les processus
    // output :pid is : 4793 // father;
    // pid_s is : 4794 // father's fork, son pid;
    // pid_s is : 0 // son's fork returns 0;
    // (pid_s == 0) ? printf("son\n") : printf("father\n");
    // printf("pid_s is : %d\n", pid_s); 


    // correction mine is correct too
    pid_t p;
    int i;
    printf("pid[%d]\n", getpid()); // try w \n and w/o it, the buffer get broken so the son processus doesn't show it when there is a \n
    p = fork();
    if (p == -1){
        perror("fork");
        return EXIT_FAILURE;
    } 
    
    if (p == 0){
        printf("fils : [%d / %d]\n", getpid(), getppid()); // getppid parent pid
        execlp("ls","ls", NULL);
        perror("ls");
        return EXIT_FAILURE;
    } else {
        for (i = 0; i < 10; i++){
            printf("le pere.....\n");
            sleep(1);
        }
    }
    return EXIT_SUCCESS;
}