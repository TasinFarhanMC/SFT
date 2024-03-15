#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <string.h>
#include "def.h"

typedef struct {
  size_t size;
  size_t cap;
  size_t type_size;
} __vec_info;

#define Vector(T) (__vec_init(sizeof(T), 0, 1))
#define Vec_InitCap(T, Cap) (__vec_init(sizeof(T), 0, Cap))
#define Vec_InitSize(T, Size) (__vec_init(sizeof(T), Size, Size));
#define Vec_InitList(Name, T, ...) T* Name = NULL;\
do {\
  const T array[] = {__VA_ARGS__};\
  __vec_info* info = malloc(sizeof(array) + sizeof(__vec_info));\
\
  if (info) {\
    info->size = sizeof(array) / sizeof(T);\
    info->cap = sizeof(array) / sizeof(T);\
    info->type_size = sizeof(T);\
    Name = (T*)(info + 1);\
    memcpy(Name, array, sizeof(array));\
  }\
} while(0)
void* __vec_init(size_t type_size, size_t size, size_t cap);

#define Vec_Free(vec) (free((__vec_info*)vec - 1))

#define Vec_Resize(Vec, Size) do {\
  __vec_info* info = (__vec_info*)Vec - 1;\
  if (Size > info->cap) {\
    __vec_info* new_info = realloc(info, Size * info->type_size + sizeof(__vec_info));\
    info = new_info;\
    info->cap = Size;\
    Vec = (TYPEOF(Vec))(info + 1);\
  }\
  info->size = Size;\
} while (0)

#define Vec_Reserve(Vec, Capacity) do {\
  __vec_info* info = (__vec_info*)Vec - 1;\
  if (Capacity > info->cap) {\
    __vec_info* new_info = realloc(info, Capacity * info->type_size + sizeof(__vec_info));\
    if (new_info) {\
      new_info->cap = Capacity;\
      Vec = (TYPEOF(Vec))(new_info + 1);\
    }\
  }\
} while (0)

#define Vec_Size(Vec) (((__vec_info*)Vec - 1)->size)
#define Vec_Cap(Vec) (((__vec_info*)Vec - 1)->cap)

#define Vec_Empty(Vec) (!(((__vec_info*)Vec - 1)->size))
#define Vec_Clear(Vec) (((__vec_info*)Vec - 1)->size = 0)

#define Vec_Back(Vec) (Vec + ((__vec_info*)Vec - 1)->size - 1)

#define Vec_Shrink_To_Fit(Vec) do {\
  __vec_info* info = (__vec_info*)Vec - 1;\
  __vec_info* new_info = realloc(info, sizeof(__vec_info) + info->size * info->type_size);\
  new_info->cap = new_info->size;\
  Vec = (TYPEOF(Vec))(new_info + 1);\
} while (0)

#define Vec_Push(Vec, Val) do {\
  __vec_info* info = (__vec_info*)(Vec) - 1;\
\
  if (info->cap == info->size) {\
    const size_t new_cap = info->cap * 2;\
    __vec_info* new_info = realloc(info, new_cap  * info->size + sizeof(__vec_info));\
    info = new_info;\
    info->cap = new_cap;\
    Vec = (TYPEOF(Vec))(info + 1);\
  }\
\
  Vec[info->size++] = Val;\
} while(0)

#define Vec_Pop(Vec) (Vec[--((__vec_info*)Vec - 1)->size])

#endif
