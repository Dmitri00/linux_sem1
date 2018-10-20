
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
    // try to set pointer below zero --> Error
    if (lseek(fd, -1, SEEK_SET)==-1)
		process_error("fseek -1L SEEK_SET"); 
    // try to set pointer after end --> OK
	if(lseek(fd, 1000, SEEK_SET)==-1)
		process_error("fseek 1000L SEEK_SET");
    // write after EOF --> OK. Hole is filled with zeros
	err = write(fd, after_end, 1);
	if( err== -1)
		process_error("write after end"); 

    // Read and write are possible
	if (lseek(fd, -10L, SEEK_CUR) == -1)
	    process_error("seek back error"); 
	err = read(fd, buff,10);
	if (err == -1)
        process_error("read error"); 

	
	lseek(fd, 4, SEEK_SET);
	err = write(fd, in_the_middle, 7);
	if( err== -1)
	 	process_error("write in the middle"); 
    
    if(close(fd)==-1)
        process_error("error during closing file");

}
int process_error(const char* syscall_name) {
    char err_str[256] = "";
    sprintf(err_str,"*******\n\
    An error occured during %s syscall.\n\
    errno = %d\nError description:%s\n",syscall_name,errno, strerror(errno));
	perror(syscall_name);
    return -1;
}
