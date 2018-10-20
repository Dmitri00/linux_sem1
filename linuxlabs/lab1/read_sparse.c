
/* imported libs */
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>           // struct stat
#include <errno.h>              // errno, perror()
#include <fcntl.h>
#include <string.h>
#include <unistd.h>



int main (int argc, char **argv) {
    if (argc < 2) {
        printf("You have to provide filename\n");
        return -1;
    }
    char* fname = (char*)argv[1];
    
    int err;
    int fd = open(fname,O_RDONLY);
    if (fd == -1) {
        perror("open");
        return -1;
    }
    char buff[32];
	if (lseek(fd, 50000L, SEEK_CUR) == -1)
	    perror("seek "); 
	err = read(fd, buff, 32);
	if( err== -1)
		perror("read"); 

    printf("%d bytes read after end\n", err);
    int flag = 0;
    int i;
    for (i = 0; i < err; i++) 
        if (buff[i] != 0){
            flag = 1;
            break;
        }
    if (err > 0) 
        if (flag ==  0)
            printf("Body of sparse file is filled with 0\n");
        else 
            printf("Body of spase file is not filled with 0\n");

	if (lseek(fd, 80000L, SEEK_CUR) == -1)
        perror("seek2");	

	err = read(fd, buff, 32);
	if( err== -1){
	 	perror("read2"); 
        return -1;
    }
    else 
        printf("%d bytes read after end\n", err);
    

    flag = 0;
    for (i = 0; i < err; i++) 
        if (buff[i] != 0){
            flag = 1;
            break;
        }
    if (err > 0)
        if (flag ==  0)
            printf("sparse file after end is filled with 0\n");
        else 
            printf("spase file after end is not filled with 0\n");
    if(close(fd)==-1)
        perror("error during closing file");

}
