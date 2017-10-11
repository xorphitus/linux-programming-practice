/* WIP */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_grep(regex_t *pat, FILE *f, int invert);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fputs("no pattern\n", stderr);
    exit(1);
  }

  int reg_flag = REG_EXTENDED | REG_NOSUB | REG_NEWLINE;
  int invert = 0;

  int opt;
  while ((opt = getopt(argc, argv, "iv")) != -1) {
    switch (opt) {
      case 'i':
        reg_flag |= REG_ICASE;
        break;
      case 'v':
        invert = 1;
        break;
      case '?':
        fprintf(stdout, "Unknown option");
        exit(1);
    }
  }

  regex_t pat;
  int err = regcomp(&pat, argv[0 + optind], reg_flag);
  if (err != 0) {
    char buf[1024];

    regerror(err, &pat, buf, sizeof buf);
    puts(buf);
    exit(1);
  }

  if (argc == 1 + optind) {
    do_grep(&pat, stdin, invert);
  } else {
    for (int i = 1 + optind; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_grep(&pat, f, invert);
      fclose(f);
    }
    regfree(&pat);
  }

  exit(0);
}

static void do_grep(regex_t *pat, FILE *src, int invert) {
  char buf[4096];

  while (fgets(buf, sizeof buf, src)) {
    int match = regexec(pat, buf, 0, NULL, 0);
    if (match == 0 && !invert) {
      fputs(buf, stdout);
    } else if (match != 0 && invert) {
      fputs(buf, stdout);
    }
  }
}
