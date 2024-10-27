#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *csv_fileReader(const char *filename) {
  FILE *f;
  if ((f = fopen(filename, "r")) == NULL) {
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
size_t strip_CRLF(const char *line) {
  size_t line_len = strlen(line);

  if (line_len > 0 && line[line_len - 1] == '\n') {
    line_len--;
    if (line_len > 0 && line[line_len - 1] == '\r') {
      line_len--;
    }
  } else if (line_len > 0 && line[line_len - 1] == '\r') {
    line_len--;
  }

  return line_len;
}

int parse_line(const char *line, const char *delim, char ***out_storage) {
  const char *start_ptr, *end_ptr;
  int tokens_found = 0;
  int delim_size = strlen(delim);

  if (*out_storage != NULL) {
    return -4;
  }
  if (!line || !delim) {
    return -1;
  }

  if (delim_size == 0) {
    return -2;
  }

  size_t line_len = strip_CRLF(line);

  start_ptr = line;
  while ((end_ptr = strstr(start_ptr, delim))) {
    tokens_found++;
    start_ptr = end_ptr + delim_size;
  }

  if (start_ptr < line + line_len) {
    tokens_found++;
  };

  int *start_idx = malloc(tokens_found * sizeof(int));
  int *end_idx = malloc(tokens_found * sizeof(int));

  if (!start_idx || !end_idx) {
    free(start_idx);
    free(end_idx);
    return -3;
  }

  tokens_found = 0;
  start_ptr = line;

  while ((end_ptr = strstr(start_ptr, delim))) {
    start_idx[tokens_found] = start_ptr - line;
    end_idx[tokens_found] = end_ptr - line;
    tokens_found++;
    start_ptr = end_ptr + delim_size;
  }

  if (start_ptr < line + line_len) {
    start_idx[tokens_found] = start_ptr - line;
    end_idx[tokens_found] = line_len;
    tokens_found++;
  }

  *out_storage = malloc(tokens_found * sizeof(char *));
  if (*out_storage == NULL) {
    free(start_idx);
    free(end_idx);
    return -3;
  }

  for (int i = 0; i < tokens_found; i++) {
    int token_length = end_idx[i] - start_idx[i];
    (*out_storage)[i] = malloc(token_length + 1);
    if ((*out_storage)[i] == NULL) {
      for (int j = 0; j < i; j++)
        free((*out_storage)[j]);
      free(*out_storage);
      free(start_idx);
      free(end_idx);
      return -3;
    }
    strncpy((*out_storage)[i], line + start_idx[i], token_length);
    (*out_storage)[i][token_length] = '\0';
  }
  free(start_idx);
  free(end_idx);

  return tokens_found;
}
