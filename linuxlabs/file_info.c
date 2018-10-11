

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
  char* fname = (char*)argv[1];
  struct stat fstat;



  // Get file stats.
  if (stat (fname, &fstat) < 0) {
    perror ("stat() ");
    exit (EXIT_FAILURE);
  }
  char ftype[32] = "";
  switch (fstat.st_mode & S_IFMT) {
    case S_IFSOCK:
      ftype = "socket";
      break;
    case S_IFREG:
      ftype = "regular file";
      break;
    case S_IFLNK:
      ftype = "symbolic link";
      break;
    case S_IFBLK:
      ftype = "block device";
      break;
    case S_IFCHR:
      ftype = "character device";
      break;
    case S_IFDIR:
      ftype = "directory";
      break;    
    case S_IFIFO:
      ftype = "FIFO";
      break;
  }
  printf ("Information for %s\n",fname);
  printf ("---------------------------\n");
  printf("ID of containing device:  [%lx,%lx]\n",
      (long) major(fstat.st_dev), (long) minor(fstat.st_dev));
  printf("File type:%40s",ftype);
  printf ("File Size: \t\t%lld bytes\n", (long long) fstat.st_size);
  printf("Blocks allocated:         %lld\n",
          (long long) fstat.st_blocks);
  printf ("Number of Links: \t%ld\n", (long) fstat.st_nlink);
  printf ("File inode: \t\t%ld\n", (long) fstat.st_ino);

  printf("Preferred I/O block size: %ld bytes\n",
  (long) fstat.st_blksize);
  printf("Ownership:                UID=%ld   GID=%ld\n",
          (long) fstat.st_uid, (long) fstat.st_gid);
  printf ("File Permissions: \t");
  printf ((S_ISDIR (fstat.st_mode)) ? "d" : "-");
  printf ((fstat.st_mode & S_IRUSR) ? "r" : "-");
  printf ((fstat.st_mode & S_IWUSR) ? "w" : "-");
  printf ((fstat.st_mode & S_IXUSR) ? "x" : "-");
  printf ((fstat.st_mode & S_IRGRP) ? "r" : "-");
  printf ((fstat.st_mode & S_IWGRP) ? "w" : "-");
  printf ((fstat.st_mode & S_IXGRP) ? "x" : "-");
  printf ((fstat.st_mode & S_IROTH) ? "r" : "-");
  printf ((fstat.st_mode & S_IWOTH) ? "w" : "-");
  printf ((fstat.st_mode & S_IXOTH) ? "x" : "-");
  printf ("\n\n");

  printf("Last status change:       %s", ctime(&sb.st_ctime));
  printf("Last file access:         %s", ctime(&sb.st_atime));
  printf("Last file modification:   %s", ctime(&sb.st_mtime));

  exit(EXIT_SUCCESS);
}
