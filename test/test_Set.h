#include <gtest/gtest.h>

#include <ostream>

#include "RedBlackTree/Set.h"
#include "array/Vector.h"

class SetTest : public ::testing::Test {
 protected:
};

TEST_F(SetTest, InsertAndSize) {
  Set<int> s;
  EXPECT_TRUE(s.empty());
  s.insert(5);
  EXPECT_EQ(s.size(), 1u);
  s.insert(3);
  s.insert(8);
  EXPECT_EQ(s.size(), 3u);

  s.insert(3);
  EXPECT_EQ(s.size(), 3u);
}

TEST_F(SetTest, FindElements) {
  Set<int> s;
  s.insert(10);
  s.insert(20);

  auto it = s.find(10);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 10);

  it = s.find(15);
  EXPECT_EQ(it, s.end());
}

TEST_F(SetTest, EraseElement) {
  Set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3u);

  s.erase(s.find(2));
  EXPECT_EQ(s.size(), 2u);
  EXPECT_EQ(s.count(2), 0u);

  s.erase(s.find(100));
  EXPECT_EQ(s.size(), 2u);
}

TEST_F(SetTest, CountElements) {
  Set<int> s;
  s.insert(42);
  EXPECT_EQ(s.count(42), 1u);
  EXPECT_EQ(s.count(0), 0u);
}

TEST_F(SetTest, IteratorOrder) {
  Set<int> s;
  s.insert(5);
  s.insert(1);
  s.insert(3);

  int expected[] = {1, 3, 5};
  size_t i = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    EXPECT_EQ(*it, expected[i]);
    i++;
  }
  EXPECT_EQ(i, 3u);
}

TEST_F(SetTest, ClearSet) {
  Set<int> s;
  s.insert(1);
  s.insert(2);
  s.insert(3);

  EXPECT_FALSE(s.empty());

  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

TEST_F(SetTest, MergeSets) {
  Set<int> s;
  Set<int> other;
  s.insert(1);
  s.insert(3);
  other.insert(2);
  other.insert(3);

  s.merge(other);
  EXPECT_EQ(s.size(), 3u);

  int expected[] = {1, 2, 3};
  size_t i = 0;
  for (auto it = s.begin(); it != s.end(); ++it) {
    EXPECT_EQ(*it, expected[i]);
    i++;
  }
}

TEST_F(SetTest, DefaultConstructor) {
  Set<int> s;
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0);
}

TEST_F(SetTest, InitializerListConstructor) {
  Set<int> s = {10, 20, 30, 10, 40};
  ASSERT_FALSE(s.empty());
  ASSERT_EQ(s.size(), 4);
  ASSERT_TRUE(s.find(20) != s.end());
  ASSERT_TRUE(s.find(50) == s.end());
}

TEST_F(SetTest, RangeConstructor) {
  std::vector<int> data = {5, 15, 25, 15, 35};
  Set<int> s(data.begin(), data.end());
  ASSERT_EQ(s.size(), 4);
  ASSERT_TRUE(s.find(5) != s.end());
  ASSERT_TRUE(s.find(15) != s.end());
  ASSERT_TRUE(s.find(25) != s.end());
  ASSERT_TRUE(s.find(45) == s.end());
}

TEST_F(SetTest, CopyConstructor) {
  Set<int> original = {1, 2, 3};
  Set<int> copy = original;
  ASSERT_EQ(copy.size(), 3);
  ASSERT_TRUE(copy.find(2) != copy.end());

  original.insert(4);
  ASSERT_EQ(original.size(), 4);
  ASSERT_EQ(copy.size(), 3);
}

TEST_F(SetTest, AssignmentOperator) {
  Set<std::string> s1 = {"a", "b"};
  Set<std::string> s2 = {"x", "y", "z"};
  s2 = s1;
  ASSERT_EQ(s2.size(), 2);
  ASSERT_TRUE(s2.find("a") != s2.end());
  ASSERT_TRUE(s2.find("z") == s2.end());
}

TEST_F(SetTest, MoveConstructor) {
  Set<int> original = {10, 20, 30};
  Set<int> moved = std::move(original);

  ASSERT_EQ(moved.size(), 3);
  ASSERT_TRUE(moved.find(20) != moved.end());
}

TEST_F(SetTest, InsertSingleValue) {
  Set<int> s;
  auto res = s.insert(10);
  ASSERT_TRUE(res.second);
  ASSERT_EQ(*res.first, 10);
  ASSERT_EQ(s.size(), 1);
}

