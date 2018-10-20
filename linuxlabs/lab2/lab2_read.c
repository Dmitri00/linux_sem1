#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    if (argc < 2) {
        printf("Please specify common file to read.\n");
        exit(EXIT_SUCCESS);
    }
    pid = fork();
    int fd_in, fd_out;
    if ( (fd_in = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (pid < 0) {
        perror("fork");
       exit(EXIT_FAILURE);
       }
    if (argc == 2) {
        fd_out = 1;
    }
    else {
    char fname_index = pid==0 ? 3 : 2;
        if ( (fd_out = open(argv[fname_index], O_WRONLY|O_CREAT, S_IRWXU)) == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }
    }
    char buf[2];
    int bufsize= 8;
    int nread;
    int nwrite;
    printf("%d", fd_out);
    while ((nread = read(fd_in, buf,sizeof(buf)))> 0) {
       if ( (nwrite = write(fd_out,buf,nread)) < 0 ) {
           perror("Write");
           exit(EXIT_FAILURE);
        }
    }
    if (close(fd_in) == -1) {
        perror("input file fclose");
        exit(EXIT_FAILURE);
    }
    if (close(fd_out) == -1) {
        perror("output file fclose");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}    
