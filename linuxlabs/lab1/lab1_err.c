#include <stdio.h>
#include <stdlib.h>
#include <errno.h>              // errno, perror()
#include <fcntl.h>
#include <string.h>



int main (int argc, char **argv) {
    if (argc < 2) {
        printf("You have to provide exisiting filename\n");
        return -1;
    }
	
    // create a new file for reading and writing with permission rw-rw-rw
    int fd = open (argv[1], O_RDWR);
    printf("file openned\n");
    if (fd == -1) {
        char err_str[256] = "";
        printf(err_str,"*******\n\
        An error occured during open() syscall.\n\
        errno = %d\nError description: %s\n",errno, strerror(errno));
        printf(err_str);
        printf("Adding info about error to stderr.\n");
        perror(err_str);
        return -1;
    }

    close (fd);  

}
