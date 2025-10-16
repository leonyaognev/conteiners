#include <gtest/gtest.h>

#include "array/BaseArray.h"

TEST(BaseArrayCreate, Noargs) {
  BaseArray<int> a;
  EXPECT_EQ(a.data(), nullptr);
  EXPECT_EQ(a.capacity(), 0);
  EXPECT_EQ(a.size(), 0);
}

TEST(BaseArrayCreate, Arg) {
  BaseArray<double> b(5);
  EXPECT_NE(b.data(), nullptr);
  EXPECT_EQ(b.capacity(), 40);
  EXPECT_EQ(b.size(), 5);
}

TEST(BaseArrayCreate, Args) {
  BaseArray<std::string> c(4, "hello");
  EXPECT_NE(c.data(), nullptr);
  // local buffer on 15 elements
  EXPECT_EQ(c.capacity(), 128);
  EXPECT_EQ(c.size(), 4);
  c.Print();
}

TEST(BaseArrayCopy, Args) {
  BaseArray<int> a(5);
  BaseArray<int> b(a);
  EXPECT_NE(b.data(), a.data());
  EXPECT_EQ(b.capacity(), 20);
  EXPECT_EQ(b.size(), 5);
  a.Print();
  b.Print();
}

TEST(BaseArrayIter, BeginEnd) {
  BaseArray<int> a(5);
  for (auto i = a.begin(); i != a.end(); ++i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  a.Print();
}

TEST(BaseArrayIter, postfixPlus) {
  BaseArray<int> a(5);
  for (auto i = a.begin(); i != a.end(); i++) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  a.Print();
}

TEST(BaseArrayIter, prefixPlus) {
  BaseArray<int> a(5);
  for (auto i = a.begin(); i != a.end(); ++i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  a.Print();
}

TEST(BaseArrayIter, postfixMinus) {
  BaseArray<int> a(5);
  for (auto i = a.end(); i != a.begin(); i--) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  a.Print();
}

TEST(BaseArrayIter, prefixMinus) {
  BaseArray<int> a(5);
  for (auto i = a.end(); i != a.begin(); --i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  a.Print();
}

TEST(BaseArrayIter, EqualOperator) {
  BaseArray<int> a(5);
  for (auto i = a.end(); !(i == a.begin()); --i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  a.Print();
}

TEST(BaseArrayIter, MemberAccessOperator) {
  struct Item {
    int value;
  };

  BaseArray<Item> a(3, Item{21});
  auto i = a.begin();
  EXPECT_EQ(i->value, 21);
  EXPECT_EQ((*i).value, i->value);
}
