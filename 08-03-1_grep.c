#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_grep(regex_t *pat, FILE *f);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fputs("no pattern\n", stderr);
    exit(1);
  }

  int reg_flag = REG_EXTENDED | REG_NOSUB | REG_NEWLINE;

  int opt;
  while ((opt = getopt(argc, argv, "iv")) != -1) {
    switch (opt) {
      case 'i':
        reg_flag = reg_flag | REG_ICASE;
        break;
      case 'v':
        /* TODO */
        break;
      case '?':
        fprintf(stdout, "Unknown option");
        exit(1);
    }
  }

  regex_t pat;
  int err = regcomp(&pat, argv[1], reg_flag);
  if (err != 0) {
    char buf[1024];

    regerror(err, &pat, buf, sizeof buf);
    puts(buf);
    exit(1);
  }

  if (argc == 1 + optind) {
    do_grep(&pat, stdin);
  } else {
    for (int i = 1 + optind; i < argc; i++) {
      FILE *f;

      f = fopen(argv[i], "r");
      if (!f) {
        perror(argv[i]);
        exit(1);
      }
      do_grep(&pat, f);
      fclose(f);
    }
    regfree(&pat);
    exit(0);
  }
}

static void do_grep(regex_t *pat, FILE *src) {
  char buf[4096];

  while (fgets(buf, sizeof buf, src)) {
    if (regexec(pat, buf, 0, NULL, 0) == 0) {
      fputs(buf, stdout);
    }
  }
}
