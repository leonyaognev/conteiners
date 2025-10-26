#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "../src/include/list/List.h"
#include "../src/include/list/Queue.h"
#include "../src/include/list/Stack.h"

// ==================== LIST TESTS ====================

void test_list_basic() {
  std::cout << "Testing list basic operations..." << std::endl;

  List<int> lst;

  // Push back
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  assert(lst.size() == 3);
  assert(lst.front() == 1);
  assert(lst.back() == 3);

  // Push front
  lst.pushFront(0);
  assert(lst.size() == 4);
  assert(lst.front() == 0);

  // Pop back
  lst.popBack();
  assert(lst.size() == 3);
  assert(lst.back() == 2);

  // Pop front
  lst.popFront();
  assert(lst.size() == 2);
  assert(lst.front() == 1);

  std::cout << "list basic operations: PASSED" << std::endl;
}

void test_list_constructors() {
  std::cout << "Testing list constructors..." << std::endl;

  List<int> lst1;
  assert(lst1.empty());

  List<int> lst2(std::size_t(3), 100);
  assert(lst2.size() == 3);
  assert(lst2.front() == 100);

  List<int> temp;
  temp.pushBack(1);
  temp.pushBack(2);
  temp.pushBack(3);

  List<int> lst3(temp.begin(), temp.end());
  assert(lst3.size() == 3);
  assert(lst3.front() == 1);
  assert(lst3.back() == 3);

  // Copy constructor
  List<int> lst4;
  lst4.pushBack(1);
  lst4.pushBack(2);
  lst4.pushBack(3);

  List<int> lst5(lst4);
  assert(lst5.size() == 3);
  assert(lst5.front() == 1);

  // Move constructor
  List<int> lst6(std::move(lst5));
  assert(lst6.size() == 3);
  assert(lst5.empty());

  std::cout << "list constructors: PASSED" << std::endl;
}

void test_list_iterators() {
  std::cout << "Testing list iterators..." << std::endl;

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
    count++;
  }
  assert(sum == 15);
  assert(count == 5);

  // Range-based for loop
  sum = 0;
  for (const auto& val : lst) {
    sum += val;
  }
  assert(sum == 15);

  // Iterator arithmetic
  auto it = lst.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  --it;
  assert(*it == 1);

  std::cout << "list iterators: PASSED" << std::endl;
}

void test_list_modifiers() {
  std::cout << "Testing list modifiers..." << std::endl;

  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);

  // Insert in middle
  auto it = lst.begin();
  ++it;
  lst.insert(it, 99);

  assert(lst.size() == 4);
  it = lst.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 99);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);

  // Erase from middle
  it = lst.begin();
  ++it;
  lst.erase(it);

  assert(lst.size() == 3);
  assert(lst.front() == 1);
  assert(lst.back() == 3);

  // Clear
  lst.clear();
  assert(lst.empty());
  assert(lst.size() == 0);

  std::cout << "list modifiers: PASSED" << std::endl;
}

void test_list_operations() {
  std::cout << "Testing list operations..." << std::endl;

  // Test remove
  List<int> lst1;
  lst1.pushBack(1);
  lst1.pushBack(2);
  lst1.pushBack(2);
  lst1.pushBack(3);
  lst1.pushBack(2);
  lst1.pushBack(4);

  lst1.remove(2);
  assert(lst1.size() == 3);
  assert(lst1.front() == 1);
  assert(lst1.back() == 4);

  // Test unique
  List<int> lst2;
  lst2.pushBack(1);
  lst2.pushBack(1);
  lst2.pushBack(2);
  lst2.pushBack(2);
  lst2.pushBack(3);
  lst2.pushBack(1);

  lst2.unique();
  assert(lst2.size() == 4);
  auto it = lst2.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);
  ++it;
  assert(*it == 1);

  // Test sort
  List<int> lst3;
  lst3.pushBack(3);
  lst3.pushBack(1);
  lst3.pushBack(4);
  lst3.pushBack(2);

  lst3.sort();
  it = lst3.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);
  ++it;
  assert(*it == 4);

  std::cout << "list operations: PASSED" << std::endl;
}

