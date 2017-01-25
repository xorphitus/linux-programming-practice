#include <stdio.h>
#include <stdlib.h>

static void do_tail(FILE *f);

#define DEFAULT_N_LINES 10

int main(int argc, char * argv[]) {
  for (int i = 1; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      perror(argv[i]);
      exit(1);
    }
    do_tail(f);
    fclose(f);
  }

  exit(0);
}

static void do_tail(FILE *f) {
  int line_feeds = 0;
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      line_feeds++;
    }
  }

  rewind(f);

  int current = 0;
  while ((c = fgetc(f)) != EOF) {
    if (c == '\n') {
      current++;
    }

    if (current > line_feeds - DEFAULT_N_LINES) {
      if (putchar(c) < 0) exit(1);
    }
  }
}
