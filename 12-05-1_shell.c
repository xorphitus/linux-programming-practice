#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

#define MAX_ARGS 100

static void split(char *str, char *results[]);
static char* trim(char *str);

int main(int argc, char *argv[]) {
  while (1) {
    printf("myshell$ ");
    char input[100];
    // TODO: fgetsに変更
    gets(input);

    char *command[MAX_ARGS] = {};
    split(input, command);

    if (strcmp(command[0], "exit") == 0) {
      exit(0);
    }

    pid_t pid = fork();
    if (pid < 0) {
      fprintf(stderr, "fork(2) failed\n");
      exit(1);
    }

    if (pid == 0) {
      // TODO: オプションと引数を同時に渡すとエラーになる件
      execvp(command[0], command);
      perror(input);
      exit(99);
    } else {
      int status;
      waitpid(pid, &status, 0);
    }
  }
}

static void split(char *str, char *results[]) {
  results[0] = strtok(str, " ");

  char *token;
  int i = 1;
  while((token = strtok(NULL, "")) && i < MAX_ARGS) {
    token = trim(token);
    if (token[0] == '\0') {
      continue;
    }
    results[i] = token;
    i++;
  }
}

static char* trim(char *str) {
  if (str && *str) {
    size_t len = strlen(str);
    for (size_t i = 0; i < len; i++) {
      if (isspace(str[i])) {
        str[i] = '\0';
      }
    }
  }

  return str;
}
