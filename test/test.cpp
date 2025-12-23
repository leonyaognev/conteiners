#include <gtest/gtest.h>

#include "test_Map.h"
#include "test_MultiSet.h"
#include "test_Set.h"

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
