// Wait children.

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>             // fork(), getpid(), getppid()

#include <errno.h>              // errno, perror()

int
main (int argc, char **argv)
{
  int i=1;
  int status;
  pid_t pid;

  int exit_status = 0;
  pid = fork();
    // pid == -1, failed to create a process.
  if (pid < 0) {
    perror ("fork() ");
    exit (EXIT_FAILURE);
  }
  // pid == 0, the child process.
  else if (pid == 0) {
    printf ("This is child with pid %u and parent pid %u\n", getpid(), getppid());
    // Sleep i seconds.
    sleep(3);
    printf ("This is child with pid %u and parent pid %u\n", getpid(), getppid());
    // Exit with i status.
    return i ;
  }
  else {
      printf ("parent %u doesn't wait for child with pid %u\n", getppid(),pid);


  exit (EXIT_SUCCESS);
}
}
