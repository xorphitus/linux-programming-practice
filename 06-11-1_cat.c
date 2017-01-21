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
    while((c = fgetc(f)) != EOF) {
      if (c == '\t') {
        printf("\\t");
      } else if (c == '\n') {
        printf("$\n");
      } else {
        if (putchar(c) < 0) {
          fclose(f);
          exit(1);
        }
      }
    }
    fclose(f);
  }

  exit(0);
}
