#include <Vector/Vector.h>
#include <stdio.h>

int main() {
  struct Int_Vec vec;
  Vec_Create(&vec.data, &vec.info, sizeof(int), 5);
  const int data[] = {1, 2, 3, 4, 5};
  Vec_Push(&vec.data, vec.info, data, 5);
  for (int i = 0; i < Vec_Size(vec.info); ++i) {
    printf("%d\n", vec.data[i]);
  }
  Vec_Free(vec.data, vec.info);
}