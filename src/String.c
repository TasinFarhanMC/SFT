#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct String {
  char* data;
  size_t len;
  size_t capacity;
};

bool Str_Set(struct String* str, const char* c_str) {
  str->len = strlen(c_str);

  if (str->data == NULL) {
    str->data = malloc(str->len);
    str->capacity = str->len;
  } else if (str->len > str->capacity) {
    char* new_data = realloc(str->data, str->len);
    if (new_data == NULL) {
      return false;
    }
    str->data = new_data;
    str->capacity = str->len;
  }

  memcpy(str->data, c_str, str->len);
  return true;
}

