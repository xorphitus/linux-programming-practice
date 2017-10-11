#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

static void traverse(char *path);
static int is_traversable(char *path);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: invalid arguments", argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; i++) {
    traverse(argv[i]);
  }

  exit(0);
}

static void traverse(char *path) {
  DIR *d = opendir(path);
  if (!d) {
    perror(path);
    exit(1);
  }

  char *parent = strcat(path, "/");
  struct dirent *ent;
  while ((ent = readdir(d))) {
    char *name = ent->d_name;

    char next[strlen(parent)];
    strcpy(next, parent);
    strcat(next, name);

    printf("%s\n", next);

    if (strcmp(name, ".") == 0 && strcmp(name, "..") == 0 && is_traversable(next)) {
      traverse(next);
    }
  }

  closedir(d);
}

static int is_traversable(char *path) {
  struct stat st;
  if (lstat(path, &st) < 0) {
    perror(path);
    exit(1);
  }

  return !S_ISLNK(st.st_mode) && S_ISDIR(st.st_mode);
}

