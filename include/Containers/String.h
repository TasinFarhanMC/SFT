#ifndef STRING_H
#define STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
 extern "C" {
#endif

char* String(const char* str);

int __str_ncat(char** dest, const char* src, size_t n);
int __str_ncpy(char** dest, const char* src, size_t n);

#define Str_nCat(dest, src) (__str_ncat(&dest, src, strlen(src)))
#define Str_nCpy(dest, src) (__str_ncpy(&dest, src, strlen(src)))

char* Str_nDup(const char* str, size_t n);

#define Str_Cat(dest, src) (__str_ncat(&dest, src, strlen(src)))
#define Str_Cpy(dest, src) (__str_ncpy(&dest, src, strlen(src)))
#define Str_Dup(str) (Str_nDup(str, strlen(str)))

char* Str_fScan(FILE* file);
char* Str_fGet(FILE* file);

#define Str_Scan() (Str_fScan(stdin))
#define Str_Get() (Str_fGet(stdin))

#define Str_Free(str) (free((size_t*)str - 1))

#ifdef __cplusplus
  }
#endif

#endif
