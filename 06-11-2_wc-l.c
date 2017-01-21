#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
  for (int i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      perror(argv[i]);
      exit(1);
    }

    int c;
    int lines = 0;
    while((c = fgetc(f)) != EOF) {
      if (c == '\n') {
        lines++;
      }
    }
    printf("%d", lines);
    fclose(f);
  }

  exit(0);
}