void test_list_edge_cases() {
  std::cout << "Testing list edge cases..." << std::endl;

  // Empty list operations
  List<int> empty_list;
  assert(empty_list.empty());
  assert(empty_list.size() == 0);

  // Pop on empty list (should not crash)
  empty_list.popBack();
  empty_list.popFront();
  assert(empty_list.empty());

  // Single element list
  List<int> single;
  single.pushBack(42);
  assert(single.size() == 1);
  assert(single.front() == 42);
  assert(single.back() == 42);

  single.popFront();
  assert(single.empty());

  // Self-assignment
  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(2);
  lst.pushBack(3);
  lst = lst;
  assert(lst.size() == 3);
  assert(lst.front() == 1);

  std::cout << "list edge cases: PASSED" << std::endl;
}

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

// ==================== STRESS TESTS ====================

void test_stress_listbase() {
  std::cout << "Testing ListBase stress..." << std::endl;

  ListBase<int> list;
  const int N = 1000;

  // Add many elements
  for (int i = 0; i < N; ++i) {
    list.pushBack(i);
  }
  assert(list.size() == N);
  assert(list.front() == 0);
  assert(list.back() == N - 1);

  // Remove all elements
  for (int i = 0; i < N; ++i) {
    list.popFront();
  }
  assert(list.empty());

  std::cout << "ListBase stress: PASSED" << std::endl;
}

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

void test_stress_mixed_operations() {
  std::cout << "Testing mixed operations stress..." << std::endl;

  List<int> lst;
  const int N = 500;

  // Mixed push/pop operations
  for (int i = 0; i < N; ++i) {
    lst.pushBack(i);
    if (i % 10 == 0) {
      lst.popFront();
    }
  }

  // Verify integrity
  assert(lst.size() > 0);
  assert(lst.front() >= 0);
  assert(lst.back() == N - 1);

  std::cout << "mixed operations stress: PASSED" << std::endl;
}

// ==================== COMPARISON TESTS ====================

void test_comparison_operations() {
  std::cout << "Testing comparison operations..." << std::endl;

  // Test assignment operators
  List<int> lst1;
  lst1.pushBack(1);
  lst1.pushBack(2);
  lst1.pushBack(3);

  List<int> lst2;
  lst2 = lst1;
  assert(lst2.size() == 3);
  assert(lst2.front() == 1);

  // Test move assignment
  List<int> lst3;
  lst3.pushBack(4);
  lst3.pushBack(5);
  lst3.pushBack(6);

  lst2 = std::move(lst3);
  assert(lst2.size() == 3);
  assert(lst2.front() == 4);
  assert(lst3.empty());

  // Test swap
  List<int> lst4;
  lst4.pushBack(1);
  lst4.pushBack(2);
  lst4.pushBack(3);

  List<int> lst5;
  lst5.pushBack(4);
  lst5.pushBack(5);

  lst4.swap(lst5);
  assert(lst4.size() == 2);
  assert(lst5.size() == 3);
  assert(lst4.front() == 4);
  assert(lst5.front() == 1);

  std::cout << "comparison operations: PASSED" << std::endl;
}

// ==================== MAIN ====================

int main() {
  std::cout << "=== STARTING CONTAINERS TESTS ===" << std::endl;

  // list tests
  test_list_basic();
  test_list_constructors();
  test_list_iterators();
  test_list_modifiers();
  test_list_operations();
  test_list_edge_cases();

  // queue tests
  test_queue_basic();
  test_queue_emplace();
  test_queue_edge_cases();

  // stack tests
  test_stack_basic();
  test_stack_emplace();
  test_stack_edge_cases();

  // Stress tests
  test_stress_listbase();
  test_stress_queue();
  test_stress_stack();
  test_stress_mixed_operations();

  // Comparison tests
  test_comparison_operations();

  std::cout << "=== ALL TESTS PASSED! ===" << std::endl;
  return 0;
}