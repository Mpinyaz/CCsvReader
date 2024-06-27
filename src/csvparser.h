#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <stdbool.h>
#include <stdio.h>
#define DEFAULT_DELIMITER ","
typedef struct {
  char **fields;
  int numOfFields;
} CsvRow;

typedef struct {
  char *filePath;
  char delim_char;
  bool hasHeader;
  int status;
  char *errMsg;
  CsvRow *header;
  FILE *sourcefile;
} CsvParser;

// CSV char constants
#define CSV_TAB 0x09
#define CSV_SPACE 0x20
#define CSV_CR 0x0d
#define CSV_LF 0x0a
// CSV Error Codes
-

#define CSV_PARSER_NO_ERR 0
#define CSV_BUFFER_EXCEEDED 1
#define CSV_EMPTY 20
#define CSV_COMMA 0x2c
#define CSV_QUOTE 0x22

    // CSV Parser Status

    enum CSV_STATUS {
      CSV_STATUS_OK,
      CSV_STATUS_FILE_NOT_FOUND,
      CSV_STATUS_ERROR
    };

// CSV Error Codes

#define CSV_PARSER_NO_ERR 0
#define CSV_BUFFER_EXCEEDED 1
#define CSV_EMPTY 20

// Function prototypes
#define int csv_init(FILE *f, const char *delimiter)

#endif
