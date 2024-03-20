#ifndef SFT_VECTOR_H
#define SFT_VECTOR_H

#include <stdlib.h>
#include <string.h>

typedef struct {
  size_t size;
  size_t cap;
} sft_vector_info_t;

#define sft_vector(name, t, _size, _cap) t* name = NULL;\
do {\
  sft_vector_info_t* info = malloc(sizeof(t) * (_cap) + sizeof(sft_vector_info_t));\
\
  if (info) {\
    info->size = (_size);\
    info->cap = (_cap);\
    name = (t*)(info + 1);\
  }\
} while(0)

#define sft_vector_free(vec) (free((sft_vector_info_t*)vec - 1))

#define sft_vector_reserve(vec, _cap) do {\
  sft_vector_info_t* info = (sft_vector_info_t*)vec - 1;\
  if (_cap != info->cap) {\
    sft_vector_info_t* new_info = realloc(info, (_cap) * sizeof(*vec) + sizeof(sft_vector_info_t));\
    if (new_info) {\
      new_info->cap = (_cap);\
      new_info->size = (new_info->size > (_cap)) ? (_cap) : new_info->size;\
      vec = (void*)(new_info + 1);\
    } else {\
      free(info);\
      vec = NULL;\
    }\
  }\
} while (0)

#define sft_vector_resize(vec, _size) do {\
  sft_vector_info_t* info = (sft_vector_info_t*)vec - 1;\
  if (_size > info->cap) {\
    sft_vector_info_t* new_info = realloc(info, (_size) * sizeof(*vec) + sizeof(sft_vector_info_t));\
    if (new_info) {\
      new_info->cap = (_size);\
      new_info->size = (_size);\
      vec = (void*)(new_info + 1);\
    } else {\
      free(info);\
      vec = NULL;\
    }\
  } else {\
    info->size = (_size);\
  }\
} while (0)

#define sft_vector_info(vec) ((sft_vector_info_t*)vec - 1)

#define sft_vector_shrink_to_fit(vec) do {\
  sft_vector_info_t* info = (sft_vector_info_t*)vec - 1;\
  if (info->size != info->cap) {\
    sft_vector_info_t* new_info = realloc(info, sizeof(sft_vector_info_t) + info->size * sizeof(*vec));\
    new_info->cap = new_info->size;\
    vec = (void*)(new_info + 1);\
  }\
} while (0)

#define sft_vector_push(vec, val) do {\
  sft_vector_info_t* info = (sft_vector_info_t*)vec - 1;\
\
  if (info->cap == info->size) {\
    sft_vector_info_t* new_info = realloc(info, info->cap * 2 * sizeof(*vec) + sizeof(sft_vector_info_t));\
    info = new_info;\
    info->cap *= 2;\
    vec = (void*)(info + 1);\
  }\
\
  vec[info->size++] = val;\
} while(0)

#define sft_vec_pop(vec) (vec[--((sft_vector_info_t*)vec - 1)->size])

#define SFT_VECTOR_MERGE_FRONT 0
#define SFT_VECTOR_MERGE_END 1

#define sft_vector_merge(vec, arr, _size, pos, offset) do {\
  sft_vector_info_t* info = (sft_vector_info_t*)vec - 1;\
\
  if (pos) {\
    if (offset) {\
      const size_t total_size = info->size + (_size);\
      if (total_size > info->cap) {\
        sft_vector_info_t* new_info = realloc(info, total_size * sizeof(*vec) + sizeof(sft_vector_info_t));\
        if (new_info) {\
          new_info->cap = total_size;\
          vec = (void*)(new_info + 1);\
          memmove(vec + info->size + (_size) - offset, vec + info->size - offset, offset * sizeof(*vec));\
          memcpy(vec + info->size - offset, arr, (_size) * sizeof(*vec));\
          new_info->size = total_size;\
        } else {\
          free(info);\
          vec = NULL;\
        }\
      } else {\
        memmove(vec + info->size + (_size) - offset, vec + info->size - offset, offset * sizeof(*vec));\
        memcpy(vec + info->size - offset, arr, (_size) * sizeof(*vec));\
        info->size = total_size;\
      }\
    } else {\
      const size_t total_size = info->size + (_size);\
      if (total_size > info->cap) {\
        sft_vector_info_t* new_info = realloc(info, total_size * sizeof(*vec) + sizeof(sft_vector_info_t));\
        if (new_info) {\
          new_info->cap = total_size;\
          vec = (void*)(new_info + 1);\
          memcpy(vec + new_info->size, arr, (_size) * sizeof(*vec));\
          new_info->size = total_size;\
        } else {\
          free(info);\
          vec = NULL;\
        }\
      } else {\
        memcpy(vec + info->size, arr, (_size) * sizeof(*vec));\
        info->size = total_size;\
      }\
    }\
  } else {\
    if (offset == info->size) {\
      const size_t total_size = info->size + (_size);\
      if (total_size > info->cap) {\
        sft_vectorinfo_t* new_info = realloc(info, total_size * sizeof(*vec) + sizeof(sft_vector_info_t));\
        if (new_info) {\
          new_info->cap = total_size;\
          vec = (void*)(new_info + 1);\
          memcpy(vec + new_info->size, arr, (_size) * sizeof(*vec));\
          new_info->size = total_size;\
        } else {\
          free(info);\
          vec = NULL;\
        }\
      } else {\
        memcpy(vec + info->size, arr, (_size) * sizeof(*vec));\
        info->size = total_size;\
      }\
    } else {\
      const size_t total_size = info->size + (_size);\
      if (total_size > info->cap) {\
        sft_vector_info_t* new_info = realloc(info, total_size * sizeof(*vec) + sizeof(sft_vector_info_t));\
        if (new_info) {\
          new_info->cap = total_size;\
          vec = (void*)(new_info + 1);\
          memmove(vec + (_size), vec + offset, info->size * sizeof(*vec));\
          memcpy(vec, arr, (_size) * sizeof(*vec));\
          new_info->size = total_size;\
        } else {\
          free(info);\
          vec = NULL;\
        }\
      } else {\
        memmove(vec + (_size), vec + offset, info->size * sizeof(*vec));\
        memcpy(vec, arr, (_size) * sizeof(*vec));\
        info->size = total_size;\
      }\
    }\
  }\
} while(0)

#endif
