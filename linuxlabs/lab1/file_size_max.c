

// Retrive all the information of a file.

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>              // fcntl()
#include <sys/stat.h>           // struct stat

#include <errno.h>              // errno, perror()

int main (int argc, char **argv) {
  if (argc < 2) {
      printf("You have to provide filename\n");
      return -1;
  }
  struct stat fstat;
  long long max_size=-1;
  int max_size_number=-1;

  int err_cnt = 0;
  int i = 1;
  for (; i < argc; i++) {
    // Get file stats.
    if (stat (argv[i], &fstat) < 0) {
        char error_message[256] = "";
        sprintf(error_message, "stat() can not read %s\n",argv[i]);
        perror (error_message);
        err_cnt++;
    }
    else if ((long long) fstat.st_size > max_size) {
        max_size = (long long) fstat.st_size;
        max_size_number = i;
    }
  }


  if (max_size >= 0) {
      if (err_cnt > 0) {
          printf("--------------------------\n");
      }
  printf ("The biggest file is %s\n",argv[max_size_number]);
  printf ("It size is \t\t%lld bytes\n", max_size);
  exit(EXIT_SUCCESS);
  }
  else {
      printf("All files were read with error. There isn't any maximum.");
      exit(EXIT_FAILURE);
 }
 }
