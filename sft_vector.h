#ifndef SFT_VECTOR_H
#define SFT_VECTOR_H

#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t size;
  size_t cap;
} sft_vec_info_t;

#define sft_vector(name, t) t* name = NULL;\
do {\
  sft_vec_info_t* info = malloc(sizeof(t) + sizeof(sft_vec_info_t));\
\
  if (info) {\
    info->size = 0;\
    info->cap = 1;\
    name = info + 1;\
  }\
} while(0)

#define sft_vector_init_cap(name, t, cap) t* name = NULL;\
do {\
  sft_vec_info_t* info = malloc((cap) ? sizeof(t) * cap : sizeof(t) + sizeof(sft_vec_info_t));\
\
  if (info) {\
    info->size = 0;\
    info->cap = (cap) ? cap : 1;\
    name = info + 1;\
  }\
} while(0)

#define sft_vector_init(name, t, count, init) t* name = NULL;\
do {\
  sft_vec_info_t* info = malloc(sizeof(t) * count + sizeof(sft_vec_info_t));\
\
  if (info) {\
    info->size = count;\
    info->cap = count;\
    name = (t*)(info + 1);\
\
    for (int i = 0; i < count; ++i) {\
      name[i] = init;\
    }\
  }\
} while(0)

#define sft_vector_init_list(name, t, ...) t* name = NULL;\
do {\
  const t array[] = {__VA_ARGS__};\
  sft_vec_info_t* info = malloc(sizeof(array) + sizeof(sft_vec_info_t));\
\
  if (info) {\
    info->size = sizeof(array) / sizeof(t);\
    info->cap = sizeof(array) / sizeof(t);\
    name = (t*)(info + 1);\
    memcpy(name, array, sizeof(array));\
  }\
} while(0)

#define sft_vector_free(vec) (free((sft_vec_info_t*)vec - 1))

#define sft_vector_reserve(vec, _size) do {\
  sft_vec_info_t* info = (sft_vec_info_t*)vec - 1;\
  if (_size != info->cap) {\
    sft_vec_info_t* new_info = realloc(info, _size * sizeof(*vec) + sizeof(sft_vec_info_t));\
    info = new_info;\
    info->cap = _size;\
    vec = (void*)(info + 1);\
  }\
} while (0)

#define sft_vector_resize(vec, _size) do {\
  sft_vec_info_t* info = (sft_vec_info_t*)vec - 1;\
  if (_size > info->cap || _size < info->size) {\
    sft_vec_info_t* new_info = realloc(info, _size * sizeof(*vec) + sizeof(sft_vec_info_t));\
    info = new_info;\
    info->cap = _size;\
    vec = (void*)(info + 1);\
  }\
  info->size = _size;\
} while (0)

#define sft_vector_info(vec) ((sft_vec_info_t*)vec - 1)

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
