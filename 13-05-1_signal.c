#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("waiting SIGINT...\n");

  if (pause() == -1) {
    perror(argv[0]);
    exit(1);
  } else {
    printf("SIGINT is trapped!\n");
    exit(0);
  }

  fprintf(stderr, "%s is terminated without SIGINT\n", argv[0]);
  exit(1);
}
