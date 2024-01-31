#include <Vector/Vector.h>
#include <string.h>

#define ceilf(value) ((size_t)value + (value > (size_t)value))

bool Vec_Create(void** vec, struct Vec_Info** info, const size_t elem_size, const size_t growth) {
  *vec = malloc(growth * elem_size);
  if (*vec == NULL) {
    return false;
  }

  (*info) = malloc(sizeof(struct Vec_Info));
  if (*info == NULL) {
    free(*vec);
    return false;
  }

  (*info)->size = 0;
  (*info)->elem_size = elem_size;
  (*info)->capacity = growth;
  (*info)->growth = growth;

  return true;
}

bool Vec_Push(void** vec, struct Vec_Info* info, const void* data, const size_t size) {
  if (info->capacity == info->size) {
    info->capacity += (size > info->growth) ? ceilf((float)(size) / info->growth) * info->growth : info->growth;

    void* new_vec = realloc(*vec, info->capacity * info->elem_size);
    if (new_vec == NULL) {
      return false;
    }
    *vec = new_vec;
  }

  memcpy(*vec + info->size * info->elem_size, data, size * info->elem_size);
  info->size += size;
  return true;
}

size_t Vec_Pop(struct Vec_Info* info, const size_t count) {
  const size_t old_size = info->size;
  info->size = (count > info->size) ? 0 : info->size - count;
  return old_size - info->size;
}

bool Vec_Reserve(void** vec, struct Vec_Info* info, const size_t capacity) {
  info->capacity = capacity;
  void* new_vec = realloc(*vec, capacity * info->elem_size);
  if (new_vec == NULL) {
    return false;
  }
  *vec = new_vec;
  return true;
}

bool Vec_Resize(void** vec, struct Vec_Info* info, const size_t size) {
  if (size > info->capacity) {
    info->capacity = ceilf((float)size / info->growth * info->growth);
    void* new_vec = realloc(*vec, info->capacity * info->elem_size);
    if (new_vec == NULL) {
      return false;
    }
    *vec = new_vec;
  }
  info->size = size;
  return true;
}

bool Vec_Shrink_To_Fit(void** vec, struct Vec_Info* info) {
  if (info->capacity > info->size) {
    void* new_vec = realloc(*vec, info->size * info->elem_size);
    if (new_vec == NULL) {
      return false;
    }
    info->capacity = info->size;
    *vec = new_vec;
  }
  return true;
}

bool Vec_Insert(void** vec, struct Vec_Info* info, const size_t pos, const void* data, const size_t size) {
  if (pos > info->size) {
    return false;
  }

  const size_t old_size = info->size;
  if (!Vec_Resize(vec, info, old_size + size)) {
    return false;
  }

  memmove(*vec + (pos + size) * info->elem_size, *vec + pos * info->elem_size, (old_size - pos) * info->elem_size);
  memcpy(*vec + pos * info->elem_size, data, size * info->elem_size);
  return true;
}

size_t Vec_Erase(void** vec, struct Vec_Info* info, const size_t pos, size_t count) {
  const size_t new_size = info->size - count;
  const size_t available = info->size - pos;
  if (count > available) {
    count = available;
  }

  memmove(*vec + pos * info->elem_size, *vec + (pos + count) * info->elem_size, (new_size - pos) * info->elem_size);
  info->size = new_size;
  return count;
}
