// Wait children.

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>             // fork(), getpid(), getppid()

#include <errno.h>              // errno, perror()

int
main (int argc, char **argv)
{
  int i;
  int status;
  pid_t pid;

      char s= 0;
  int exit_status = 0;
  pid = fork();
    // pid == -1, failed to create a process.
  if (pid < 0) {
    perror ("fork() ");
    exit (EXIT_FAILURE);
  }
  // pid == 0, the child process.
  else if (pid == 0) {
    // Sleep i seconds.
    printf ("This is child with pid %u and parent pid %u\n", getpid(), getppid());
   setpgrp();
    pause();
    return 0 ;
  }
  else {
      printf("Parent %u is paused.\n",getpid());
      pause();
      pid = wait(&status);
  printf ("Child %u ended with status %d\n", pid, status);
  exit (EXIT_SUCCESS);
  }
}
