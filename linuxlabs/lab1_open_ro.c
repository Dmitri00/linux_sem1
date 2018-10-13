
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
    if (argc < 3) {
        printf("You have to provide filename and file's access mode\n");
        return -1;
    }
    char* fname = (char*)argv[1];
    int fmode = strtol(argv[2], NULL, 8);
    printf("%o\n",fmode);
    int err;
    int fd = creat(fname,0400|fmode);
    if (fd == -1) {
        return process_error("open",1);
    }
    char buff[256] = "";
    printf("Type text for new file (<256 symbols):\n");
    err = scanf("%s",buff);
    if (err == -1)
        return process_error("scanf",1);
	printf("String read:%s\n",buff);
    err = write(fd, buff, strlen(buff));
    perror("WRITE 1");
    if (err == -1)
        return process_error("write",1);
    close(fd);
    fd = open(fname, O_RDWR);
    if (fd == -1) {
        return process_error("open",1);
    }   

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
