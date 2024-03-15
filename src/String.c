#include <Containers/String.h>

char* String(const char* str) {
  const size_t len = strlen(str);
  char* newstr = NULL;
  size_t* cap = malloc(sizeof(size_t) + len + 1);
  if (cap) {
    *cap = len;
    newstr = (char*)(cap + 1);
    strcpy(newstr, str);
  }
  return newstr;
}

int __str_ncat(char** dest, const char* src, const size_t n) {
  size_t* cap = (size_t*)dest - 1;
  const size_t newLen = strlen(*dest) + strlen(src) + 1;

  if (*cap <= newLen) {
    size_t* newcapptr = realloc(cap, sizeof(size_t) + newLen);
    if (newcapptr == NULL) {
      free(cap);
      return 1;
    }
    cap = newcapptr;
    *dest = (char*)(cap + 1);
  }

  strncat(*dest, src, n);
  return 0;
}

int __str_ncpy(char** dest, const char* src, const size_t n) {
  size_t* cap = (size_t*)dest - 1;
  const size_t newLen = strlen(src) + 1;

  if (*cap <= newLen) {
    size_t* newcapptr = realloc(cap, sizeof(size_t) + newLen);
    if (newcapptr == NULL) {
      free(cap);
      return 1;
    }
    cap = newcapptr;
    *dest = (char*)(cap + 1);
  }

  strncat(*dest, src, n);
  return 0;
}

char* Str_nDup(const char* str, const size_t n) {
  char* newstr = NULL;
  size_t* cap = malloc(sizeof(size_t) + n + 1);
  if (cap) {
    *cap = n;
    newstr = (char*)(cap + 1);
    strncpy(newstr, str, n);
  }
  return newstr;
}

char* Str_fScan(FILE* file) {
  char* str = NULL;
  size_t* cap = malloc(sizeof(size_t) + 11);
  size_t len = 0;
  if (cap == NULL) {
    return NULL;
  }
  *cap = 11;
  str = (char*)(cap + 1);
  char c;

  while (1){
    c = getc(file);

    switch (c) {
    case '\n':
    case '\t':
    case ' ':
    case EOF:
      str[len] = '\0';
      return str;

    default:
      break;
    }

    if (*cap <= len) {
      size_t* newcapptr = realloc(cap, sizeof(size_t) + *cap * 2);
      if (newcapptr == NULL) {
        free(cap);
        return NULL;
      }
      cap = newcapptr;
      str = (char*)(cap + 1);
    }

    str[len++] = c;
  }
}

char* Str_fGet(FILE* file) {
  char* str = NULL;
  size_t* cap = malloc(sizeof(size_t) + 11);
  size_t len = 0;
  if (cap == NULL) {
    return NULL;
  }
  *cap = 11;
  str = (char*)(cap + 1);

  while (1){
    const char c = getc(file);

    switch (c) {
    case '\n':
    case EOF:
      str[len] = '\0';
      return str;

    default:
      break;
    }

    if (*cap <= len) {
      size_t* newcapptr = realloc(cap, sizeof(size_t) + *cap * 2);
      if (newcapptr == NULL) {
        free(cap);
        return NULL;
      }
      cap = newcapptr;
      str = (char*)(cap + 1);
    }

    str[len++] = c;
  }
}