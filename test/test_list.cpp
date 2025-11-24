#include <gtest/gtest.h>

#include "../src/include/list/List.h"

// ==================== TEST SUITES ====================

TEST(ListTest, BasicOperations) {
  List<int> lst;

  // Push back
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);

  // Push front
  lst.pushFront(0);
  EXPECT_EQ(lst.size(), 4);
  EXPECT_EQ(lst.front(), 0);

  // Pop back
  lst.popBack();
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.back(), 2);

  // Pop front
  lst.popFront();
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 1);
}

TEST(ListTest, Constructors) {
  List<int> lst1;
  EXPECT_TRUE(lst1.empty());

  List<int> lst2(std::size_t(3), 100);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 100);

  List<int> temp;
  temp.pushBack(1);
  temp.pushBack(2);
  temp.pushBack(3);

  List<int> lst3(temp.begin(), temp.end());
  EXPECT_EQ(lst3.size(), 3);
  EXPECT_EQ(lst3.front(), 1);
  EXPECT_EQ(lst3.back(), 3);

  // Copy constructor
  List<int> lst4;
  lst4.pushBack(1);
  lst4.pushBack(2);
  lst4.pushBack(3);
  List<int> lst5(lst4);
  EXPECT_EQ(lst5.size(), 3);
  EXPECT_EQ(lst5.front(), 1);
  EXPECT_EQ(lst5.back(), 3);

  // Move constructor
  List<int> lst6(std::move(lst5));
  EXPECT_EQ(lst6.size(), 3);
  EXPECT_TRUE(lst5.empty());
}

TEST(ListTest, Iterators) {
  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  lst.pushBack(4);
  lst.pushBack(5);

  // Forward iteration
  int sum = 0;
  int count = 0;
  for (auto it = lst.begin(); it != lst.end(); ++it) {
    sum += *it;
    ++count;
  }
  EXPECT_EQ(sum, 15);
  EXPECT_EQ(count, 5);

  // Range-based for loop
  sum = 0;
  for (const auto& val : lst) {
    sum += val;
  }
  EXPECT_EQ(sum, 15);

  // Iterator arithmetic
  auto it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
}

TEST(ListTest, Modifiers) {
  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);

  // Insert in middle
  auto it = lst.begin();
  ++it;
  lst.insert(it, 99);

  EXPECT_EQ(lst.size(), 4);
  it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 99);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);

  // Erase from middle
  it = lst.begin();
  ++it;
  lst.erase(it);

  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);

  // Clear
  lst.clear();
  EXPECT_TRUE(lst.empty());
  EXPECT_EQ(lst.size(), 0);
}

TEST(ListTest, Operations) {
  // Test remove
  List<int> lst1;
  lst1.pushBack(1);
  lst1.pushBack(2);
  lst1.pushBack(2);
  lst1.pushBack(3);
  lst1.pushBack(2);
  lst1.pushBack(4);

  lst1.remove(2);
  EXPECT_EQ(lst1.size(), 3);
  EXPECT_EQ(lst1.front(), 1);
  EXPECT_EQ(lst1.back(), 4);

  // Test unique
  List<int> lst2;
  lst2.pushBack(1);
  lst2.pushBack(1);
  lst2.pushBack(2);
  lst2.pushBack(2);
  lst2.pushBack(3);
  lst2.pushBack(1);

  lst2.unique();
  EXPECT_EQ(lst2.size(), 4);
  auto it = lst2.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 1);

  // Test sort
  List<int> lst3;
  lst3.pushBack(3);
  lst3.pushBack(1);
  lst3.pushBack(4);
  lst3.pushBack(2);

  lst3.sort();
  it = lst3.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
}

TEST(ListTest, EdgeCases) {
  // Empty list operations
  List<int> empty_list;
  EXPECT_TRUE(empty_list.empty());
  EXPECT_EQ(empty_list.size(), 0);

  // Pop on empty list (should not crash)
  empty_list.popBack();
  empty_list.popFront();
  EXPECT_TRUE(empty_list.empty());

  // Single element list
  List<int> single;
  single.pushBack(42);
  EXPECT_EQ(single.size(), 1);
  EXPECT_EQ(single.front(), 42);
  EXPECT_EQ(single.back(), 42);

  single.popFront();
  EXPECT_TRUE(single.empty());

  // Self-assignment
  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  lst = lst;
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
}

