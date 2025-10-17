#pragma once

#include <new>

#include "list/ListBase.h"

template <typename T>
ListBase<T>::ListBase() : dummy(), _size(0) {}

template <typename T>
ListBase<T>::ListBase(std::size_t count, const T& value) : ListBase() {
  for (std::size_t i = 0; i < count; ++i) {
    pushBack(value);
  }
}

template <typename T>
template <typename InputIt>
ListBase<T>::ListBase(InputIt first, InputIt last) : ListBase() {
  for (auto it = first; it != last; ++it) {
    pushBack(*it);
  }
}

template <typename T>
ListBase<T>::ListBase(const ListBase& other) : ListBase() {
  for (auto it = other.begin(); it != other.end(); ++it) {
    pushBack(*it);
  }
}

template <typename T>
ListBase<T>::ListBase(ListBase&& other) noexcept : dummy(), _size(other._size) {
  if (other.empty()) {
    dummy.next = &dummy;
    dummy.prev = &dummy;
  } else {
    dummy.next = other.dummy.next;
    dummy.prev = other.dummy.prev;

    dummy.next->prev = &dummy;
    dummy.prev->next = &dummy;

    other.dummy.next = &other.dummy;
    other.dummy.prev = &other.dummy;
    other._size = 0;
  }
}

template <typename T>
void ListBase<T>::assign(std::size_t count, const T& value) {
  clear();
  for (std::size_t i = 0; i < count; ++i) {
    pushBack(value);
  }
}

template <typename T>
template <typename InputIt>
void ListBase<T>::assign(InputIt first, InputIt last) {
  clear();
  for (auto it = first; it != last; ++it) {
    pushBack(*it);
  }
}

template <typename T>
typename ListBase<T>::iterator ListBase<T>::insert(iterator pos, T&& value) {
  node* newNode;

  try {
    newNode = new node(std::move(value));
  } catch (const std::bad_alloc&) {
    throw;
  }

  node* posNode = pos.current;

  newNode->prev = posNode->prev;
  newNode->next = posNode;

  posNode->prev->next = newNode;
  posNode->prev = newNode;

  ++_size;
  return iterator(newNode);
}

template <typename T>
typename ListBase<T>::iterator ListBase<T>::insert(iterator pos,
                                                   std::size_t count,
                                                   const T& value) {
  if (count == 0) return pos;

  iterator res = insert(pos, value);
  iterator current = res;

  for (std::size_t i = 1; i < count; ++i) {
    try {
      current = insert(pos, value);
    } catch (const std::bad_alloc&) {
      throw;
    }
  }
  return res;
}

template <typename T>
template <typename InputIt>
typename ListBase<T>::iterator ListBase<T>::insert(iterator pos, InputIt first,
                                                   InputIt last) {
  if (first == last) return pos;

  iterator res = insert(pos, *first);
  ++first;

  iterator current = res;
  while (first != last) {
    try {
      current = insert(pos, *first);
      ++first;
    } catch (const std::bad_alloc&) {
      throw;
    }
  }
  return res;
}

template <typename T>
template <typename... Args>
typename ListBase<T>::iterator ListBase<T>::emplace(iterator pos,
                                                    Args&&... args) {
  node* newNode;

  try {
    newNode = new node(T(std::forward<Args>(args)...));
  } catch (const std::bad_alloc&) {
    throw;
  } catch (...) {
    throw std::bad_alloc();
  }

  node* posNode = pos.current;

  newNode->prev = posNode->prev;
  newNode->next = posNode;

  posNode->prev->next = newNode;
  posNode->prev = newNode;

  ++_size;
  return iterator(newNode);
}

template <typename T>
typename ListBase<T>::iterator ListBase<T>::erase(iterator pos) {
  if (pos == end() || empty()) return end();

  node* deleted = pos.current;
  iterator nextIterator(deleted->next);

  deleted->prev->next = deleted->next;
  deleted->next->prev = deleted->prev;

  delete deleted;
  --_size;

  return nextIterator;
}

template <typename T>
typename ListBase<T>::iterator ListBase<T>::erase(iterator first,
                                                  iterator last) {
  iterator current = first;
  while (current != last) {
    current = erase(current);
  }
  return last;
}

template <typename T>
void ListBase<T>::resize(std::size_t count, const T& value) {
  while (_size > count) {
    popBack();
  }
  while (_size < count) {
    pushBack(value);
  }
}

