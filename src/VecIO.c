#include <Vector/VecIO.h>

bool VecIO_Write_Buff(const void* buff, const size_t elem_size, const size_t size, FILE* file) {
  const size_t array_size = elem_size * size;
  const long pos = ftell(file);

  if (fwrite(&array_size, sizeof(size_t), 1, file) != 1) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  if (fwrite(buff, elem_size, size, file) != size) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  return true;
}

bool VecIO_Read_Buff(void* buff, const size_t buff_capacity, const size_t elem_size, size_t* size, FILE* file) {
  size_t array_size;
  const long pos = ftell(file);

  if (fread(&array_size, sizeof(size_t), 1, file) != 1) {
    fseek(file, pos, SEEK_SET);
    return false;
  }
  const size_t local_size = array_size / elem_size;

  if (buff_capacity < local_size) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  if (fread(buff, elem_size, local_size, file) != local_size) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  if (size != NULL) {
    *size = local_size;
  }

  return true;
}

bool VecIO_Write(const void* vec, const struct Vec_Info* info, FILE* file) {
  const long pos = ftell(file);
  const size_t array_size = info->size * info->elem_size;

  if (fwrite(&array_size, sizeof(size_t), 1, file) != 1) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  if (fwrite(vec, info->elem_size, info->size, file) != info->size) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  return true;
}

bool VecIO_Read(void** vec, struct Vec_Info** info, const size_t elem_size, const size_t growth, FILE* file) {
  if (!Vec_Create(vec, info, elem_size, growth)) {
    return false;
  }

  size_t array_size;
  const long pos = ftell(file);

  if (fread(&array_size, sizeof(size_t), 1, file) != 1) {
    fseek(file, pos, SEEK_SET);
    return false;
  }

  if (!Vec_Resize(vec, *info, array_size / elem_size)) {
    return false;
  }

  if (fread(*vec, elem_size, (*info)->size, file) != (*info)->size) {
    return false;
  }

  return true;
}

size_t VecIO_Skip(const size_t count, FILE* file) {
  size_t array_size;
  size_t skips = 0;

  for (; skips < count; ++skips) {
    const long pos = ftell(file);
    if (fread(&array_size, sizeof(size_t), 1, file) != 1) {
      fseek(file, pos, SEEK_SET);
      break;
    }
    fseek(file, array_size, SEEK_CUR);
  }

  return skips;
}
