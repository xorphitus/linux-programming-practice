#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static struct option longopts[] = {
  {"show", no_argument, NULL, 's'},
  {0, 0, 0, 0}
};

int main(int argc, char * argv[]) {
  int show_flag = 0;
  int opt;
  while ((opt = getopt_long(argc, argv, "s", longopts, NULL)) != -1) {
    switch (opt) {
      case 's':
        show_flag = 1;
        break;
      case '?':
        fprintf(stdout, "Unknown option");
        exit(1);
    }
  }

  for (int i = optind; i < argc; i++) {
    FILE *f = fopen(argv[i], "r");
    if (!f) {
      perror(argv[i]);
      exit(1);
    }

    int c;
    while((c = fgetc(f)) != EOF) {
      if (show_flag && c == '\t') {
        printf("\\t");
      } else if (show_flag && c == '\n') {
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
