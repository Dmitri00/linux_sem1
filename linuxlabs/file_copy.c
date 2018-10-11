#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <fcntl.h>              // fcntl()

#include <errno.h>              // errno, perror()

int main (int argc, char **argv) {
    int fd_src=0, fd_dest=1;
    if (argc == 3) {
            fd_src = open(argv[1],O_RD);
            if (fd_src == -1) {
                return perror("open src file");
            }
            fd_dst = creat(argv[2],S_IRUSR|S_IWUSR);
            if (fd_dst == -1) {
                return perror("creat dest file");
            }
    }
    else if (argc == 2) {
        fd_dst = creat(argv[1],S_IRUSR|S_IWUSR);
        if (fd_dst == -1) {
            return process_error("creat dest file");
        }
    }
    int err = sendfile(fd_dst, fd_src, NULL, -1);
    if (err == -1)
        perror("sendfile ")
    if (fd_src != 0 && close(fd_src) == -1)
        perror("close fd_src");
    if (fd_dst != 1 && close(fd_dst) == -1)
        perror("close fd_dst");
    exit(EXIT_SUCCESS);
}
