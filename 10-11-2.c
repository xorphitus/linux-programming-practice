#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void touch(char *path);
static void experiment1(char *path);
static void experiment2(char *path);
static void experiment3(char *path, char *path2);

int main(int argc, char *argv[]) {
  if (argc != 5) {
    fprintf(stderr, "%s: invalid arguments\n", argv[0]);
    exit(1);
  }

  experiment1(argv[1]);
  experiment2(argv[2]);
  experiment3(argv[3], argv[4]);

  exit(0);
}

static void touch(char *path) {
  FILE *fp = fopen(path, "w");
  fclose(fp);
}

static void experiment1(char *path) {
  touch(path);

  int fd = open(path, O_RDONLY);
  if (rename(path, "hoge") < 0) {
    perror(path);
    printf("ex1: failed to rename\n");
  } else {
    close(fd);
    printf("ex1: succeed\n");
  }
}

static void experiment2(char *path) {
  touch(path);

  int fd = open(path, O_RDONLY);
  if (unlink(path) < 0) {
    perror(path);
    printf("ex2: failed to unlink\n");
  } else {
    close(fd);
    printf("ex2: succeed\n");
  }
}

static void experiment3(char *path, char *path2) {
  touch(path);
  touch(path2);

  int fd = open(path, O_RDONLY);
  if (rename(path2, "fuga") < 0) {
    perror(path);
    printf("ex3: failed to rename\n");
  } else {
    close(fd);
    printf("ex3: succeed\n");
  }
}