TEST(ListTest, Emplace) {
  List<std::string> lst;

  lst.emplaceFront("world");
  lst.emplaceFront("hello");
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), "hello");
  EXPECT_EQ(lst.back(), "world");

  lst.emplaceBack("test");
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.back(), "test");

  auto it = lst.begin();
  ++it;
  lst.emplace(it, "middle");
  EXPECT_EQ(lst.size(), 4);

  it = lst.begin();
  EXPECT_EQ(*it, "hello");
  ++it;
  EXPECT_EQ(*it, "middle");
  ++it;
  EXPECT_EQ(*it, "world");
  ++it;
  EXPECT_EQ(*it, "test");
}

TEST(ListTest, Resize) {
  List<int> lst;

  lst.resize(3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 0);
  EXPECT_EQ(lst.back(), 0);

  lst.resize(5, 42);
  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(lst.back(), 42);

  lst.resize(2);
  EXPECT_EQ(lst.size(), 2);
  EXPECT_EQ(lst.front(), 0);
  EXPECT_EQ(lst.back(), 0);

  List<int> empty_lst;
  empty_lst.resize(3, 10);
  EXPECT_EQ(empty_lst.size(), 3);
  EXPECT_EQ(empty_lst.front(), 10);
  EXPECT_EQ(empty_lst.back(), 10);
}

TEST(ListTest, Splice) {
  List<int> lst1;
  lst1.pushBack(1);
  lst1.pushBack(2);
  lst1.pushBack(3);

  List<int> lst2;
  lst2.pushBack(4);
  lst2.pushBack(5);
  lst2.pushBack(6);

  // Splice entire list
  lst1.splice(lst1.end(), lst2);
  EXPECT_EQ(lst1.size(), 6);
  EXPECT_TRUE(lst2.empty());
  EXPECT_EQ(lst1.back(), 6);

  // Reset
  lst2.pushBack(7);
  lst2.pushBack(8);
  lst2.pushBack(9);

  // Splice single element
  auto it = lst2.begin();
  lst1.splice(lst1.begin(), lst2, it);
  EXPECT_EQ(lst1.size(), 7);
  EXPECT_EQ(lst2.size(), 2);
  EXPECT_EQ(lst1.front(), 7);

  // Splice range
  auto first = lst2.begin();
  auto last = lst2.end();
  lst1.splice(lst1.end(), lst2, first, last);
  EXPECT_EQ(lst1.size(), 9);
  EXPECT_TRUE(lst2.empty());
  EXPECT_EQ(lst1.back(), 9);
}

TEST(ListTest, Merge) {
  List<int> lst1;
  lst1.pushBack(1);
  lst1.pushBack(3);
  lst1.pushBack(5);

  List<int> lst2;
  lst2.pushBack(2);
  lst2.pushBack(4);
  lst2.pushBack(6);

  // Merge sorted lists
  lst1.merge(lst2);
  EXPECT_EQ(lst1.size(), 6);
  EXPECT_TRUE(lst2.empty());

  auto it = lst1.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 6);
}

TEST(ListTest, ReverseIterators) {
  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  lst.pushBack(4);
  lst.pushBack(5);

  // Reverse iteration
  int sum = 0;
  int count = 0;
  for (auto it = lst.rbegin(); it != lst.rend(); --it) {
    sum += *it;
    ++count;
  }
  EXPECT_EQ(sum, 15);
  EXPECT_EQ(count, 5);

  // Check reverse order
  auto rit = lst.rbegin();
  EXPECT_EQ(*rit, 5);
  --rit;
  EXPECT_EQ(*rit, 4);
  --rit;
  EXPECT_EQ(*rit, 3);
  --rit;
  EXPECT_EQ(*rit, 2);
  --rit;
  EXPECT_EQ(*rit, 1);
}

