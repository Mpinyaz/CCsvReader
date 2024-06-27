#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *csv_fileReader(const char *filename) {
  FILE *f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Could not read file \n");
    perror(filename);
    exit(2);
  }
  return f;
}

size_t get_max_line_length(FILE *f) {
  size_t max_length = 0;
  char line[1024]; // Temporary buffer for reading lines

  // Go through the file line by line
  while (fgets(line, sizeof(line), f)) {
    size_t current_length = strlen(line);
    if (current_length > max_length) {
      max_length = current_length;
    }
  }

  // Reset file pointer to the beginning of the file
  rewind(f);

  return max_length;
}
void parse_csv(FILE *f, const char *delimiter) {
  char line[1024];
  while (fgets(line, sizeof(line), f)) {
    char *token = strtok(line, delimiter);
    while (token) {
      printf("%s\n", token);
      token = strtok(NULL, delimiter);
    }
  }
}
