#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void experiment1(char *path);
static void experiment2(char *path);
static void experiment3(char *path, char *path2);

int main(int argc, char *argv[]) {
  if (argc != 4) {
    fprintf(stderr, "%s: invalid arguments\n", argv[0]);
    exit(1);
  }

  experiment1(argv[1]);
  experiment2(argv[2]);
  experiment3(argv[3], argv[4]);

  exit(0);
}

static void experiment1(char *path) {
  int fd = open(path, O_RDONLY);
  if (rename(path, "hoge") < 0) {
    perror(path);
    exit(1);
  }
  close(fd);
}

static void experiment2(char *path) {
  int fd = open(path, O_RDONLY);
  if (unlink(path) < 0) {
    perror(path);
    exit(1);
  }
  close(fd);
}

static void experiment3(char *path, char *path2) {
  int fd = open(path, O_RDONLY);
  if (rename(path2, "fuga") < 0) {
    perror(path);
    exit(1);
  }
  close(fd);
}
