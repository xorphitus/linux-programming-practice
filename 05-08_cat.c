#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_echo();
static void do_cat(const char *path);
static void die(const char *s);

int main(int argc, char * argv[]) {
  if (argc < 1) {
    fprintf(stderr, "%s: file name not given\n", argv[0]);
    exit(1);
  }
  if (argc == 1) {
    do_echo();
  } else {
    for (int i = 1; i < argc; i++) {
      do_cat(argv[i]);
    }
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static void do_echo() {
  unsigned char buf[BUFFER_SIZE];

  for(;;) {
    int n = read(STDIN_FILENO, buf, sizeof buf);
    if (n == 0) break;
    write(STDOUT_FILENO, buf, n);
  }
}

static void do_cat(const char *path) {
  unsigned char buf[BUFFER_SIZE];

  int fd = open(path, O_RDONLY);
  if (fd < 0) die(path);
  for (;;) {
    int n = read(fd, buf, sizeof buf);
    if (n < 0) die(path);
    if (n == 0) break;
    if (write(STDOUT_FILENO, buf, n) < 0) die(path);
  }
  if (close(fd) < 0) die(path);
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
