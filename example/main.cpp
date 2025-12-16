#include <gtest/gtest.h>

#include "RedBlackTree/Set.h"
#include "array/Vector.h"

int main(void) {
  Set<int> s;
  for (int i = 0; i < 1000; i++) {
    s.insert(i);
  }
  s.displayTree();
  return 0;
}
