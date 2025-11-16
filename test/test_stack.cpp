#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "../src/include/list/Stack.h"

// ==================== STACK TESTS ====================

void test_stack_basic() {
  std::cout << "Testing stack basic operations..." << std::endl;

  Stack<int> st;

  // Test empty stack
  assert(st.empty());
  assert(st.size() == 0);

  // Push elements
  st.push(1);
  st.push(2);
  st.push(3);

  assert(st.size() == 3);
  assert(st.top() == 3);

  // Pop elements (LIFO)
  st.pop();
  assert(st.top() == 2);
  assert(st.size() == 2);

  st.pop();
  assert(st.top() == 1);
  assert(st.size() == 1);

  st.pop();
  assert(st.empty());

  std::cout << "stack basic operations: PASSED" << std::endl;
}

void test_stack_emplace() {
  std::cout << "Testing stack emplace..." << std::endl;

  Stack<std::string> st;

  st.emplace("hello");
  st.emplace(3, 'a');

  assert(st.size() == 2);
  assert(st.top() == "aaa");

  st.pop();
  assert(st.top() == "hello");

  std::cout << "stack emplace: PASSED" << std::endl;
}

void test_stack_copy_move() {
  std::cout << "Testing stack copy and move..." << std::endl;

  Stack<int> st1;
  st1.push(1);
  st1.push(2);
  st1.push(3);

  // Copy constructor
  Stack<int> st2(st1);
  assert(st2.size() == 3);
  assert(st2.top() == 3);

  // Move constructor
  Stack<int> st3(std::move(st2));
  assert(st3.size() == 3);
  assert(st2.empty());

  // Copy assignment
  Stack<int> st4;
  st4 = st3;
  assert(st4.size() == 3);
  assert(st4.top() == 3);

  // Move assignment
  Stack<int> st5;
  st5 = std::move(st4);
  assert(st5.size() == 3);
  assert(st4.empty());

  std::cout << "stack copy and move: PASSED" << std::endl;
}

void test_stack_edge_cases() {
  std::cout << "Testing stack edge cases..." << std::endl;

  Stack<int> st;

  // Empty stack
  assert(st.empty());
  assert(st.size() == 0);

  // Single element
  st.push(42);
  assert(st.size() == 1);
  assert(st.top() == 42);

  st.pop();
  assert(st.empty());

  // Push after pop
  st.push(1);
  st.push(2);
  st.pop();
  st.push(3);
  assert(st.top() == 3);
  assert(st.size() == 2);

  std::cout << "stack edge cases: PASSED" << std::endl;
}

// ==================== STRESS TEST ====================

void test_stress_stack() {
  std::cout << "Testing stack stress..." << std::endl;

  Stack<int> st;
  const int N = 1000;

  // Push many elements
  for (int i = 0; i < N; ++i) {
    st.push(i);
  }
  assert(st.size() == N);
  assert(st.top() == N - 1);

  // Pop all elements
  for (int i = N - 1; i >= 0; --i) {
    assert(st.top() == i);
    st.pop();
  }
  assert(st.empty());

  std::cout << "stack stress: PASSED" << std::endl;
}

// ==================== COMPARISON TESTS ====================

void test_stack_insert_many_back() {
  std::cout << "Testing stack insert_many_back..." << std::endl;

  Stack<int> st;

  // Массовая вставка в стек
  st.insert_many_back(1, 2, 3);
  assert(st.size() == 3);
  assert(st.top() == 3);  // LIFO - последний добавленный наверху

  // Дополнительная вставка
  st.insert_many_back(4, 5);
  assert(st.size() == 5);
  assert(st.top() == 5);  // Последний добавленный наверху

  // Извлечение и проверка порядка (LIFO)
  assert(st.top() == 5);
  st.pop();
  assert(st.top() == 4);
  st.pop();
  assert(st.top() == 3);
  st.pop();
  assert(st.top() == 2);
  st.pop();
  assert(st.top() == 1);
  st.pop();
  assert(st.empty());

  std::cout << "stack insert_many_back: PASSED" << std::endl;
}

// ==================== MAIN ====================

int main() {
  std::cout << "=== STARTING CONTAINERS TESTS ===" << std::endl;

  // stack tests
  test_stack_basic();
  test_stack_emplace();
  test_stack_copy_move();
  test_stack_edge_cases();
  test_stack_insert_many_back();

  // Stress test
  test_stress_stack();

  std::cout << "=== ALL TESTS PASSED! ===" << std::endl;
  return 0;
}