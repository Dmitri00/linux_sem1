#include <stdio.h>
#include <stdlib.h>
#include <sys/sendfile.h>
#include <fcntl.h>              // fcntl()
#include <sys/stat.h>
#include <curses.h>
#include <errno.h>              // errno, perror()
#define BUF_SIZE 32
#define MAX(a,b) a > b ? a : b
int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Input filename must be specified\n");
        return -1;
        }
    struct stat fstat;
    if (stat(argv[1],&fstat) < 0) {
        perror("stat() ");
        return -1;
    }
    if ( fstat.st_size > 256) {
        printf("File is to large. Do you want to continue? (y/n)");
        int ch;
        int cont = 0;
        while(cont == 0) {
            printf("%d\n",ch);
            ch = getch();
            
            switch(ch) {
                case 'y':case 'Y': cont++; break;
                case 'n':case 'N': return 0;
                default: printf("y/n:");
                }
        }
    }
       
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open input file");
        return -1;
       }
    int buf_size = BUF_SIZE;
    char buffer[BUF_SIZE];
    long long offset = fstat.st_size;
    if (lseek(fd, 0, SEEK_END) == -1) {
        perror("lseek ()");
        return -1;
    }
    int read_cnt;
    int i;
    while (offset != 0) {
        read_cnt = offset - MAX(offset - BUF_SIZE,0);
        offset -= read_cnt;
        if (lseek(fd, -read_cnt, SEEK_CUR) == -1) {
            perror("lseek seek_cur ");
            return -1;
        }
        if(read(fd, buffer, read_cnt) != read_cnt) {
            perror("read");
            return -1;
        }
        for ( i = read_cnt - 1; i >= 0; i--) {
            printf("%c",buffer[i]);
        }
    } 
    return 0;

}
