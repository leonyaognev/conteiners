#include <gtest/gtest.h>

#include "array/Vector.h"

TEST(VectorCreate, Noargs) {
  Vector<int> a;
  EXPECT_EQ(a.data(), nullptr);
  EXPECT_EQ(a.capacity(), 0);
  EXPECT_EQ(a.size(), 0);
}

TEST(VectorCreate, Arg) {
  Vector<double> b(5);
  EXPECT_NE(b.data(), nullptr);
  EXPECT_EQ(b.capacity(), 40);
  EXPECT_EQ(b.size(), 5);
}

TEST(VectorCreate, Args) {
  Vector<std::string> c(4, "hello");
  EXPECT_NE(c.data(), nullptr);
  // local buffer on 15 elements
  EXPECT_EQ(c.capacity(), 128);
  EXPECT_EQ(c.size(), 4);
  //c.Print();
}

TEST(VectorCopy, Args) {
  Vector<int> a(5);
  Vector<int> b(a);
  EXPECT_NE(b.data(), a.data());
  EXPECT_EQ(b.capacity(), 20);
  EXPECT_EQ(b.size(), 5);
  //a.Print();
  //b.Print();
}

TEST(VectorIter, BeginEnd) {
  Vector<int> a(5);
  for (auto i = a.begin(); i != a.end(); ++i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, postfixPlus) {
  Vector<int> a(5);
  for (auto i = a.begin(); i != a.end(); i++) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, prefixPlus) {
  Vector<int> a(5);
  for (auto i = a.begin(); i != a.end(); ++i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, postfixMinus) {
  Vector<int> a(5);
  for (auto i = a.end(); i != a.begin(); i--) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, prefixMinus) {
  Vector<int> a(5);
  for (auto i = a.end(); i != a.begin(); --i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, EqualOperator) {
  Vector<int> a(5);
  for (auto i = a.end(); !(i == a.begin()); --i) {
    *i = 4;
  }
  EXPECT_EQ(a[3], 4);
  //a.Print();
}

TEST(VectorIter, MemberAccessOperator) {
  struct Item {
    int value;
  };

  Vector<Item> a(3, Item{21});
  auto i = a.begin();
  EXPECT_EQ(i->value, 21);
  EXPECT_EQ((*i).value, i->value);
}

TEST(VectorIter, IncreaseIter){
  Vector<int> a(10);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 10;
  }
  //a.Print();
  auto b = a.begin();
  EXPECT_EQ(*b, 0);
  //b = b + 3;
  EXPECT_EQ(*b, 3);
}

TEST(VectorIter, DecreaseIter){
  Vector<int> a(10);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 10;
  }
  //a.Print();
  auto b = a.end() - 2;
  EXPECT_EQ(*b, 7);
}

TEST(VectorEdit, EraseOneArg){
  Vector<int> a(10);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 10;
  }
  a.Print();
  a.erase(a.begin() + 5);
  a.Print();
}

TEST(VectorEdit, EraseTwoArgs){
  Vector<int> a(4);
  for (size_t i = 0; i < a.size(); i++){
    a[i] = i + 2;
  }
  a.Print();
  a.erase((a.begin() + 1), (a.begin() + 3));
  a.Print();
}