template <typename T>
void ListBase<T>::swap(ListBase& other) noexcept {
  if (this == &other) return;

  node tempDummy = dummy;
  std::size_t tempSize = _size;

  if (other.empty()) {
    dummy.next = &dummy;
    dummy.prev = &dummy;
  } else {
    dummy.next = other.dummy.next;
    dummy.prev = other.dummy.prev;
    dummy.next->prev = &dummy;
    dummy.prev->next = &dummy;
  }
  _size = other._size;

  if (tempSize == 0) {
    other.dummy.next = &other.dummy;
    other.dummy.prev = &other.dummy;
  } else {
    other.dummy.next = tempDummy.next;
    other.dummy.prev = tempDummy.prev;
    other.dummy.next->prev = &other.dummy;
    other.dummy.prev->next = &other.dummy;
  }
  other._size = tempSize;
}

template <typename T>
template <typename Compare>
void ListBase<T>::merge(ListBase& other, Compare comp) {
  if (this == &other) return;

  iterator it1 = begin();
  iterator it2 = other.begin();
  iterator end1 = end();
  iterator end2 = other.end();

  while (it1 != end1 && it2 != end2) {
    if (comp(*it2, *it1)) {
      node* nodeMove = it2.current;
      ++it2;

      nodeMove->prev->next = nodeMove->next;
      nodeMove->next->prev = nodeMove->prev;

      nodeMove->prev = it1.current->prev;
      nodeMove->next = it1.current;
      it1.current->prev->next = nodeMove;
      it1.current->prev = nodeMove;

      ++_size;
      --other._size;
    } else {
      ++it1;
    }
  }
  if (it2 != end2) {
    splice(end(), other, it2, end2);
  }
}

template <typename T>
void ListBase<T>::splice(iterator pos, ListBase& other) {
  if (other.empty()) return;

  splice(pos, other, other.begin(), other.end());
}

template <typename T>
void ListBase<T>::splice(iterator pos, ListBase& other, iterator it) {
  if (it == other.end()) return;

  iterator next = it;
  ++next;
  splice(pos, other, it, next);
}

template <typename T>
template <typename InputIt>
void ListBase<T>::splice(iterator pos, ListBase& other, InputIt first,
                         InputIt last) {
  if (first == last) return;

  std::size_t count = 0;
  for (auto it = first; it != last; ++it) {
    ++count;
  }

  node* firstNode = first.current;
  node* lastNode = last.current->prev;
  node* posNode = pos.current;

  firstNode->prev->next = last.current;
  last.current->prev = firstNode->prev;

  firstNode->prev = posNode->prev;
  lastNode->next = posNode;
  posNode->prev->next = firstNode;
  posNode->prev = lastNode;

  _size += count;
  other._size -= count;
}

template <typename T>
void ListBase<T>::remove(const T& value) {
  remove([&value](const T& elem) { return elem == value; });
}

template <typename T>
template <typename BinaryPredicate>
void ListBase<T>::remove(BinaryPredicate p) {
  iterator it = begin();
  iterator end_it = end();

  while (it != end_it) {
    if (p(*it)) {
      it = erase(it);
    } else {
      ++it;
    }
  }
}

template <typename T>
template <typename BinaryPredicate>
void ListBase<T>::unique(BinaryPredicate p) {
  if (_size <= 1) return;

  iterator current = begin();
  iterator next = current;
  ++next;
  while (next != end()) {
    if (p(*current, *next)) {
      next = erase(next);
    } else {
      current = next;
      ++next;
    }
  }
}

template <typename T>
template <typename Compare>
void ListBase<T>::sort(Compare comp) {
  if (_size <= 1) return;

  bool swaped;
  do {
    swaped = false;
    iterator it = begin();
    iterator next = it;
    ++next;

    while (next != end()) {
      if (comp(*next, *it)) {
        std::swap(*it, *next);
        swaped = true;
      }
      ++it;
      ++next;
    }
  } while (swaped);
}

template <typename T>
void ListBase<T>::clear() noexcept {
  while (!empty()) {
    popFront();
  }
}

template <typename T>
ListBase<T>& ListBase<T>::operator=(const ListBase& other) {
  if (this != &other) {
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
      pushBack(*it);
    }
  }
  return *this;
}

template <typename T>
ListBase<T>& ListBase<T>::operator=(ListBase&& other) noexcept {
  if (this != &other) {
    clear();
    if (!other.empty()) {
      dummy.next = other.dummy.next;
      dummy.prev = other.dummy.prev;

      dummy.next->prev = &dummy;
      dummy.prev->next = &dummy;

      _size = other._size;

      other.dummy.next = &other.dummy;
      other.dummy.prev = &other.dummy;
      other._size = 0;
    }
  }
  return *this;
}
