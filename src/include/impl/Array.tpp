#pragma once

#include <sstream>

#include "array/Array.h"
#include "logger.h"

template <typename T, std::size_t N>
void Array<T, N>::Print() {
  std::stringstream out;
  out << "[";
  for (size_t i = 0; i < size(); i++) {
    out << _data[i];
    if (i != size() - 1) out << ", ";
  }
  out << "]";
  std::string str = out.str();
  log_info("Array: %s", str.c_str());
}

/**-----------------------------
 *         ARRAY METHODS
 *------------------------------
 */

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::data() {
  return iterator(_data);
}

template <typename T, std::size_t N>
typename Array<T, N>::const_iterator Array<T, N>::data() const {
  return iterator(_data);
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::size_type Array<T, N>::size() const {
  return N;
}

template <typename T, std::size_t N>
typename Array<T, N>::size_type constexpr Array<T, N>::max_size() const {
  return N;
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::back() noexcept {
  return _data[N - 1];
}

template <typename T, std::size_t N>
constexpr typename Array<T, N>::const_reference Array<T, N>::back()
    const noexcept {
  return _data[N - 1];
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::begin() noexcept {
  return iterator(_data);
}

template <typename T, std::size_t N>
typename Array<T, N>::iterator Array<T, N>::end() noexcept {
  return iterator(_data + N);
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator Array<T, N>::begin() const noexcept {
  return const_iterator(_data);
}

template <typename T, size_t N>
typename Array<T, N>::const_iterator Array<T, N>::end() const noexcept {
  return const_iterator(_data + N);
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::at(
    typename Array<T, N>::size_type off) {
  if (off >= N) throw std::out_of_range("Index is out of range");
  return _data[off];
}

template <typename T, std::size_t N>
constexpr bool Array<T, N>::empty() const {
  return N == 0;
}

template <typename T, std::size_t N>
void Array<T, N>::fill(typename Array<T, N>::const_reference val) {
  for (std::size_t i = 0; i < N; i++) {
    _data[i] = val;
  }
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::front() {
  return _data[0];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference constexpr Array<T, N>::front() const {
  return _data[0];
}

template <typename T, std::size_t N>
void Array<T, N>::swap(Array& right) {
  std::swap(_data, right._data);
}

template <typename T, std::size_t N>
typename Array<T, N>::reference Array<T, N>::operator[](
    typename Array<T, N>::size_type off) {
  return _data[off];
}

template <typename T, std::size_t N>
typename Array<T, N>::const_reference Array<T, N>::operator[](
    typename Array<T, N>::size_type off) const {
  return _data[off];
}

// template <typename T, std::size_t N>
// Array<T,N>& Array<T,N>::operator=(Array<T,N>& right){
// 	for (std::size_t i = 0; i < N; i++){
// 		_data[i] = right._data[i];
// 	}
// 	return *this;
// }

// template <typename T, std::size_t N>
// Array<T,N>& Array<T,N>::operator=(Array<T,N>&& right) noexcept {
//     if (this != &right) {
//         for (std::size_t i = 0; i < N; i++) {
//             _data[i] = std::move(right._data[i]);
//         }
//     }
//     return *this;
// }
