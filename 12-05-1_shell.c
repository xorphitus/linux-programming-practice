#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("myshell$ ");
  char input[100];
  // TODO: fgetsに変更
  gets(input);

  pid_t pid = fork();
  if (pid < 0) {
    fprintf(stderr, "fork(2) failed\n");
    exit(1);
  }

  if (pid == 0) {
    // TODO: 引数を渡せるようにする
    // TODO: コマンドをフルパス指定じゃなくてOKにする
    execl(input, input, NULL);
    perror(input);
    exit(99);
  } else {
    int status;
    waitpid(pid, &status, 0);
  }

  // TODO: 1コマンドだけで終了しないようにする
  exit(0);
}
