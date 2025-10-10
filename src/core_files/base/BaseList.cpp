#include "../../include/list/ListBase.h"

template <typename T>
ListBase<T>::ListBase() : dummy(), _size(0) {}

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
void ListBase<T>::pushFront(T&& data) {
  insert(begin(), std::move(data));
}

template <typename T>
void ListBase<T>::pushFront(const T& data) {
  insert(begin(), data);
}

template <typename T>
void ListBase<T>::pushBack(T&& data) {
  insert(end(), std::move(data));
}

template <typename T>
void ListBase<T>::pushBack(const T& data) {
  insert(end(), data);
}

template <typename T>
void ListBase<T>::popFront() {
  if (!empty()) erase(begin());
}

template <typename T>
void ListBase<T>::popBack() {
  if (!empty()) erase(--end());
}

template <typename T>
typename ListBase<T>::iterator ListBase<T>::insert(iterator pos,
                                                   const T& data) {
  return insert(pos, T(data));
}

template <typename T>
typename ListBase<T>::iterator ListBase<T>::insert(iterator pos, T&& data) {
  node* newNode = new node(std::move(data));
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
                                                   const T& data) {
  if (count == 0) return pos;

  iterator res = insert(pos, data);
  iterator current = res;

  for (std::size_t i = 1; i < count; ++i) {
    current = insert(pos, data);
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
    current = insert(pos, *first);
    ++first;
  }
  return res;
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