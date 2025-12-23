#include <gtest/gtest.h>

#include <ostream>
#include <string>
#include <vector>

#include "RedBlackTree/MultiSet.h"
#include "array/Vector.h"

class MultiSetTest : public ::testing::Test {
 protected:
};

TEST_F(MultiSetTest, InsertAndSize) {
  MultiSet<int> s;
  EXPECT_TRUE(s.empty());
  s.insert(5);
  EXPECT_EQ(s.size(), 1u);
  s.insert(3);
  s.insert(8);
  EXPECT_EQ(s.size(), 3u);

  s.insert(3);
  EXPECT_EQ(s.size(), 4u);
}

TEST_F(MultiSetTest, FindElements) {
  MultiSet<int> s;
  s.insert(10);
  s.insert(20);
  s.insert(10);

  auto it = s.find(10);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 10);

  it = s.find(15);
  EXPECT_EQ(it, s.end());
}

TEST_F(MultiSetTest, EraseElement) {
  MultiSet<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 4u);

  s.erase(s.find(2));
  EXPECT_EQ(s.size(), 3u);
  EXPECT_EQ(s.count(2), 1u);

  auto it_bad = s.find(100);
  if (it_bad != s.end()) {
    s.erase(it_bad);
  }
  EXPECT_EQ(s.size(), 3u);
}

TEST_F(MultiSetTest, CountElements) {
  MultiSet<int> s;
  s.insert(42);
  s.insert(42);
  s.insert(42);
  EXPECT_EQ(s.count(42), 3u);
  EXPECT_EQ(s.count(0), 0u);
}

TEST_F(MultiSetTest, IteratorOrder) {
  MultiSet<int> s;
  s.insert(5);
  s.insert(1);
  s.insert(3);
  s.insert(3);

  int expected[] = {1, 3, 3, 5};
  size_t i = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    EXPECT_EQ(*it, expected[i]);
    i++;
  }
  EXPECT_EQ(i, 4u);
}

TEST_F(MultiSetTest, DefaultConstructor) {
  MultiSet<int> s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0u);
}

TEST_F(MultiSetTest, InitializerListConstructor) {
  MultiSet<int> s = {10, 20, 30, 10, 40};
  ASSERT_FALSE(s.empty());
  ASSERT_EQ(s.size(), 5u);
  ASSERT_EQ(s.count(10), 2u);
}

TEST_F(MultiSetTest, RangeConstructor) {
  std::vector<int> data = {5, 15, 25, 15, 35};
  MultiSet<int> s(data.begin(), data.end());
  ASSERT_EQ(s.size(), 5u);
  ASSERT_EQ(s.count(15), 2u);
}

TEST_F(MultiSetTest, CopyConstructor) {
  MultiSet<int> original = {1, 2, 2, 3};
  MultiSet<int> copy = original;
  ASSERT_EQ(copy.size(), 4u);
  ASSERT_EQ(copy.count(2), 2u);

  original.insert(4);
  ASSERT_EQ(original.size(), 5u);
  ASSERT_EQ(copy.size(), 4u);
}

TEST_F(MultiSetTest, AssignmentOperator) {
  MultiSet<std::string> s1 = {"a", "b", "a"};
  MultiSet<std::string> s2 = {"x", "y", "z"};
  s2 = s1;
  ASSERT_EQ(s2.size(), 3u);
  ASSERT_EQ(s2.count("a"), 2u);
  ASSERT_TRUE(s2.find("z") == s2.end());
}

TEST_F(MultiSetTest, MoveConstructor) {
  MultiSet<int> original = {10, 20, 20, 30};
  MultiSet<int> moved = std::move(original);

  ASSERT_EQ(moved.size(), 4u);
  ASSERT_EQ(moved.count(20), 2u);
}

TEST_F(MultiSetTest, InsertSingleValue) {
  MultiSet<int> s;
  auto it = s.insert(10);
  ASSERT_EQ(*it, 10);
  ASSERT_EQ(s.size(), 1u);

  s.insert(10);
  ASSERT_EQ(s.size(), 2u);
  ASSERT_EQ(s.count(10), 2u);
}

TEST_F(MultiSetTest, InsertInitializerListWithDuplicates) {
  MultiSet<int> s = {10, 20};
  s.insert({20, 30, 10, 40});

  ASSERT_EQ(s.size(), 6u);
  ASSERT_EQ(s.count(20), 2u);
}

TEST_F(MultiSetTest, InsertRangeWithDuplicates) {
  MultiSet<int> s = {1, 2, 3};
  std::vector<int> data = {3, 4, 5, 1};
  s.insert(data.begin(), data.end());

  ASSERT_EQ(s.size(), 7u);
  ASSERT_EQ(s.count(1), 2u);
  ASSERT_EQ(s.count(3), 2u);
}

TEST_F(MultiSetTest, InsertManyWithDuplicates) {
  MultiSet<int> s = {5};

  s.insert_many(10, 5, 20);
  ASSERT_EQ(s.size(), 4u);
  ASSERT_EQ(s.count(5), 2u);
}

TEST_F(MultiSetTest, ClearNonEmpty) {
  MultiSet<int> s = {1, 2, 2, 3};
  s.clear();
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0u);
}

TEST_F(MultiSetTest, EraseBeginIterator) {
  MultiSet<int> s = {10, 10, 20, 30};
  s.erase(s.begin());
  ASSERT_EQ(s.size(), 3u);
  ASSERT_EQ(s.count(10), 1u);
}

TEST_F(MultiSetTest, SwapBasic) {
  MultiSet<int> s1 = {1, 1, 2};
  MultiSet<int> s2 = {10, 20, 30};

  s1.swap(s2);

  ASSERT_EQ(s1.size(), 3u);
  ASSERT_EQ(s2.size(), 3u);
  ASSERT_EQ(s2.count(1), 2u);
}

TEST_F(MultiSetTest, MergeBasic) {
  MultiSet<int> s1 = {1, 2, 3};
  MultiSet<int> s2 = {4, 5, 6};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 6u);
  ASSERT_TRUE(s2.empty());
}

TEST_F(MultiSetTest, MergeWithDuplicates) {
  MultiSet<int> s1 = {1, 2, 3};
  MultiSet<int> s2 = {2, 3, 4};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 6u);
  ASSERT_EQ(s1.count(2), 2u);
  ASSERT_EQ(s1.count(3), 2u);
  ASSERT_TRUE(s2.empty());
}

TEST_F(MultiSetTest, ContainsExistingElement) {
  MultiSet<int> s = {10, 20, 20, 30};
  ASSERT_TRUE(s.contains(20));
  ASSERT_TRUE(s.contains(10));
}

TEST_F(MultiSetTest, ContainsNonExistingElement) {
  MultiSet<int> s = {10, 20, 30};
  ASSERT_FALSE(s.contains(40));
}

TEST_F(MultiSetTest, ContainsStringValue) {
  MultiSet<std::string> s = {"x", "y", "y", "z"};
  ASSERT_TRUE(s.contains("y"));
  ASSERT_EQ(s.count("y"), 2u);
  ASSERT_FALSE(s.contains("a"));
}

TEST_F(MultiSetTest, EraseLargeMultiSet) {
  MultiSet<int> s;
  for (int i = 0; i < 100; i++) {
    s.insert(i);
    s.insert(i);
  }

  auto i = s.begin();
  while (i != s.end()) {
    auto cur = i;
    ++i;
    s.erase(cur);
  }
  ASSERT_EQ(s.size(), 0u);
}
