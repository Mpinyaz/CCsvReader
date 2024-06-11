#ifndef CSVPARSER_H
#define CSVPARSER_H
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
