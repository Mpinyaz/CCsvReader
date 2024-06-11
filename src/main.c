#include "csvparser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *f;
  const char *delimiter = DEFAULT_DELIMITER;

  if (argc < 2 || argc > 4) {
    printf("Usage: %s <filename> [--delimiter <delim> | -d <delim>]\n",
           argv[0]);
    exit(1);
  }

  for (int i = 1; i < argc; ++i) {
    if (strcmp(argv[i], "--delimiter") == 0 || strcmp(argv[i], "-d") == 0) {
      if (i + 1 < argc) {
        delimiter = argv[i + 1];
        i++;
      } else {
        fprintf(stderr, "Error: Delimiter flag requires a value\n");
        exit(2);
      }
    }
  }

  f = fopen(argv[1], "r");
  if (f == NULL) {
    fprintf(stderr, "Could not read file \n");
    perror(argv[1]);
    exit(2);
  } else {
    parse_csv(f, delimiter);
  }

  return 0;
}
