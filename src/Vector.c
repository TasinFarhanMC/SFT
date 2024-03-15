#include <Containers/Vector.h>

void* __vec_init(const size_t type_size, const size_t size, const size_t cap) {
  void* vec = NULL;
  __vec_info* info = malloc(type_size * size + sizeof(__vec_info));

  if (info) {
    info->size = size;
    info->cap = cap;
    info->type_size = type_size;
    vec = info + 1;
  }

  return vec;
}
