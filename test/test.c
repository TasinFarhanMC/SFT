#include <stdio.h>
#include <stdlib.h>
#include <Vector/VecIO.h>

void printVector(int* vec, struct Vec_Info* info) {
  printf("Vector: [");
  for (size_t i = 0; i < Vec_Size(info); ++i) {
    printf("%d", vec[i]);
    if (i < Vec_Size(info) - 1) {
      printf(", ");
    }
  }
  printf("]\n");
}

int main() {
  // Test Vec_Create
  int* vec;
  struct Vec_Info* info;
  if (!Vec_Create((void**)&vec, &info, sizeof(int), 5)) {
    fprintf(stderr, "Vec_Create failed.\n");
    return 1;
  }

  // Fill the vector with data
  int data[] = {1, 2, 3, 4, 5};
  if (!Vec_Push((void**)&vec, info, &data, 5)) {
    fprintf(stderr, "Vec_Push failed.\n");
    Vec_Free((void*)vec, info);
    return 1;
  }

  // Test VecIO_Write multiple times
  FILE* file = fopen("testfile_skip.bin", "wb");
  if (!file) {
    fprintf(stderr, "Failed to open file for writing.\n");
    Vec_Free((void*)vec, info);
    return 1;
  }

  for (int i = 0; i < 5; ++i) {
    if (!VecIO_Write((void*)vec, info, file)) {
      fprintf(stderr, "VecIO_Write failed.\n");
      fclose(file);
      Vec_Free((void*)vec, info);
      return 1;
    }
  }

  fclose(file);

  // Test VecIO_Skip
  file = fopen("testfile_skip.bin", "rb");
  if (!file) {
    fprintf(stderr, "Failed to open file for reading.\n");
    Vec_Free((void*)vec, info);
    return 1;
  }

  // Skip the first two vectors
  size_t skipped = VecIO_Skip(2, file);
  printf("Skipped %zu vectors.\n", skipped);

  // Read and print the remaining vectors
  for (int i = 0; i < 3; ++i) {
    if (!VecIO_Read((void**)&vec, &info, sizeof(int), 5, file)) {
      fprintf(stderr, "VecIO_Read failed.\n");
      fclose(file);
      Vec_Free((void*)vec, info);
      return 1;
    }

    printVector(vec, info);
  }

  fclose(file);

  // Cleanup
  Vec_Free((void*)vec, info);

  return 0;
}
