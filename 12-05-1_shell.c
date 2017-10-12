#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("myshell$ ");
  char input[100];
  gets(input);

  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork(2) failed\n");
    exit(1);
  }

  if (pid == 0) {
    execl(input, input, NULL);
    perror(input);
    exit(99);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }

  exit(0);
}
