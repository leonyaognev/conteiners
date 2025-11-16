#include "../src/include/list/Queue.h"

#include <gtest/gtest.h>

// ==================== TEST SUITES ====================

TEST(QueueTest, BasicOperations) {
  Queue<int> q;

  // Test empty queue
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);

  // Push elements
  q.push(1);
  q.push(2);
  q.push(3);

  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);

  // Pop elements (FIFO)
  q.pop();
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.size(), 2);

  q.pop();
  EXPECT_EQ(q.front(), 3);
  EXPECT_EQ(q.size(), 1);

  q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Emplace) {
  Queue<std::string> q;

  q.emplace("hello");
  q.emplace(3, 'a');  // std::string(3, 'a') → "aaa"

  EXPECT_EQ(q.size(), 2);
  EXPECT_EQ(q.front(), "hello");
  EXPECT_EQ(q.back(), "aaa");
}

TEST(QueueTest, CopyAndMoveSemantics) {
  Queue<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);

  // Copy constructor
  Queue<int> q2(q1);
  EXPECT_EQ(q2.size(), 3);
  EXPECT_EQ(q2.front(), 1);

  // Move constructor
  Queue<int> q3(std::move(q2));
  EXPECT_EQ(q3.size(), 3);
  EXPECT_TRUE(q2.empty());

  // Copy assignment
  Queue<int> q4;
  q4 = q3;
  EXPECT_EQ(q4.size(), 3);
  EXPECT_EQ(q4.front(), 1);

  // Move assignment
  Queue<int> q5;
  q5 = std::move(q4);
  EXPECT_EQ(q5.size(), 3);
  EXPECT_TRUE(q4.empty());
}

TEST(QueueTest, EdgeCases) {
  Queue<int> q;

  // Empty queue
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);

  // Single element
  q.push(42);
  EXPECT_EQ(q.size(), 1);
  EXPECT_EQ(q.front(), 42);
  EXPECT_EQ(q.back(), 42);

  q.pop();
  EXPECT_TRUE(q.empty());

  // Push after pop
  q.push(1);
  q.push(2);
  q.pop();
  q.push(3);
  EXPECT_EQ(q.front(), 2);
  EXPECT_EQ(q.back(), 3);
}

TEST(QueueTest, InsertManyBack) {
  Queue<int> q;

  // Mass insertion
  q.insert_many_back(1, 2, 3);
  EXPECT_EQ(q.size(), 3);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 3);

  // Additional insertion
  q.insert_many_back(4, 5);
  EXPECT_EQ(q.size(), 5);
  EXPECT_EQ(q.front(), 1);
  EXPECT_EQ(q.back(), 5);

  // Check FIFO order via pop
  EXPECT_EQ(q.front(), 1); q.pop();
  EXPECT_EQ(q.front(), 2); q.pop();
  EXPECT_EQ(q.front(), 3); q.pop();
  EXPECT_EQ(q.front(), 4); q.pop();
  EXPECT_EQ(q.front(), 5); q.pop();
  EXPECT_TRUE(q.empty());
}

TEST(QueueTest, Stress) {
  Queue<int> q;
  const int N = 1000;

  // Enqueue many elements
  for (int i = 0; i < N; ++i) {
    q.push(i);
  }
  EXPECT_EQ(q.size(), N);
  EXPECT_EQ(q.front(), 0);

  // Dequeue all elements
  for (int i = 0; i < N; ++i) {
    EXPECT_EQ(q.front(), i);
    q.pop();
  }
  EXPECT_TRUE(q.empty());
}