TEST_F(SetTest, InsertMultipleUniqueValues) {
  Set<int> s;
  s.insert(20);
  s.insert(10);
  s.insert(30);
  ASSERT_EQ(s.size(), 3);

  std::vector<int> expected = {10, 20, 30};
  std::vector<int> actual;
  for (int val : s) {
    actual.push_back(val);
  }
  ASSERT_EQ(actual, expected);
}

TEST_F(SetTest, InsertDuplicateValue) {
  Set<int> s = {10, 20};
  auto res = s.insert(10);
  ASSERT_FALSE(res.second);
  ASSERT_EQ(*res.first, 10);
  ASSERT_EQ(s.size(), 2);
}

TEST_F(SetTest, InsertStressTest) {
  Set<int> s;
  for (int i = 0; i < 100; ++i) {
    s.insert(i);
  }
  ASSERT_EQ(s.size(), 100);
}

TEST_F(SetTest, InsertStringValues) {
  Set<std::string> s;
  s.insert("apple");
  s.insert("banana");
  s.insert("cherry");
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.find("banana") != s.end());
}

TEST_F(SetTest, InsertInitializerListBasic) {
  Set<int> s = {1, 2};
  s.insert({3, 4, 5});
  ASSERT_EQ(s.size(), 5);
  ASSERT_TRUE(s.find(5) != s.end());
}

TEST_F(SetTest, InsertInitializerListWithDuplicates) {
  Set<int> s = {10, 20};
  s.insert({20, 30, 10, 40});
  ASSERT_EQ(s.size(), 4);
  ASSERT_TRUE(s.find(40) != s.end());
}

TEST_F(SetTest, InsertEmptyInitializerList) {
  Set<int> s = {1};
  s.insert({});
  ASSERT_EQ(s.size(), 1);
}

TEST_F(SetTest, InsertInitializerListStrings) {
  Set<std::string> s;
  s.insert({"cat", "dog", "mouse"});
  s.insert({"dog", "bird"});
  ASSERT_EQ(s.size(), 4);
}

TEST_F(SetTest, InsertInitializerListLarge) {
  Set<int> s;
  s.insert({1, 5, 2, 6, 3, 7, 4, 8, 9, 0});
  ASSERT_EQ(s.size(), 10);
  ASSERT_TRUE(s.find(5) != s.end());
  ASSERT_TRUE(s.find(10) == s.end());
}

TEST_F(SetTest, InsertRangeBasic) {
  Set<int> s = {100};
  std::vector<int> data = {1, 2, 3};
  s.insert(data.begin(), data.end());
  ASSERT_EQ(s.size(), 4);
  ASSERT_TRUE(s.find(2) != s.end());
}

TEST_F(SetTest, InsertRangeWithDuplicates) {
  Set<int> s = {1, 2, 3};
  std::vector<int> data = {3, 4, 5, 1};
  s.insert(data.begin(), data.end());
  ASSERT_EQ(s.size(), 5);
  ASSERT_TRUE(s.find(4) != s.end());
}

TEST_F(SetTest, InsertRangeEmpty) {
  Set<int> s = {1};
  std::vector<int> data = {};
  s.insert(data.begin(), data.end());
  ASSERT_EQ(s.size(), 1);
}

TEST_F(SetTest, InsertRangeIterators) {
  std::vector<std::string> data = {"one", "two", "three"};
  Set<std::string> s;
  s.insert(data.begin(), data.end());
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.find("two") != s.end());
}

TEST_F(SetTest, InsertRangeSameSet) {
  Set<int> s = {1, 2, 3};

  s.insert(s.begin(), s.end());
  ASSERT_EQ(s.size(), 3);
}

TEST_F(SetTest, InsertManyBasic) {
  Set<int> s;
  auto results = s.insert_many(10, 20, 30);
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(results.size(), 3);
  ASSERT_TRUE(results[0].second);
  ASSERT_TRUE(s.find(20) != s.end());
}

TEST_F(SetTest, InsertManyWithDuplicates) {
  Set<int> s = {5};
  auto results = s.insert_many(10, 5, 20);
  ASSERT_EQ(s.size(), 3);
  ASSERT_EQ(results.size(), 3);
  ASSERT_TRUE(results[0].second);
  ASSERT_FALSE(results[1].second);
  ASSERT_TRUE(results[2].second);
}

TEST_F(SetTest, InsertManyEmpty) {
  Set<int> s = {1};

  auto results = s.insert_many();
  ASSERT_EQ(s.size(), 1);
  ASSERT_TRUE(results.empty());
}

TEST_F(SetTest, InsertManyRvalue) {
  Set<std::string> s;

  auto results =
      s.insert_many(std::string("first"), "second", std::string("third"));
  ASSERT_EQ(s.size(), 3);
  ASSERT_TRUE(s.find("first") != s.end());
}

