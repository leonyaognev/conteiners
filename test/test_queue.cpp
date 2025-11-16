#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "../src/include/list/Queue.h"

// ==================== QUEUE TESTS ====================

void test_queue_basic() {
  std::cout << "Testing queue basic operations..." << std::endl;

  Queue<int> q;

  // Test empty queue
  assert(q.empty());
  assert(q.size() == 0);

  // Push elements
  q.push(1);
  q.push(2);
  q.push(3);

  assert(q.size() == 3);
  assert(q.front() == 1);
  assert(q.back() == 3);

  // Pop elements (FIFO)
  q.pop();
  assert(q.front() == 2);
  assert(q.size() == 2);

  q.pop();
  assert(q.front() == 3);
  assert(q.size() == 1);

  q.pop();
  assert(q.empty());

  std::cout << "queue basic operations: PASSED" << std::endl;
}

void test_queue_emplace() {
  std::cout << "Testing queue emplace..." << std::endl;

  Queue<std::string> q;

  q.emplace("hello");
  q.emplace(3, 'a');

  assert(q.size() == 2);
  assert(q.front() == "hello");
  assert(q.back() == "aaa");

  std::cout << "queue emplace: PASSED" << std::endl;
}

void test_queue_copy_move() {
  std::cout << "Testing queue copy and move..." << std::endl;

  Queue<int> q1;
  q1.push(1);
  q1.push(2);
  q1.push(3);

  // Copy constructor
  Queue<int> q2(q1);
  assert(q2.size() == 3);
  assert(q2.front() == 1);

  // Move constructor
  Queue<int> q3(std::move(q2));
  assert(q3.size() == 3);
  assert(q2.empty());

  // Copy assignment
  Queue<int> q4;
  q4 = q3;
  assert(q4.size() == 3);
  assert(q4.front() == 1);

  // Move assignment
  Queue<int> q5;
  q5 = std::move(q4);
  assert(q5.size() == 3);
  assert(q4.empty());

  std::cout << "queue copy and move: PASSED" << std::endl;
}

void test_queue_edge_cases() {
  std::cout << "Testing queue edge cases..." << std::endl;

  Queue<int> q;

  // Empty queue
  assert(q.empty());
  assert(q.size() == 0);

  // Single element
  q.push(42);
  assert(q.size() == 1);
  assert(q.front() == 42);
  assert(q.back() == 42);

  q.pop();
  assert(q.empty());

  // Push after pop
  q.push(1);
  q.push(2);
  q.pop();
  q.push(3);
  assert(q.front() == 2);
  assert(q.back() == 3);

  std::cout << "queue edge cases: PASSED" << std::endl;
}

// ==================== STRESS TEST ====================

void test_stress_queue() {
  std::cout << "Testing queue stress..." << std::endl;

  Queue<int> q;
  const int N = 1000;

  // Enqueue many elements
  for (int i = 0; i < N; ++i) {
    q.push(i);
  }
  assert(q.size() == N);
  assert(q.front() == 0);

  // Dequeue all elements
  for (int i = 0; i < N; ++i) {
    assert(q.front() == i);
    q.pop();
  }
  assert(q.empty());

  std::cout << "queue stress: PASSED" << std::endl;
}

// ==================== COMPARISON TEST ====================

void test_queue_insert_many_back() {
  std::cout << "Testing queue insert_many_back..." << std::endl;

  Queue<int> q;

  // Массовая вставка в очередь
  q.insert_many_back(1, 2, 3);
  assert(q.size() == 3);
  assert(q.front() == 1);
  assert(q.back() == 3);

  // Дополнительная вставка
  q.insert_many_back(4, 5);
  assert(q.size() == 5);
  assert(q.front() == 1);  // FIFO - первый остается
  assert(q.back() == 5);   // Последний добавленный

  // Извлечение и проверка порядка (FIFO)
  assert(q.front() == 1);
  q.pop();
  assert(q.front() == 2);
  q.pop();
  assert(q.front() == 3);
  q.pop();
  assert(q.front() == 4);
  q.pop();
  assert(q.front() == 5);
  q.pop();
  assert(q.empty());

  std::cout << "queue insert_many_back: PASSED" << std::endl;
}

int main() {
  std::cout << "=== STARTING CONTAINERS TESTS ===" << std::endl;

  // queue tests
  test_queue_basic();
  test_queue_emplace();
  test_queue_copy_move();
  test_queue_edge_cases();
  test_queue_insert_many_back();

  // Stress test
  test_stress_queue();

  std::cout << "=== ALL TESTS PASSED! ===" << std::endl;
  return 0;
}