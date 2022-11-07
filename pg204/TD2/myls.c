#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#define BUFFER_SIZE 500


#include <unistd.h>

#include "utils.h"

void print_perms(mode_t perms){
    printf( (perms & S_IRUSR) ? "r" : "-");
    printf( (perms & S_IWUSR) ? "w" : "-");
    printf( (perms & S_IXUSR) ? "x" : "-");
    printf( (perms & S_IRGRP) ? "r" : "-");
    printf( (perms & S_IWGRP) ? "w" : "-");
    printf( (perms & S_IXGRP) ? "x" : "-");
    printf( (perms & S_IROTH) ? "r" : "-");
    printf( (perms & S_IWOTH) ? "w" : "-");
    printf( (perms & S_IXOTH) ? "x" : "-");
    printf(" ");
}

void print_time(time_t time){
    printf("a");
}

int main(int argc, char *argv[])
{
    int i;
    size_t r;
    // int fd_dir;
    int files_num = 0;
    DIR *dir;
    struct dirent *dir_st;
    struct stat *buf = malloc(sizeof(struct stat));
    int stat_fd = 0;


    stat_fd++;
    if ((dir = opendir (".")) == NULL) {
        perror ("Cannot open .");
        exit (1);
    }

    while ((dir_st = readdir(dir)) != NULL){
            files_num++;
            stat_fd = stat(dir_st->d_name, buf);

            if (stat_fd == -1){
                perror("stat");
                return EXIT_FAILURE;
            }
            switch (dir_st->d_type)
            {
            case DT_BLK:
                printf("blk\t");
                break;

            case DT_CHR:
                printf("chr\t");
                break;

            case DT_DIR:
                printf("%d :\t", files_num);
                print_perms(buf->st_mode);
                printf(" d ");
                printf(" %ld\t", buf->st_size);
                printf("%s\t\n",dir_st->d_name);
                break;

            case DT_FIFO:
                printf("ff\t");
                break;

            case DT_LNK:
                printf("l\t");
                break;

            case DT_REG:
                printf("%d :\t", files_num);
                print_perms(buf->st_mode);
                printf(" - ");
                printf(" %ld\t", buf->st_size);
                printf("%s\t\n",dir_st->d_name);
                break;

            case DT_SOCK:
                printf("sock\t");
                break;

            default:
                printf("unknown\t");
                break;
            }
    }
    closedir(dir);
    free(buf);

    for (i = 1; i < argc; i++){
        r = write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        if (r == -1){
            perror("write :");
            exit(EXIT_FAILURE);
        }
        printf("\n");
    }

    return EXIT_SUCCESS;
}