TEST_F(SetTest, InsertManyMixedTypes) {
  Set<int> s;

  auto results = s.insert_many(1, 2, 3);
  ASSERT_EQ(s.size(), 3);
}

TEST_F(SetTest, FindExistingElement) {
  Set<int> s = {10, 20, 30};
  auto it = s.find(20);
  ASSERT_TRUE(it != s.end());
  ASSERT_EQ(*it, 20);
}

TEST_F(SetTest, FindNonExistingElement) {
  Set<int> s = {10, 20, 30};
  auto it = s.find(40);
  ASSERT_TRUE(it == s.end());
}

TEST_F(SetTest, FindInEmptySet) {
  Set<int> s;
  auto it = s.find(10);
  ASSERT_TRUE(it == s.end());
}

TEST_F(SetTest, FindEdgeCases) {
  Set<int> s = {1, 100};
  ASSERT_TRUE(s.find(1) != s.end());
  ASSERT_TRUE(s.find(100) != s.end());
  ASSERT_TRUE(s.find(50) == s.end());
}

TEST_F(SetTest, FindStringValue) {
  Set<std::string> s = {"x", "y", "z"};
  auto it = s.find("y");
  ASSERT_TRUE(it != s.end());
  ASSERT_EQ(*it, "y");
  ASSERT_TRUE(s.find("a") == s.end());
}

TEST_F(SetTest, CountExistingElement) {
  Set<int> s = {10, 20, 30};
  ASSERT_EQ(s.count(20), 1);
}

TEST_F(SetTest, CountNonExistingElement) {
  Set<int> s = {10, 20, 30};
  ASSERT_EQ(s.count(40), 0);
}

TEST_F(SetTest, CountInEmptySet) {
  Set<int> s;
  ASSERT_EQ(s.count(10), 0);
}

TEST_F(SetTest, CountStringValue) {
  Set<std::string> s = {"a", "b", "c"};
  ASSERT_EQ(s.count("b"), 1);
  ASSERT_EQ(s.count("d"), 0);
}

TEST_F(SetTest, CountLargeSet) {
  Set<int> s;
  for (int i = 0; i < 1000; ++i) {
    s.insert(i);
  }
  ASSERT_EQ(s.count(500), 1);
  ASSERT_EQ(s.count(1001), 0);
}

TEST_F(SetTest, EraseByIteratorExisting) {
  Set<int> s = {10, 20, 30};
  auto it = s.find(20);

  s.erase(it);
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.count(20), 0);
}

TEST_F(SetTest, EraseByIteratorRange) {
  Set<int> s;
  s.insert({1, 2, 3, 4, 5});

  auto it = s.find(3);

  s.erase(it);
  s.erase(s.find(4));
  s.erase(s.find(5));

  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.count(3), 0);
  ASSERT_EQ(s.count(1), 1);
}

TEST_F(SetTest, EraseBeginIterator) {
  Set<int> s = {10, 20, 30};
  s.erase(s.begin());
  ASSERT_EQ(s.size(), 2);
  ASSERT_EQ(s.count(10), 0);
  ASSERT_EQ(*s.begin(), 20);
}

TEST_F(SetTest, EraseEndIteratorInvalid) {
  Set<int> s = {10};

  s.erase(s.end());
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(s.count(10), 1);
}

TEST_F(SetTest, EraseAndIterate) {
  Set<int> s = {10, 20, 30, 40};
  auto it = s.find(20);
  s.erase(it);

  std::vector<int> expected = {10, 30, 40};
  std::vector<int> actual;
  for (int val : s) {
    actual.push_back(val);
  }
  ASSERT_EQ(actual, expected);
}

TEST_F(SetTest, EraseLargeSet) {
  Set<int> s;
  for (int i = 0; i < 1000; i++) {
    s.insert(i);
  }

  auto i = s.begin();
  while (i != s.end()) {
    auto cur = i;
    ++i;
    s.erase(cur);
  }
}

TEST_F(SetTest, ClearNonEmpty) {
  Set<int> s = {1, 2, 3, 4, 5};
  s.clear();
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0);
  ASSERT_TRUE(s.find(1) == s.end());
}

TEST_F(SetTest, ClearEmpty) {
  Set<int> s;
  s.clear();
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.size(), 0);
}

TEST_F(SetTest, ClearAndInsert) {
  Set<int> s = {10};
  s.clear();
  s.insert(20);
  ASSERT_EQ(s.size(), 1);
  ASSERT_EQ(*s.begin(), 20);
}

