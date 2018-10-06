
/* imported libs */
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>           // struct stat
#include <errno.h>              // errno, perror()
#include <string.h>

/* private functions */
void process_error(const char* syscall_name, bool add_to_stderr=true);


int main (int argc, char **argv) {
    if (argc < 3) {
        printf("You have to provide filename and file's access mode");
        return -1;
    }
    char* fname = argv[1];
    mode_t fmode = argv[2];
    int err;
    // create a new file for reading and writing with permission rw-rw-rw
    int fd = open(fname, O_CREAT,S_IRUSR);
    if (fd == -1) {
        return process_error("open");
    }
    char buff[256] = "";
    err = scanf("Type text for new file (<256 symbols):\n%s",buff);
    if (err == -1)
        return process_error("scanf");

    err = write(fd, buff, strlen(buff));
    if (err == -1)
        return process_error("write");
    close(fd);
    fd = open(fname, O_RDWR);
    if (fd == -1) {
        return process_error("open");
    }   

}
void process_error(const char* syscall_name, bool add_to_stderr) {
    char err_str[256] = "";
    sprintf(err_str,"*******\n
    An error occured during %s syscall.\n
    errno = %d\nError description: %s\n",syscall_name,errno, sys_errlist[errno]);
    printf(err_str);
    
    if (add_to_stderr) {
        printf("Adding info about error to stderr.");
        perrno(err_str);
    }
    return -1;
}