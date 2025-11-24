#include <gtest/gtest.h>

#include "../src/include/list/Stack.h"

// Для тестирования emplace со строками, но без включения <string>
// можно использовать string literals и std::string напрямую:
// gtest и стандартная библиотека обычно позволяют это без явного include.
// Если компилятор ругается — раскомментируйте:
// #include <string>   // только если строго необходимо

TEST(StackTest, BasicOperations) {
  Stack<int> st;

  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);

  st.push(1);
  st.push(2);
  st.push(3);

  EXPECT_EQ(st.size(), 3);
  EXPECT_EQ(st.top(), 3);

  st.pop();
  EXPECT_EQ(st.top(), 2);
  EXPECT_EQ(st.size(), 2);

  st.pop();
  EXPECT_EQ(st.top(), 1);
  EXPECT_EQ(st.size(), 1);

  st.pop();
  EXPECT_TRUE(st.empty());
}

TEST(StackTest, Emplace) {
  Stack<std::string> st;

  st.emplace("hello");
  st.emplace(3, 'a');  // std::string(3, 'a') → "aaa"

  EXPECT_EQ(st.size(), 2);
  EXPECT_EQ(st.top(), "aaa");

  st.pop();
  EXPECT_EQ(st.top(), "hello");
}

TEST(StackTest, CopyAndMoveSemantics) {
  Stack<int> st1;
  st1.push(1);
  st1.push(2);
  st1.push(3);

  // Copy constructor
  Stack<int> st2(st1);
  EXPECT_EQ(st2.size(), 3);
  EXPECT_EQ(st2.top(), 3);

  // Move constructor
  Stack<int> st3(std::move(st2));
  EXPECT_EQ(st3.size(), 3);
  EXPECT_TRUE(st2.empty());

  // Copy assignment
  Stack<int> st4;
  st4 = st3;
  EXPECT_EQ(st4.size(), 3);
  EXPECT_EQ(st4.top(), 3);

  // Move assignment
  Stack<int> st5;
  st5 = std::move(st4);
  EXPECT_EQ(st5.size(), 3);
  EXPECT_TRUE(st4.empty());
}

TEST(StackTest, EdgeCases) {
  Stack<int> st;

  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);

  st.push(42);
  EXPECT_EQ(st.size(), 1);
  EXPECT_EQ(st.top(), 42);

  st.pop();
  EXPECT_TRUE(st.empty());

  st.push(1);
  st.push(2);
  st.pop();
  st.push(3);
  EXPECT_EQ(st.top(), 3);
  EXPECT_EQ(st.size(), 2);
}

TEST(StackTest, InsertManyBack) {
  Stack<int> st;

  st.insert_many_back(1, 2, 3);
  EXPECT_EQ(st.size(), 3);
  EXPECT_EQ(st.top(), 3);

  st.insert_many_back(4, 5);
  EXPECT_EQ(st.size(), 5);
  EXPECT_EQ(st.top(), 5);

  // LIFO order
  EXPECT_EQ(st.top(), 5);
  st.pop();
  EXPECT_EQ(st.top(), 4);
  st.pop();
  EXPECT_EQ(st.top(), 3);
  st.pop();
  EXPECT_EQ(st.top(), 2);
  st.pop();
  EXPECT_EQ(st.top(), 1);
  st.pop();
  EXPECT_TRUE(st.empty());
}

TEST(StackTest, Stress) {
  Stack<int> st;
  const int N = 1000;

  for (int i = 0; i < N; ++i) {
    st.push(i);
  }
  EXPECT_EQ(st.size(), N);
  EXPECT_EQ(st.top(), N - 1);

  for (int i = N - 1; i >= 0; --i) {
    EXPECT_EQ(st.top(), i);
    st.pop();
  }
  EXPECT_TRUE(st.empty());
}