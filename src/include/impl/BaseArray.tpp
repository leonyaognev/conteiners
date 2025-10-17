#pragma once

#include <sstream>

#include "array/BaseArray.h"
#include "logger.h"

template <typename T>
BaseArray<T>::iterator::iterator() : current(nullptr) {}

template <typename T>
BaseArray<T>::iterator::iterator(pointer ptr) : current(ptr) {}

template <typename T>
BaseArray<T>::iterator::iterator(const iterator& it) : current(it.current) {}

template <typename T>
typename BaseArray<T>::iterator::reference BaseArray<T>::iterator::operator*()
    const {
  return *current;
}

template <typename T>
typename BaseArray<T>::iterator::pointer BaseArray<T>::iterator::operator->()
    const {
  return current;
}

template <typename T>
typename BaseArray<T>::iterator& BaseArray<T>::iterator::operator++() {
  ++current;
  return *this;
}

template <typename T>
typename BaseArray<T>::iterator BaseArray<T>::iterator::operator++(int) {
  iterator tmp = *this;
  ++current;
  return tmp;
}

template <typename T>
typename BaseArray<T>::iterator& BaseArray<T>::iterator::operator--() {
  --current;
  return *this;
}

template <typename T>
typename BaseArray<T>::iterator BaseArray<T>::iterator::operator--(int) {
  iterator tmp = *this;
  --current;
  return tmp;
}

template <typename T>
bool BaseArray<T>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename T>
bool BaseArray<T>::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

// ---------------- BaseArray methods ----------------

template <typename T>
BaseArray<T>::BaseArray() : _data(nullptr), _capacity(0), _size(0) {}

template <typename T>
BaseArray<T>::BaseArray(std::size_t n)
    : _data(new T[n]), _capacity(sizeof(T) * n), _size(n) {}

template <typename T>
BaseArray<T>::BaseArray(std::size_t n, const T& value)
    : _data(new T[n]), _capacity(sizeof(T) * n), _size(n) {
  for (std::size_t i = 0; i < _size; i++) _data[i] = value;
}

template <typename T>
BaseArray<T>::BaseArray(const BaseArray& other)
    : _data(new T[other._size]),
      _capacity(sizeof(T) * other._size),
      _size(other._size) {
  for (std::size_t i = 0; i < _size; i++) _data[i] = other._data[i];
}

template <typename T>
BaseArray<T>::BaseArray(BaseArray&& other)
    : _data(other._data), _capacity(other._capacity), _size(other._size) {
  other._data = nullptr;
  other._size = 0;
  other._capacity = 0;
}

template <typename T>
BaseArray<T>& BaseArray<T>::operator=(const BaseArray& other) {
  if (this != &other) {
    delete[] _data;
    _data = new T[other._size];
    _capacity = sizeof(T) * other._size;
    _size = other._size;
    for (std::size_t i = 0; i < _size; i++) _data[i] = other._data[i];
  }
  return *this;
}

template <typename T>
BaseArray<T>& BaseArray<T>::operator=(BaseArray&& other) {
  if (this != &other) {
    delete[] _data;
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
  }
  return *this;
}

template <typename T>
BaseArray<T>::~BaseArray() {
  delete[] _data;
}

template <typename T>
typename BaseArray<T>::iterator BaseArray<T>::begin() const {
  return iterator(_data);
}

template <typename T>
typename BaseArray<T>::iterator BaseArray<T>::end() const {
  return iterator(_data + _size);
}

template <typename T>
T& BaseArray<T>::at(std::size_t n) {
  return _data[n];
}

template <typename T>
const T& BaseArray<T>::at(std::size_t n) const {
  return _data[n];
}

template <typename T>
T& BaseArray<T>::front() {
  return _data[0];
}

template <typename T>
const T& BaseArray<T>::front() const {
  return _data[0];
}

template <typename T>
T& BaseArray<T>::back() {
  return _data[_size - 1];
}

template <typename T>
const T& BaseArray<T>::back() const {
  return _data[_size - 1];
}

template <typename T>
T* BaseArray<T>::data() {
  return _data;
}

template <typename T>
const T* BaseArray<T>::data() const {
  return _data;
}

template <typename T>
bool BaseArray<T>::empty() const noexcept {
  return _size == 0;
}

template <typename T>
std::size_t BaseArray<T>::size() const noexcept {
  return _size;
}

template <typename T>
std::size_t BaseArray<T>::capacity() const noexcept {
  return _capacity;
}

template <typename T>
void BaseArray<T>::Print() {
  std::stringstream out;
  out << "[";
  for (size_t i = 0; i < _size; i++) {
    out << _data[i];
    if (i != _size - 1) out << ", ";
  }
  out << "]";
  std::string str = out.str();
  log_info("Array: %s", str.c_str());
}

template <typename T>
T& BaseArray<T>::operator[](std::size_t index) {
  return _data[index];
}
template <typename T>
const T& BaseArray<T>::operator[](std::size_t index) const {
  return _data[index];
}
