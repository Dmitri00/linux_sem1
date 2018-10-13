
/* imported libs */
#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>           // struct stat
#include <errno.h>              // errno, perror()
#include <fcntl.h>
#include <string.h>
#include <unistd.h>


void wpk(char*);

int main (int argc, char **argv) {
    if (argc < 2) {
        printf("You have to provide filename\n");
        return -1;
    }
    
    char* fname = (char*)argv[1];
    int err;
    /*
    int fd = creat(fname,0700);
    if (fd == -1) {
        perror("open");
        return -1;
    } 
    wpk("file created\n");
    
    close(fd);
    
    wpk("file closed\n");
*/
    int fd = open(fname,O_RDWR);
    if (fd == -1) {
        perror("open");
        return -1;
    } 
    wpk("file openned\n");
 //   lseek(fd, 100L, SEEK_SET); 

    /*
    wpk("seek made\n");
    char ch = 0;
    err = write(fd, &ch, 1);
    if (err == -1){
        perror("write");
        return -1;
    }

    wpk("write made\n");
    */
    char ch = 0;
    int n = read(fd, &ch, 1);
    printf("%d bytes read\n",n);
    wpk(" read made\n");
    
    close(fd);
  
    wpk(" close made\n ");
    

       

}
void wpk(char* message) {
    printf(message);
    char ch;
    scanf("%c",&ch);
}
