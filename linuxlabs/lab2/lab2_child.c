// Create a child process.

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>             // fork(), getpid(), getppid()

#include <errno.h>              // errno, perror()

int
main (int argc, char **argv)
{
  pid_t pid;

  // Create a child process.
  pid = fork();

  // pid == -1, failed to create a process.
  if (pid < 0) {
    perror ("fork() ");
    exit (EXIT_FAILURE);
  }
  // pid == 0, the child process.
  else if (pid == 0) {
    printf ("This is child with pid %u and parent pid %u\n", getpid(), getppid());
  }
  // pid > 0, the parent process..
  else {
    printf ("This is parent with pid %u\n", getpid());
    // Do not let child process become an orphan process.
    // An orphan process will be adopted by INIT process (pid is 1).
    sleep (3);
  }

  exit (EXIT_SUCCESS);
}
