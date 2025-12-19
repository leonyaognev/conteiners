#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

#include "RedBlackTree/Map.h"

// Тестируем map<int, std::string> для большинства случаев
using test_map = Map<int, std::string>;

// --- ГРУППА 1: КОНСТРУКТОРЫ И ДЕСТРУКТОРЫ ---

TEST(MapConstructors, Default) {
  test_map m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapConstructors, InitializerList) {
  test_map m = {{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], "one");
  EXPECT_EQ(m[3], "three");
}

TEST(MapConstructors, Copy) {
  test_map m1 = {{10, "ten"}, {20, "twenty"}};
  test_map m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m2[10], "ten");
  m2[10] = "changed";
  EXPECT_NE(m1[10], m2[10]);  // Проверка глубокого копирования
}

TEST(MapConstructors, Move) {
  test_map m1 = {{1, "a"}, {2, "b"}};
  test_map m2(std::move(m1));
  EXPECT_EQ(m2.size(), 2);
  EXPECT_TRUE(m1.empty());  // После move оригинал должен быть пуст
}

TEST(MapConstructors, AssignmentOperator) {
  test_map m1 = {{5, "5"}};
  test_map m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 1);
  EXPECT_EQ(m2[5], "5");
}

// --- ГРУППА 2: ДОСТУП К ЭЛЕМЕНТАМ ---

TEST(MapAccess, AtMethod) {
  test_map m = {{1, "apple"}, {2, "banana"}};
  EXPECT_EQ(m.at(1), "apple");
  EXPECT_EQ(m.at(2), "banana");
  EXPECT_THROW(m.at(3), std::out_of_range);  // Несуществующий ключ
}

TEST(MapAccess, OperatorSquareBrackets) {
  test_map m;
  m[10] = "ten";  // Вставка нового
  EXPECT_EQ(m.size(), 1);
  EXPECT_EQ(m[10], "ten");

  m[10] = "TEN";  // Обновление существующего
  EXPECT_EQ(m[10], "TEN");

  EXPECT_EQ(m[5], "");  // Обращение к новому ключу должно создать default value
  EXPECT_EQ(m.size(), 2);
}

TEST(MapAccess, ConstAccess) {
  const test_map m = {{1, "const"}};
  // m[1] = "error"; // Не должно компилироваться
  EXPECT_EQ(m.at(1), "const");
}

// --- ГРУППА 3: ИТЕРАТОРЫ ---

TEST(MapIterators, BeginEnd) {
  test_map m = {{3, "c"}, {1, "a"}, {2, "b"}};
  auto it = m.begin();
  EXPECT_EQ((*it).first, 1);  // Проверка сортировки (бинарное дерево)
  ++it;
  EXPECT_EQ((*it).first, 2);
  ++it;
  EXPECT_EQ((*it).first, 3);
  ++it;
  EXPECT_EQ(it, m.end());
}

TEST(MapIterators, PostfixIncrDecr) {
  test_map m = {{1, "1"}, {2, "2"}};
  auto it = m.begin();
  auto it_old = it++;
  EXPECT_EQ((*it_old).first, 1);
  EXPECT_EQ((*it).first, 2);
}

// --- ГРУППА 4: CAPACITY (ВМЕСТИМОСТЬ) ---

TEST(MapCapacity, EmptyAndSize) {
  test_map m;
  EXPECT_TRUE(m.empty());
  m.insert({1, "1"});
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 1);
}

TEST(MapCapacity, MaxSize) {
  test_map m;
  // Значение зависит от архитектуры, но должно быть > 0
  EXPECT_GT(m.max_size(), 0);
}

// --- ГРУППА 5: МОДИФИКАТОРЫ (MODIFIERS) ---

TEST(MapModifiers, Clear) {
  test_map m = {{1, "1"}, {2, "2"}};
  m.clear();
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(MapModifiers, InsertValue) {
  test_map m;
  auto res = m.insert({10, "ten"});
  EXPECT_TRUE(res.second);
  EXPECT_EQ((*res.first).second, "ten");

  auto res2 = m.insert({10, "duplicate"});
  EXPECT_FALSE(res2.second);  // Дубликат не вставляется
  EXPECT_EQ(m.at(10), "ten");
}

TEST(MapModifiers, InsertKeyAndObj) {
  test_map m;
  auto res = m.insert(5, "five");
  EXPECT_TRUE(res.second);
  EXPECT_EQ(m[5], "five");
}

TEST(MapModifiers, InsertOrAssign) {
  test_map m;
  m.insert_or_assign(1, "one");
  EXPECT_EQ(m[1], "one");

  m.insert_or_assign(1, "ONE");  // Должно перезаписать
  EXPECT_EQ(m[1], "ONE");
  EXPECT_EQ(m.size(), 1);
}

TEST(MapModifiers, Erase) {
  test_map m = {{1, "a"}, {2, "b"}, {3, "c"}};
  auto it = m.begin();  // ключ 1
  m.erase(it);
  EXPECT_EQ(m.size(), 2);
  EXPECT_FALSE(m.contains(1));
}

TEST(MapModifiers, Swap) {
  test_map m1 = {{1, "1"}};
  test_map m2 = {{2, "2"}, {3, "3"}};
  m1.swap(m2);
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m2.size(), 1);
  EXPECT_TRUE(m1.contains(2));
  EXPECT_TRUE(m2.contains(1));
}

TEST(MapModifiers, Merge) {
  test_map m1 = {{1, "a"}, {2, "b"}};
  test_map m2 = {{2, "duplicate"}, {3, "c"}};
  m1.merge(m2);

  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1.at(2), "b");  // m1 сохраняет свой элемент при конфликте
  EXPECT_EQ(m2.size(), 1);   // Элемент с ключом 2 остался в m2
  EXPECT_TRUE(m2.contains(2));
}

// --- ГРУППА 6: ПОИСК (LOOKUP) ---

TEST(MapLookup, Contains) {
  test_map m = {{100, "hundred"}};
  EXPECT_TRUE(m.contains(100));
  EXPECT_FALSE(m.contains(200));
}

// --- ГРУППА 7: СТРЕСС-ТЕСТЫ И ГРАНИЧНЫЕ СЛУЧАИ ---

TEST(MapStress, LargeInsertion) {
  Map<int, int> m;
  for (int i = 0; i < 1000; ++i) {
    m.insert({i, i});
  }
  EXPECT_EQ(m.size(), 1000);
  // Проверка, что дерево не развалилось и элементы на месте
  for (int i = 0; i < 1000; ++i) {
    EXPECT_EQ(m.at(i), i);
  }
}

TEST(MapStress, EraseRoot) {
  test_map m = {{10, "root"}, {5, "left"}, {15, "right"}};
  // Если 10 — корень, удаляем его
  auto it = m.begin();
  while ((*it).first != 10) ++it;

  m.erase(it);
  EXPECT_EQ(m.size(), 2);
  EXPECT_FALSE(m.contains(10));
  EXPECT_TRUE(m.contains(5));
  EXPECT_TRUE(m.contains(15));
}

TEST(MapStress, EmptyMapOperations) {
  test_map m;
  EXPECT_THROW(m.at(1), std::out_of_range);
  EXPECT_FALSE(m.contains(1));
  EXPECT_EQ(m.begin(), m.end());
  m.clear();  // не должно падать
  EXPECT_EQ(m.size(), 0);
}
