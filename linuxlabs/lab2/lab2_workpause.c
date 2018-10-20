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
    pause();
    return 0 ;
  }
  else {
  printf ("parent %u, grandparent %u \n", getpid(),getppid());
      printf("Parent is waiting.\n");
      pause();
      pid = wait(&status);
    printf ("child with pid %u and parent pid %u ended with status %d\n", pid, getpid(), status);
  exit (EXIT_SUCCESS);
  }
}
