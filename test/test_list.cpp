#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>

#include "../src/include/list/List.h"

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

void test_list_emplace() {
  std::cout << "Testing list emplace..." << std::endl;

  // Emplace at front
  List<std::string> lst;

  lst.emplaceFront("world");
  lst.emplaceFront("hello");
  assert(lst.size() == 2);
  assert(lst.front() == "hello");
  assert(lst.back() == "world");

  // Emplace at back
  lst.emplaceBack("test");
  assert(lst.size() == 3);
  assert(lst.back() == "test");

  // Emplace in middle
  auto it = lst.begin();
  ++it;
  lst.emplace(it, "middle");
  assert(lst.size() == 4);

  it = lst.begin();
  assert(*it == "hello");
  ++it;
  assert(*it == "middle");
  ++it;
  assert(*it == "world");
  ++it;
  assert(*it == "test");

  std::cout << "list emplace: PASSED" << std::endl;
}

void test_list_resize() {
  std::cout << "Testing list resize..." << std::endl;
  // Resize up with default values
  List<int> lst;

  lst.resize(3);
  assert(lst.size() == 3);
  assert(lst.front() == 0);
  assert(lst.back() == 0);

  // Resize up with custom value
  lst.resize(5, 42);
  assert(lst.size() == 5);
  assert(lst.back() == 42);

  // Resize down
  lst.resize(2);
  assert(lst.size() == 2);
  assert(lst.front() == 0);
  assert(lst.back() == 0);

  // Resize empty list
  List<int> empty_lst;
  empty_lst.resize(3, 10);
  assert(empty_lst.size() == 3);
  assert(empty_lst.front() == 10);
  assert(empty_lst.back() == 10);

  std::cout << "list resize: PASSED" << std::endl;
}

void test_list_splice() {
  std::cout << "Testing list splice..." << std::endl;

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
  assert(lst1.size() == 6);
  assert(lst2.empty());
  assert(lst1.back() == 6);

  // Reset
  lst2.pushBack(7);
  lst2.pushBack(8);
  lst2.pushBack(9);

  // Splice single element
  auto it = lst2.begin();
  lst1.splice(lst1.begin(), lst2, it);
  assert(lst1.size() == 7);
  assert(lst2.size() == 2);
  assert(lst1.front() == 7);

  // Splice range
  auto first = lst2.begin();
  auto last = lst2.end();
  lst1.splice(lst1.end(), lst2, first, last);
  assert(lst1.size() == 9);
  assert(lst2.empty());
  assert(lst1.back() == 9);

  std::cout << "list splice: PASSED" << std::endl;
}

void test_list_merge() {
  std::cout << "Testing list merge..." << std::endl;

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
  assert(lst1.size() == 6);
  assert(lst2.empty());

  auto it = lst1.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);
  ++it;
  assert(*it == 4);
  ++it;
  assert(*it == 5);
  ++it;
  assert(*it == 6);

  std::cout << "list merge: PASSED" << std::endl;
}

void test_list_reverse_iterators() {
  std::cout << "Testing list reverse iterators..." << std::endl;

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
    count++;
  }
  assert(sum == 15);
  assert(count == 5);

  // Check reverse order
  auto rit = lst.rbegin();
  assert(*rit == 5);
  --rit;
  assert(*rit == 4);
  --rit;
  assert(*rit == 3);
  --rit;
  assert(*rit == 2);
  --rit;
  assert(*rit == 1);

  std::cout << "list reverse iterators: PASSED" << std::endl;
}

