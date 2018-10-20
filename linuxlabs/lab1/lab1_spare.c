
/* imported libs */
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>           // struct stat
#include <errno.h>              // errno, perror()
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/* private functions */
int process_error(const char* syscall_name, int add_to_stderr);


int main (int argc, char **argv) {
    if (argc < 2) {
        printf("You have to provide filename\n");
        return -1;
    }
    char* fname = (char*)argv[1];
    int err;
    int fd = creat(fname,0400);
    if (fd == -1) {
        return process_error("open",1);
    }
    lseek(fd, 100000L, SEEK_SET); 
    char ch = 0;
    err = write(fd, &ch, 1);
    if (err == -1)
        return process_error("write",1);
    close(fd);
  

       

}
int process_error(const char* syscall_name, int add_to_stderr) {
    char err_str[256] = "";
    sprintf(err_str,"*******\n\
    An error occured during %s syscall.\n\
    errno = %d\nError description:%s\n",syscall_name,errno, strerror(errno));
    if (add_to_stderr)
		perror(syscall_name);
    return -1;
}
