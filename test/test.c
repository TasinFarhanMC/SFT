#include <assert.h>
#include <stdio.h>
#include <Vector/Vector.h>
#include <Vector/VecIO.h>

// Function to test all functions and macros in Vector.h
void testVector() {
  int *vec;
  struct Vec_Info *info;

  // Test Vec_Create
  assert(Vec_Create((void**)&vec, &info, sizeof(int), 5));

  // Test Vec_Push
  int data[] = {1, 2, 3, 4, 5};
  assert(Vec_Push((void**)&vec, info, data, 5));

  // Test Vec_Size and Vec_Capacity
  assert(Vec_Size(info) == 5);
  assert(Vec_Capacity(info) >= 5);

  // Test Vec_Front and Vec_Back
  assert(Vec_Front(info) == 0);
  assert(Vec_Back(info) == 4);

  // Test Vec_Reserve
  assert(Vec_Reserve((void**)&vec, info, 10));
  assert(Vec_Capacity(info) >= 10);

  // Test Vec_Resize
  assert(Vec_Resize((void**)&vec, info, 8));
  assert(Vec_Size(info) == 8);

  // Test Vec_Shrink_To_Fit
  assert(Vec_Shrink_To_Fit((void**)&vec, info));
  assert(Vec_Capacity(info) == Vec_Size(info));

  // Test Vec_Insert
  assert(Vec_Insert((void**)&vec, info, 2, &data, 3));
  assert(vec[2] == 1 && vec[3] == 2 && vec[4] == 3);

  // Test Vec_Erase
  size_t erased = Vec_Erase((void **) &vec, info, 2, 2);
  assert(erased == 2);
  assert(vec[2] == 3);

  // Test Vec_Clear
  Vec_Clear(info);
  assert(Vec_Size(info) == 0);

  // Clean up
  Vec_Free((void*)vec, info);
}

void testVecIO() {
  int *vec;
  struct Vec_Info *info;

  // Create a vector and populate it with data
  assert(Vec_Create((void**)&vec, &info, sizeof(int), 5));
  int data[] = {1, 2, 3, 4, 5};
  assert(Vec_Push((void**)&vec, info, &data, 5));

  // Test VecIO_Write and VecIO_Read
  FILE *file = fopen("testfile.bin", "wb");
  assert(file != NULL);
  assert(VecIO_Write((void*)vec, info, file));
  fclose(file);

  file = fopen("testfile.bin", "rb");
  assert(file != NULL);
  assert(VecIO_Read((void**)&vec, &info, sizeof(int), 5, file));

  // Verify the read vector matches the original data
  for (size_t i = 0; i < Vec_Size(info); ++i) {
    assert(vec[i] == data[i]);
  }

  fclose(file);

  file = fopen("testfile.bin", "rb");
  assert(file != NULL);
  size_t skipped = VecIO_Skip(1, file);
  fclose(file);
  assert(skipped == 1);

  // Test VecIO_Write_Buff and VecIO_Read_Buff
  FILE* buffFile = fopen("testbufffile.bin", "wb");
  assert(buffFile != NULL);
  assert(VecIO_Write_Buff((void*)data, sizeof(int), 5, buffFile));
  fclose(buffFile);

  buffFile = fopen("testbufffile.bin", "rb");
  assert(buffFile != NULL);
  int readBuff[5];
  size_t readSize;
  assert(VecIO_Read_Buff((void*)readBuff, 5, sizeof(int), &readSize, buffFile));
  fclose(buffFile);
  assert(readSize == 5);

  for (size_t i = 0; i < readSize; ++i) {
    assert(readBuff[i] == data[i]);
  }

  // Clean up
  Vec_Free((void*)vec, info);
}

int main() {
  // Run the tests
  testVector();
  testVecIO();
  printf("All tests passed!\n");

  return 0;
}
