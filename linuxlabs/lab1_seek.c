
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
int process_error(const char* syscall_name);


int main (int argc, char **argv) {
    if (argc < 2) {
        printf("You have to provide filename\n");
        return -1;
    }
    char* fname = (char*)argv[1];
    
    int err;
    int fd = open(fname,O_RDWR);
    if (fd == -1) {
        return process_error("open");
    }
    char buff[256];
    char after_end[10] ="E";
    char at_end[11] ="AT THE END";
    char in_the_middle[7]="middle";
    if (lseek(fd, -1, SEEK_SET)==-1)
		process_error("fseek -1L SEEK_SET"); 
	if(lseek(fd, 1000, SEEK_SET)==-1)
		process_error("fseek 1000L SEEK_SET");
	err = write(fd, after_end, 1);
	if( err== -1)
		process_error("write after end"); 

	lseek(fd, -10L, SEEK_CUR);
	process_error("seek back after write"); 
	err = read(fd, buff,10);
	process_error("read after seek back"); 
	lseek(fd, 1, SEEK_END);
	err = write(fd, at_end, 11);
	if( err== -1)
		process_error("write at the end"); 
	
	lseek(fd, 4, SEEK_SET);
	err = write(fd, in_the_middle, 7);
	if( err== -1)
		process_error("write in the middle"); 
    
    close(fd);
    fd = open(fname, O_RDWR);

}
int process_error(const char* syscall_name) {
    char err_str[256] = "";
    sprintf(err_str,"*******\n\
    An error occured during %s syscall.\n\
    errno = %d\nError description:%s\n",syscall_name,errno, strerror(errno));
	perror(syscall_name);
    return -1;
}