void test_list_insert_many() {
  std::cout << "Testing list insert_many..." << std::endl;

  List<int> lst;
  lst.pushBack(1);
  lst.pushBack(5);

  // Вставка нескольких элементов в середину
  auto it = lst.begin();
  ++it;
  auto result = lst.insert_many(it, 2, 3, 4);

  assert(lst.size() == 5);
  assert(*result == 2);  // Возвращает итератор на первый вставленный элемент

  // Проверяем порядок элементов
  auto check_it = lst.begin();
  assert(*check_it == 1);
  ++check_it;
  assert(*check_it == 2);
  ++check_it;
  assert(*check_it == 3);
  ++check_it;
  assert(*check_it == 4);
  ++check_it;
  assert(*check_it == 5);

  // Вставка в начало
  lst.insert_many(lst.begin(), -1, 0);
  assert(lst.size() == 7);
  assert(lst.front() == -1);

  // Вставка в конец
  lst.insert_many(lst.end(), 6, 7);
  assert(lst.size() == 9);
  assert(lst.back() == 7);

  // Вставка без аргументов (ничего не должно произойти)
  auto empty_result = lst.insert_many(lst.begin());
  assert(lst.size() == 9);
  assert(empty_result == lst.begin());

  std::cout << "list insert_many: PASSED" << std::endl;
}

void test_list_insert_many_back() {
  std::cout << "Testing list insert_many_back..." << std::endl;

  List<int> lst;

  // Вставка нескольких элементов в пустой список
  lst.insert_many_back(1, 2, 3);
  assert(lst.size() == 3);
  assert(lst.front() == 1);
  assert(lst.back() == 3);

  // Вставка дополнительных элементов
  lst.insert_many_back(4, 5);
  assert(lst.size() == 5);
  assert(lst.back() == 5);

  // Проверяем полный порядок
  auto it = lst.begin();
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);
  ++it;
  assert(*it == 4);
  ++it;
  assert(*it == 5);

  // Вставка разных категорий значений
  int x = 6;
  const int y = 7;
  lst.insert_many_back(x, y, 8);  // lvalue, const lvalue, rvalue
  assert(lst.size() == 8);
  assert(lst.back() == 8);

  // Вставка без аргументов (ничего не должно произойти)
  lst.insert_many_back();
  assert(lst.size() == 8);  // Размер не изменился

  std::cout << "list insert_many_back: PASSED" << std::endl;
}

void test_list_insert_many_front() {
  std::cout << "Testing list insert_many_front..." << std::endl;

  List<int> lst;

  // Вставка нескольких элементов в пустой список
  lst.insert_many_front(3, 2, 1);
  assert(lst.size() == 3);
  assert(lst.front() == 1);  // Последний вставленный становится первым
  assert(lst.back() == 3);   // Первый вставленный становится последним

  // Вставка дополнительных элементов
  lst.insert_many_front(5, 4);
  assert(lst.size() == 5);
  assert(lst.front() == 4);  // Новые элементы добавляются в начало

  // Проверяем полный порядок (обратный порядок вставки)
  auto it = lst.begin();
  assert(*it == 4);
  ++it;
  assert(*it == 5);
  ++it;
  assert(*it == 1);
  ++it;
  assert(*it == 2);
  ++it;
  assert(*it == 3);

  // Вставка разных категорий значений
  int x = 6;
  const int y = 7;
  lst.insert_many_front(y, x, 8);  // const lvalue, lvalue, rvalue
  assert(lst.size() == 8);
  assert(lst.front() == 8);

  // Вставка без аргументов (ничего не должно произойти)
  lst.insert_many_front();
  assert(lst.size() == 8);  // Размер не изменился

  std::cout << "list insert_many_front: PASSED" << std::endl;
}
// ==================== STRESS TESTS ====================
void test_stress_listbase() {
  std::cout << "Testing List stress..." << std::endl;

  List<int> list;
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

  std::cout << "List stress: PASSED" << std::endl;
}

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

int main() {
  std::cout << "=== STARTING CONTAINERS TESTS ===" << std::endl;

  // list tests
  test_list_basic();
  test_list_constructors();
  test_list_iterators();
  test_list_modifiers();
  test_list_operations();
  test_list_edge_cases();
  test_list_emplace();
  test_list_resize();
  test_list_splice();
  test_list_merge();
  test_list_reverse_iterators();
  test_list_insert_many();
  test_list_insert_many_back();
  test_list_insert_many_front();

  // Stress tests
  test_stress_listbase();

  // Comparison tests
  test_comparison_operations();

  std::cout << "=== ALL TESTS PASSED! ===" << std::endl;
  return 0;
}