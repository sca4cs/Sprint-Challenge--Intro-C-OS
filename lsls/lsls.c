#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

/**
 * Main
 */
int main(int argc, char **argv)
{
  char *dir;

  // Parse command line
  if (argc > 2) {
    printf("Please provide a single directory\n");
    exit(1);
  } else if (argc == 1) {
    dir = ".";
  } else {
    dir = argv[1];
  }

  // Open directory
  DIR *d = opendir(dir);

  if (d == NULL) { 
    fprintf(stderr, "Could not open directory\n");
    exit(1);
  }

  // Repeatly read and print entries
  struct dirent *ent;
  char fullpath[8192];

  while ((ent = readdir(d)) != NULL) {
    sprintf(fullpath, "%s/%s", dir, ent->d_name);

    struct stat buf;
    stat(fullpath, &buf);

    if ((buf.st_mode & S_IFREG) != 0) {
      printf("%lld  %s\n", buf.st_size, ent->d_name);
    } else {
      printf("<DIR>  %s\n", ent->d_name);
      
    }
  }

  // Close directory
  closedir(d);

  return 0;
}