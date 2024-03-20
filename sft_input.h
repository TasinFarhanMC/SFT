#ifndef SFT_INPUT_H
#define SFT_INPUT_H

#include <stdio.h>
#include <stdbool.h>

bool sft_input_scans(char* buffer, size_t size);
bool sft_input_fscans(FILE* file, char* buffer, size_t size);

bool sft_input_gets(char* buffer, size_t size, bool inc_newline);
bool sft_input_fgets(char* buffer, size_t size, bool inc_newline, FILE* file);

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

bool sft_input_gets(char* buffer, size_t size, bool inc_newline) {
  buffer[size - 2] = 0; 
  fgets(buffer, size, stdin);

  if (inc_newline) {
    if (buffer[size - 2] == 0 || buffer[size - 2] == '\n') {
      return true;
    } else {
      scanf("%*s");
      return false;
    }
  } else {
    if (buffer[size - 2] == '\n') {
      buffer[size - 2] = 0;
      return true;
    }

    if (buffer[size - 2] == 0) {
      buffer[strlen(buffer) - 2] = 0;
      return true;
    } else {
      scanf("%*s");
      return false;
    }
  }
}

bool sft_input_fgets(char* buffer, size_t size, bool inc_newline, FILE* file) {
  buffer[size - 2] = 0; 
  fgets(buffer, size, file);

  if (inc_newline) {
    if (buffer[size - 2] == 0 || buffer[size - 2] == '\n') {
      return true;
    } else {
      scanf("%*s");
      return false;
    }
  } else {
    if (buffer[size - 2] == '\n') {
      buffer[size - 2] = 0;
      return true;
    }

    if (buffer[size - 2] == 0) {
      buffer[strlen(buffer) - 2] = 0;
      return true;
    } else {
      scanf("%*s");
      return false;
    }
  }
}

#endif
#endif
