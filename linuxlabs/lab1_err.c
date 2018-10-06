
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>              // errno, perror()

int main (int argc, char **argv) {
    if (argc < 2) {
        printf("You have to provide filename");
        return -1;
    }

    // create a new file for reading and writing with permission rw-rw-rw
    fd = open (argv[1], O_RDWR);
    if (fd == -1) {
        char err_str[256] = "";
        sprintf(err_str,"*******\n
        An error occured during open() syscall.\n
        errno = %d\nError description: %s\n"err_str,errno, sys_errlist[errno]);
        printf(err_str);
        printf("Adding info about error to stderr.");
        perrno(err_str);
        return -1;
    }

    close (fd);  

}
