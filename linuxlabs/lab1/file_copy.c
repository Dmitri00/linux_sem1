#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>              // fcntl()
#include <unistd.h>
#include <errno.h>              // errno, perror()

int main (int argc, char **argv) {
    int fd_src=0, fd_dst=1;
    if (argc == 3) {
            fd_src = open(argv[2],O_RDONLY);
            if (fd_src == -1) {
                perror("creat src file");
            }
            
            fd_dst = creat(argv[1],S_IRUSR|S_IWUSR);
            if (fd_dst == -1) {
                perror("creat dest file");
            }
}
    
    else if (argc == 2) {
        fd_dst = creat(argv[1],S_IRUSR|S_IWUSR);
        if (fd_dst == -1) {
            perror("creat dest file");
        }
    }

    int err = dup2(fd_src, fd_dst);
    if (err == -1)
        perror("dup ");
    if ( (fd_dst = open(argv[1], O_RDWR)) == -1)
        perror("Error dusring opening dst file");
    char buf[512];
    int n;
    while ( (n = read(fd_src, buf, 512)) > 0)
        if ( write(fd_dst, buf, n) == -1)
            perror("Error during writing to dst file");
    if (fd_src != 0 && close(fd_src) == -1)
        perror("close fd_src");
    if (fd_dst != 1 && close(fd_dst) == -1)
        perror("close fd_dst");
    exit(EXIT_SUCCESS);
}