TEST(ListTest, InsertMany) {
  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(5);

  auto it = lst.begin();
  ++it;
  auto result = lst.insert_many(it, 2, 3, 4);

  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(*result, 2);

  auto check_it = lst.begin();
  EXPECT_EQ(*check_it, 1);
  ++check_it;
  EXPECT_EQ(*check_it, 2);
  ++check_it;
  EXPECT_EQ(*check_it, 3);
  ++check_it;
  EXPECT_EQ(*check_it, 4);
  ++check_it;
  EXPECT_EQ(*check_it, 5);

  lst.insert_many(lst.begin(), -1, 0);
  EXPECT_EQ(lst.size(), 7);
  EXPECT_EQ(lst.front(), -1);

  lst.insert_many(lst.end(), 6, 7);
  EXPECT_EQ(lst.size(), 9);
  EXPECT_EQ(lst.back(), 7);

  auto empty_result = lst.insert_many(lst.begin());
  EXPECT_EQ(lst.size(), 9);
  EXPECT_EQ(empty_result, lst.begin());
}

TEST(ListTest, InsertManyBack) {
  List<int> lst;
  lst.insert_many_back(1, 2, 3);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);

  lst.insert_many_back(4, 5);
  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(lst.back(), 5);

  auto it = lst.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);

  int x = 6;
  const int y = 7;
  lst.insert_many_back(x, y, 8);
  EXPECT_EQ(lst.size(), 8);
  EXPECT_EQ(lst.back(), 8);

  lst.insert_many_back();
  EXPECT_EQ(lst.size(), 8);
}

TEST(ListTest, InsertManyFront) {
  List<int> lst;
  lst.insert_many_front(3, 2, 1);
  EXPECT_EQ(lst.size(), 3);
  EXPECT_EQ(lst.front(), 1);
  EXPECT_EQ(lst.back(), 3);

  lst.insert_many_front(5, 4);
  EXPECT_EQ(lst.size(), 5);
  EXPECT_EQ(lst.front(), 4);

  auto it = lst.begin();
  EXPECT_EQ(*it, 4);
  ++it;
  EXPECT_EQ(*it, 5);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);

  int x = 6;
  const int y = 7;
  lst.insert_many_front(y, x, 8);
  EXPECT_EQ(lst.size(), 8);
  EXPECT_EQ(lst.front(), 8);

  lst.insert_many_front();
  EXPECT_EQ(lst.size(), 8);
}

TEST(ListTest, Stress) {
  List<int> list;
  const int N = 1000;

  for (int i = 0; i < N; ++i) {
    list.pushBack(i);
  }
  EXPECT_EQ(list.size(), N);
  EXPECT_EQ(list.front(), 0);
  EXPECT_EQ(list.back(), N - 1);

  for (int i = 0; i < N; ++i) {
    list.popFront();
  }
  EXPECT_TRUE(list.empty());
}

TEST(ListTest, ComparisonOperations) {
  List<int> lst1;
  lst1.pushBack(1);
  lst1.pushBack(2);
  lst1.pushBack(3);

  List<int> lst2;
  lst2 = lst1;
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 1);

  List<int> lst3;
  lst3.pushBack(4);
  lst3.pushBack(5);
  lst3.pushBack(6);

  lst2 = std::move(lst3);
  EXPECT_EQ(lst2.size(), 3);
  EXPECT_EQ(lst2.front(), 4);
  EXPECT_TRUE(lst3.empty());

  List<int> lst4;
  lst4.pushBack(1);
  lst4.pushBack(2);
  lst4.pushBack(3);

  List<int> lst5;
  lst5.pushBack(4);
  lst5.pushBack(5);

  lst4.swap(lst5);
  EXPECT_EQ(lst4.size(), 2);
  EXPECT_EQ(lst5.size(), 3);
  EXPECT_EQ(lst4.front(), 4);
  EXPECT_EQ(lst5.front(), 1);
}