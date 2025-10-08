#pragma once

#include <cstddef>
#include <sstream>
#include <string>

#include "logger.h"

template <typename T>
class BaseArray {
 private:
  T* _data;
  std::size_t _capacity;
  std::size_t _size;

  class iterator {
   public:
    using valueType = T;
    using pointer = T*;
    using reference = T&;

    pointer current;

    iterator() : current(nullptr) {}

    iterator(pointer ptr) : current(ptr) {}

    iterator(const iterator& it) : current(it.current) {}

    reference operator*() const { return *current; }

    pointer operator->() const { return current; }

    iterator& operator++() {
      ++current;
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++current;
      return tmp;
    };

    iterator& operator--() {
      --current;
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      --current;
      return tmp;
    }

    bool operator==(const iterator& other) const {
      return current == other.current;
    }

    bool operator!=(const iterator& other) const {
      return current != other.current;
    }
  };

  using Iterator = iterator;

 public:
  BaseArray() : _data(nullptr), _size(0), _capacity(0) {}
  BaseArray(std::size_t n) : _data(new T[n]), _size(n), _capacity(n) {}
  BaseArray(std::size_t n, const T& value)
      : _data(new T[n]), _size(n), _capacity(n) {
    for (std::size_t i = 0; i < _size; i++) {
      _data[i] = value;
    }
  }

  BaseArray(const BaseArray& other);
  BaseArray(BaseArray&& other);
  BaseArray operator=(const BaseArray& other);
  BaseArray operator=(BaseArray&& other);

  ~BaseArray() { delete[] _data; }

  iterator begin() const { return iterator(_data); }
  iterator end() const { return iterator(_data + _size); }

  T& at(std::size_t n) { return _data[n]; }
  const T& at(std::size_t n) const { return _data[n]; }

  T& front() { return _data[0]; }
  const T& front() const { return _data[0]; }

  T& back() { return _data[_size - 1]; }
  const T& back() const { return _data[_size - 1]; }

  T* data() { return _data; }
  const T* data() const { return _data; }

  bool empty() const noexcept { return _size == 0; }

  std::size_t size() const noexcept { return _size; }
  std::size_t capacity() const noexcept { return _capacity; }

  void reserve(std::size_t new_cap);
  void shrink_to_fit();

  void clear();

  iterator insert(iterator pos, const T& value);
  iterator insert(iterator pos, T&& value);
  iterator insert(iterator pos, std::size_t count, const T& value);
  template <typename InputIt>
  iterator insert(iterator pos, InputIt first, InputIt last);

  template <typename... Args>
  iterator emplace(iterator pos, Args&&... args);

  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);

  void push_back(const T& value);
  void push_back(T&& value);

  template <typename... Args>
  T& emplace_back(Args&&... args);

  void pop_back();

  void resize(std::size_t count);
  void resize(std::size_t count, const T& value);

  void swap(BaseArray& other);

  T& operator[](std::size_t index) { return _data[index]; }

  const T& operator[](std::size_t index) const { return _data[index]; }

  auto operator<=>(BaseArray other);

  void Print() {
    std::stringstream out;
    for (size_t i = 0; i < _size; i++) {
      out << _data[i];
    }
    std::string str = out.str();
    log_info("Array: %s", str.c_str());
  }
};
