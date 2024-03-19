#ifndef SFT_INPUT_H
#define SFT_INPUT_H

#include <stdio.h>
#include <stdbool.h>

bool sft_input_scans(char* buffer, size_t size);
bool sft_input_fscans(FILE* file, char* buffer, size_t size);

int sft_input_gets(char* buffer, size_t size, bool inc_newline);
int sft_input_fgets(FILE* file, char* buffer, size_t size, bool inc_newline);

#ifdef SFT_INPUT_IMP  
#include <string.h>

bool sft_input_scans(char* buffer, const size_t size) {
  buffer[size - 2] = 0;
  char format[24];
  sprintf(format, "%%%zus", size);

  if (!scanf(format, buffer) || buffer[size - 2] != 0) {
    return false;
  }

  return true;
}

bool sft_input_fscans(FILE* file, char* buffer, const size_t size) {
  buffer[size - 2] = 0;
  char format[24];
  sprintf(format, "%%%zus", size);

  if (!fscanf(file, format, buffer) || buffer[size - 2] != 0) {
    return false;
  }

  return true;
}
#endif
#endif
