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
  char delimiter;
  bool hasHeader;
  char *errMsg;
  CsvRow *header;
  FILE *sourcefile;
} CsvParser;

#endif
