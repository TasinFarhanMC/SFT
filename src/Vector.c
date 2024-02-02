#include <Vector/Vector.h>
#include <string.h>
#include <stdlib.h>

#define ceilf(value) ((size_t)value + (value > (size_t)value))

bool Vec_Init(void** data, struct Vec_Info* info, const size_t elem_size, const size_t growth) {
  *data = malloc(growth * elem_size);
  if (*data == NULL) {
    return false;
  }

  info->size = 0;
  info->elem_size = elem_size;
  info->capacity = growth;
  info->growth = growth;

  return true;
}

bool Vec_Push(void** data, struct Vec_Info* info, const void* push_data, const size_t push_size) {
  if (info->capacity == info->size) {
    info->capacity += (push_size > info->growth) ? ceilf((float)(push_size) / info->growth) * info->growth : info->growth;

    void* new_dataPtr = realloc(*data, info->capacity * info->elem_size);
    if (new_dataPtr == NULL) {
      return false;
    }
    *data = new_dataPtr;
  }

  memcpy(*data + info->size * info->elem_size, push_data, push_size * info->elem_size);
  info->size += push_size;
  return true;
}

size_t Vec_Pop(struct Vec_Info* info, const size_t count) {
  const size_t old_size = info->size;
  info->size = (count > info->size) ? 0 : info->size - count;
  return old_size - info->size;
}

bool Vec_Reserve(void** data, struct Vec_Info* info, const size_t capacity) {
  info->capacity = capacity;
  void* new_dataPtr = realloc(*data, capacity * info->elem_size);
  if (new_dataPtr == NULL) {
    return false;
  }
  *data = new_dataPtr;
  return true;
}

bool Vec_Resize(void** data, struct Vec_Info* info, const size_t size) {
  if (size > info->capacity) {
    info->capacity = ceilf((float)size / info->growth * info->growth);
    void* new_dataPtr = realloc(*data, info->capacity * info->elem_size);
    if (new_dataPtr == NULL) {
      return false;
    }
    *data = new_dataPtr;
  }
  info->size = size;
  return true;
}

bool Vec_Shrink_To_Fit(void** data, struct Vec_Info* info) {
  if (info->capacity > info->size) {
    void* new_dataPtr = realloc(*data, info->size * info->elem_size);
    if (new_dataPtr == NULL) {
      return false;
    }
    info->capacity = info->size;
    *data = new_dataPtr;
  }
  return true;
}

bool Vec_Insert(void** data, struct Vec_Info* info, const size_t pos, const void* insert_data, const size_t insert_size) {
  if (pos > info->size) {
    return false;
  }

  const size_t old_size = info->size;
  if (!Vec_Resize(data, info, old_size + insert_size)) {
    return false;
  }

  memmove(*data + (pos + insert_size) * info->elem_size, *data + pos * info->elem_size, (old_size - pos) * info->elem_size);
  memcpy(*data + pos * info->elem_size, insert_data, insert_size * info->elem_size);
  return true;
}

size_t Vec_Erase(void** data, struct Vec_Info* info, const size_t pos, size_t count) {
  const size_t new_size = info->size - count;
  const size_t available = info->size - pos;
  if (count > available) {
    count = available;
  }

  memmove(*data + pos * info->elem_size, *data + (pos + count) * info->elem_size, (new_size - pos) * info->elem_size);
  info->size = new_size;
  return count;
}