TEST_F(SetTest, ClearLargeSet) {
  Set<int> s;
  for (int i = 0; i < 100; ++i) s.insert(i);
  s.clear();

  ASSERT_TRUE(s.empty());
}

TEST_F(SetTest, ClearStringSet) {
  Set<std::string> s = {"hello", "world"};
  s.clear();
  ASSERT_TRUE(s.empty());
  ASSERT_EQ(s.find("hello"), s.end());
}

TEST_F(SetTest, SwapBasic) {
  Set<int> s1 = {1, 2};
  Set<int> s2 = {10, 20, 30};

  s1.swap(s2);

  ASSERT_EQ(s1.size(), 3);
  ASSERT_EQ(s2.size(), 2);
  ASSERT_TRUE(s1.find(10) != s1.end());
  ASSERT_TRUE(s2.find(1) != s2.end());
}

TEST_F(SetTest, SwapWithEmpty) {
  Set<int> s1 = {1, 2};
  Set<int> s2;

  s1.swap(s2);

  ASSERT_TRUE(s1.empty());
  ASSERT_EQ(s2.size(), 2);
  ASSERT_TRUE(s2.find(1) != s2.end());
}

TEST_F(SetTest, SwapWithSelf) {
  Set<int> s1 = {1, 2};
  Set<int> copy = s1;
  s1.swap(s1);
  ASSERT_EQ(s1.size(), 2);
  ASSERT_TRUE(s1.find(1) != s1.end());
}

TEST_F(SetTest, SwapAndInsert) {
  Set<int> s1 = {1};
  Set<int> s2 = {10, 20};

  s1.swap(s2);

  s1.insert(30);
  s2.insert(3);

  ASSERT_EQ(s1.size(), 3);
  ASSERT_EQ(s2.size(), 2);
}

TEST_F(SetTest, SwapStringSet) {
  Set<std::string> s1 = {"a", "b"};
  Set<std::string> s2 = {"c"};

  s1.swap(s2);
  ASSERT_EQ(s1.size(), 1);
  ASSERT_EQ(s2.size(), 2);
  ASSERT_TRUE(s1.find("c") != s1.end());
  ASSERT_TRUE(s2.find("a") != s2.end());
}

TEST_F(SetTest, MergeBasic) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2 = {4, 5, 6};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 6);
  ASSERT_TRUE(s1.find(4) != s1.end());
  ASSERT_TRUE(s2.empty());
}

TEST_F(SetTest, MergeWithDuplicates) {
  Set<int> s1 = {1, 2, 3};
  Set<int> s2 = {2, 3, 4};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 4);
  ASSERT_TRUE(s1.find(4) != s1.end());
  ASSERT_FALSE(s2.empty());
}

TEST_F(SetTest, MergeIntoEmpty) {
  Set<int> s1;
  Set<int> s2 = {1, 2};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 2);
  ASSERT_TRUE(s1.find(1) != s1.end());
  ASSERT_TRUE(s2.empty());
}

TEST_F(SetTest, MergeEmptyIntoNonEmpty) {
  Set<int> s1 = {1, 2};
  Set<int> s2;

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 2);
  ASSERT_TRUE(s2.empty());
}

TEST_F(SetTest, MergeStringSets) {
  Set<std::string> s1 = {"a", "b"};
  Set<std::string> s2 = {"b", "c"};

  s1.merge(s2);

  ASSERT_EQ(s1.size(), 3);
  ASSERT_TRUE(s1.find("c") != s1.end());
  ASSERT_FALSE(s2.empty());
}

TEST_F(SetTest, ContainsExistingElement) {
  Set<int> s = {10, 20, 30};
  auto it = s.find(20);
  ASSERT_TRUE(it != s.end());
  ASSERT_EQ(*it, 20);
}

TEST_F(SetTest, ContainsNonExistingElement) {
  Set<int> s = {10, 20, 30};
  bool it = s.contains(40);
  ASSERT_FALSE(it);
}

TEST_F(SetTest, ContainsInEmptySet) {
  Set<int> s;
  bool it = s.contains(10);
  ASSERT_FALSE(it);
}

TEST_F(SetTest, ContainsEdgeCases) {
  Set<int> s = {1, 100};

  ASSERT_TRUE(s.contains(1));
  ASSERT_TRUE(s.contains(100));
  ASSERT_FALSE(s.contains(50));
}

TEST_F(SetTest, ContainsStringValue) {
  Set<std::string> s = {"x", "y", "z"};
  auto it = s.contains("y");
  ASSERT_TRUE(it);
  ASSERT_FALSE(s.contains("a"));
}
