#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

static void sighandler(int n);

int main(int argc, char *argv[]) {
  printf("waiting SIGINT...\n");

  struct sigaction act;
  act.sa_handler = sighandler;
  sigemptyset(&act.sa_mask);
  if (sigaction(SIGINT, &act, NULL) < 0) {
    perror(argv[0]);
    exit(1);
  }

  if (pause() < 0) {
    perror(argv[0]);
    exit(1);
  }

  fprintf(stderr, "%s is terminated without SIGINT\n", argv[0]);
  exit(1);
}

static void sighandler(int n) {
  printf("SIGINT is trapped!\n");
  exit(0);
}
