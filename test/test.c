#include <stdio.h>
#include <Containers/String.h>
#include <Containers/Vector.h>

int main() {
  Vec_InitList(vec, int, 1, 2, 3);

  for (int i = 0; i < Vec_Size(vec); ++i) {
    printf("%d\n", vec[i]);
  }

  Vec_Free(vec);

  return 0;
}
