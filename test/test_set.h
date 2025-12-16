#include <gtest/gtest.h>

#include <ostream>

#include "RedBlackTree/Set.h"

class SetTest : public ::testing::Test {
 protected:
  Set<int> s;

  void SetUp() override {
    // начальная инициализация, если нужна
  }

  void TearDown() override { s.clear(); }
};

// Проверка вставки и размера
TEST_F(SetTest, InsertAndSize) {
  EXPECT_TRUE(s.empty());
  s.insert(5);
  std::cout << "penis: " << *s.find(5) << "\n";
  EXPECT_EQ(s.size(), 1u);
  s.insert(3);
  s.insert(8);
  EXPECT_EQ(s.size(), 3u);

  // вставка дубликата не должна менять размер
  s.insert(3);
  EXPECT_EQ(s.size(), 3u);
}

// Проверка find
TEST_F(SetTest, FindElements) {
  s.insert(10);
  s.insert(20);

  auto it = s.find(10);
  EXPECT_NE(it, s.end());
  EXPECT_EQ(*it, 10);

  it = s.find(15);
  EXPECT_EQ(it, s.end());
}

// Проверка erase по значению
TEST_F(SetTest, EraseElement) {
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_EQ(s.size(), 3u);

  s.erase(2);
  EXPECT_EQ(s.size(), 2u);
  EXPECT_EQ(s.count(2), 0u);

  // удаление несуществующего элемента не должно ломать
  s.erase(100);
  EXPECT_EQ(s.size(), 2u);
}

// Проверка count
TEST_F(SetTest, CountElements) {
  s.insert(42);
  EXPECT_EQ(s.count(42), 1u);
  EXPECT_EQ(s.count(0), 0u);
}

// Проверка итераторов и упорядоченности
TEST_F(SetTest, IteratorOrder) {
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

// Проверка clear
TEST_F(SetTest, ClearSet) {
  s.insert(1);
  s.insert(2);
  s.insert(3);
  EXPECT_FALSE(s.empty());

  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0u);
}

// Проверка merge
TEST_F(SetTest, MergeSets) {
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
