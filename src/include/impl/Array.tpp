#pragma once

#include <sstream>

#include "array/Array.h"
#include "logger.h"

template <typename T, std::size_t N>
Array<T,N>::iterator::iterator() : current(nullptr) {}

template <typename T, std::size_t N>
Array<T,N>::iterator::iterator(pointer ptr) : current(ptr) {}

template <typename T, std::size_t N>
Array<T,N>::iterator::iterator(const iterator& it) : current(it.current) {}

template <typename T, std::size_t N>
typename Array<T,N>::iterator::reference Array<T,N>::iterator::operator*()
    const {
  return *current;
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator::pointer Array<T,N>::iterator::operator->()
    const {
  return current;
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator& Array<T,N>::iterator::operator++() {
  ++current;
  return *this;
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::iterator::operator+(size_t n){
  return iterator(current + n);
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::iterator::operator-(size_t n){
  return iterator(current - n);
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::iterator::operator++(int) {
  iterator tmp = *this;
  ++current;
  return tmp;
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator& Array<T,N>::iterator::operator--() {
  --current;
  return *this;
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::iterator::operator--(int) {
  iterator tmp = *this;
  --current;
  return tmp;
}

template <typename T, std::size_t N>
bool Array<T,N>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename T, std::size_t N>
bool Array<T,N>::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::iterator::operator=(const iterator& other) {
  current = other.current;
  return *this;
}

template <typename T, std::size_t N>
void Array<T,N>::Print() {
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
T* Array<T,N>::data(){
  return _data;
}

template <typename T, std::size_t N>
const T* Array<T,N>::data() const{
  return _data;
}

template <typename T, std::size_t N>
typename Array<T,N>::size_type constexpr Array<T,N>::size() const{
    return N;
}

template <typename T, std::size_t N>
typename Array<T,N>::size_type constexpr Array<T,N>::max_size() const{
    return N;
}

template <typename T, std::size_t N>
typename Array<T,N>::reference Array<T,N>::back() noexcept{
  return _data[N - 1];
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::begin() noexcept{
  return iterator(_data);
}

template <typename T, std::size_t N>
typename Array<T,N>::iterator Array<T,N>::end(){
  return iterator(_data + N);
 }

template<typename T, size_t N>
typename Array<T,N>::const_iterator Array<T,N>::begin() const noexcept {
    return const_iterator(_data);
}

template<typename T, size_t N>
typename Array<T,N>::const_iterator Array<T,N>::end() const noexcept {
    return const_iterator(_data + N);
}

template <typename T, std::size_t N>
typename Array<T,N>::reference Array<T,N>::at(typename Array<T,N>::size_type off){
  return _data[off];
}

template <typename T, std::size_t N>
constexpr bool Array<T,N>::empty() const {
  return N == 0;
}

template <typename T, std::size_t N>
 void Array<T,N>::fill(typename Array<T,N>::const_reference val){
  for (std::size_t i = 0; i < N; i++){
    _data[i] = val;
  }
 }

template <typename T, std::size_t N>
typename Array<T,N>::reference Array<T,N>::front(){
  return _data[0];
}

template <typename T, std::size_t N>
typename Array<T,N>::const_reference constexpr Array<T,N>::front() const{
  return _data[0];
}

template <typename T, std::size_t N>
void Array<T,N>::swap(Array& right){
  std::swap(_data, right._data);
}

template <typename T, std::size_t N>
typename Array<T,N>::reference Array<T,N>::operator[](typename Array<T,N>::size_type off){
	return _data[off];
}

template <typename T, std::size_t N>
typename Array<T,N>::const_reference Array<T,N>::operator[](typename Array<T,N>::size_type off) const{
	return _data[off];
}
