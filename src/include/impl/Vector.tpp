#pragma once

#include <sstream>

#include "array/Vector.h"
#include "logger.h"

template <typename T>
Vector<T>::iterator::iterator() : current(nullptr) {}

template <typename T>
Vector<T>::iterator::iterator(pointer ptr) : current(ptr) {}

template <typename T>
Vector<T>::iterator::iterator(const iterator& it) : current(it.current) {}

template <typename T>
typename Vector<T>::iterator::reference Vector<T>::iterator::operator*()
    const {
  return *current;
}

template <typename T>
typename Vector<T>::iterator::pointer Vector<T>::iterator::operator->()
    const {
  return current;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator++() {
  ++current;
  return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator++(int) {
  iterator tmp = *this;
  ++current;
  return tmp;
}

template <typename T>
typename Vector<T>::iterator& Vector<T>::iterator::operator--() {
  --current;
  return *this;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator--(int) {
  iterator tmp = *this;
  --current;
  return tmp;
}

template <typename T>
bool Vector<T>::iterator::operator==(const iterator& other) const {
  return current == other.current;
}

template <typename T>
bool Vector<T>::iterator::operator!=(const iterator& other) const {
  return current != other.current;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator=(const iterator& other) {
  current = other.current;
  return current;
}

// ---------------- Vector methods ----------------

template <typename T>
Vector<T>::Vector() : _data(nullptr), _capacity(0), _size(0) {}

template <typename T>
Vector<T>::Vector(std::size_t n)
    : _data(new T[n]()), _capacity(n), _size(n) {}

template <typename T>
Vector<T>::Vector(std::size_t n, const T& value)
    : _data(new T[n]), _capacity(n), _size(n) {
  for (std::size_t i = 0; i < _size; i++) _data[i] = value;
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : _data(new T[other._size]),
      _capacity(other._size),
      _size(other._size) {
  for (std::size_t i = 0; i < _size; i++) _data[i] = other._data[i];
}

template <typename T>
Vector<T>::Vector(Vector&& other)
    : _data(other._data), _capacity(other._capacity), _size(other._size) {
  other._data = nullptr;
  other._size = 0;
  other._capacity = 0;
}

template <typename T>
Vector<T>::Vector(std::initializer_list<T> init_list) : _data(new T[init_list.size()]), _capacity(init_list.size()), _size(init_list.size()){
	std::size_t i = 0;
	for (const T& value : init_list) {
        _data[i++] = value;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
  if (this != &other) {
    delete[] _data;
    _data = new T[other._size];
    _capacity = other._size;
    _size = other._size;
    for (std::size_t i = 0; i < _size; i++) _data[i] = other._data[i];
  }
  return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
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
Vector<T>::~Vector() {
  delete[] _data;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::begin() const {
  return iterator(_data);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::end() const {
  return iterator(_data + _size);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator+(size_t n){
  return iterator(current + n);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::iterator::operator-(size_t n){
  return iterator(current - n);
}

template <typename T>
T& Vector<T>::at(std::size_t n) {
  return _data[n];
}

template <typename T>
const T& Vector<T>::at(std::size_t n) const {
  return _data[n];
}

template <typename T>
T& Vector<T>::front() {
  return _data[0];
}

template <typename T>
const T& Vector<T>::front() const {
  return _data[0];
}

template <typename T>
T& Vector<T>::back() {
  return _data[_size - 1];
}

template <typename T>
const T& Vector<T>::back() const {
  return _data[_size - 1];
}

template <typename T>
T* Vector<T>::data() {
  return _data;
}

template <typename T>
const T* Vector<T>::data() const {
  return _data;
}

template <typename T>
bool Vector<T>::empty() const noexcept {
  return _size == 0;
}

template <typename T>
std::size_t Vector<T>::size() const noexcept {
  return _size;
}

template <typename T>
std::size_t Vector<T>::capacity() const noexcept {
  return _capacity;
}

template <typename T>
void Vector<T>::Print() {
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
T& Vector<T>::operator[](std::size_t index) {
  return _data[index];
}

template <typename T>
const T& Vector<T>::operator[](std::size_t index) const {
  return _data[index];
}

template <typename T>
Vector<T>::iterator Vector<T>::erase(iterator pos){
  for (auto a = pos; a != (end() - 1); a++){
    *a = *(a + 1);
  }
  _size--;
  return begin();
}

template <typename T>
typename Vector<T>::iterator Vector<T>::erase(iterator first, iterator last){
  size_t iter = 0;
  auto b = last;
  for (auto a = first; b != end(); a++){
    *a = *b;
    b++;
    iter++;
  }
  _size = _size - (last.current - first.current);
  return begin();
}

template <typename T>
void Vector<T>::pop_back(){
	if (_size > 0) _size--; 
}

template <typename T>
void Vector<T>::push_back(const T& value){
	if (_size == _capacity) extend();
		auto i = end();
		*i = value;
		_size++;
}

template <typename T>
void Vector<T>::push_back(T&& value){
	if (_size == _capacity) extend();
		auto i = end();
		*i = value;
		_size++;
}

template <typename T>
void Vector<T>::extend(){
	std::size_t tempCapacity = _capacity * 2;
	T* tempData = new T[tempCapacity]();
	for (std::size_t i = 0; i < _capacity; i++){
		tempData[i] = _data[i];
	}
	delete[] _data;
	_data = tempData;
	_capacity = tempCapacity;
}

template <typename T>
void Vector<T>::extend(std::size_t newCapacity){
	T* tempData = new T[newCapacity]();
	std::size_t minSize = newCapacity < _size ? newCapacity : _size;
	for (std::size_t i = 0; i < minSize; i++){
		tempData[i] = _data[i];
	}
	delete[] _data;
	_data = tempData;
	_capacity = newCapacity;
}

template <typename T>
void Vector<T>::shrink_to_fit(){
	extend(_size);
}

template <typename T>
void Vector<T>::resize(std::size_t newSize){
	if (newSize > _capacity) extend(newSize);
	_size = newSize;
}

template <typename T>
void Vector<T>::resize(std::size_t newSize, const T& value){
	if (newSize > _capacity) extend(newSize);
	for(std::size_t i = _size; i < newSize; i++){
		_data[i] = value;
	}
	_size = newSize;
}

template <typename T>
void Vector<T>::reserve(std::size_t new_cap){
  if (new_cap > _capacity) extend(new_cap);
}

template <typename T>
void Vector<T>::swap(Vector& other){
  std::swap(_data, other._data);
  std::swap(_capacity, other._capacity);
  std::swap(_size, other._size);
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, const T& value){
  std::size_t shift = pos.current - _data;
  if (_size == _capacity) extend();

  pos = iterator(_data + shift);
  for (std::size_t i = _size; i != shift; i--){
   _data[i] = _data[i - 1];
  }
  *pos = value;
  _size++;
  return pos;
}

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, T&& value){
  std::size_t shift = pos.current - _data;
  if (_size == _capacity) extend();

  pos = iterator(_data + shift);
  for (std::size_t i = _size; i != shift; i--){
   _data[i] = _data[i - 1];
  }
  *pos = value;
  _size++;
  return pos;
}  

template <typename T>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, std::size_t count, const T& value){
  std::size_t shift = pos.current - _data; //получаем индекс с которого вставляем
  if ((count + _size) > (2 * _capacity)){
    extend(count + _size);
  }  else if (count + _size > _capacity){
    extend();
  }
  pos = iterator(_data + shift); //указатель на элемент, с которого начинаем вставку
  for (std::size_t i = _size - 1; i >= shift; i--){
    _data[i + count] = _data[i];
  }
  for (std::size_t i = 0; i != count; i++){
    _data[shift + i] = value;
  }
  _size = _size + count;
  return pos;
}

template <typename T>
template <typename InputIt>
typename Vector<T>::iterator Vector<T>::insert(iterator pos, InputIt first, InputIt last){
	std::size_t posIndex = pos.current - _data;
	std::size_t count = std::distance(first, last);
	if ((count + _size) > (2 * _capacity)){
    extend(count + _size);
  }  else if (count + _size > _capacity){
    extend();
  }
  pos = iterator(_data + posIndex);
  for (std::size_t i = _size - 1; i >= posIndex; i--){
	_data[i + count] = _data[i];
  }
  for (std::size_t i = 0; i < count; i++){
	_data[i + posIndex] = *(first + i);
  }
  _size = _size + count;
  return pos;
}

template <typename T>
void Vector<T>::clear(){
  for (std::size_t i = 0; i < _size; i++){
    _data[i].~T();
  }
  _size = 0;
}

template <typename T>
template <typename... Args>
T& Vector<T>::emplace_back(Args&&... args){
  if (_size == _capacity) extend();
  new(end().current) T(std::forward<Args>(args)...);
  _size++;
  return _data[_size - 1];
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::emplace(iterator pos, Args&&... args){
  std::size_t shift = pos.current - _data;
  if (_size == _capacity) extend();
  for (std::size_t i = _size; i != shift; i--){
    _data[i] = _data[i - 1];
  }
  new(begin().current + shift) T(std::forward<Args>(args)...);
  _size++;
  return begin() + shift;
}

template <typename T>
void Vector<T>::assign(std::size_t count, const T& value){
  if(count > _capacity) extend(count);
  for (std::size_t i = 0; i < count; i++){
    _data[i] = value;
  }
  _size = count;
}

template <typename T>
void Vector<T>::assign(iterator first, iterator last){
  std::size_t shift = last.current - first.current;
  if (shift > _capacity) extend(shift);
  auto pos = first;
  for (std::size_t i = 0; i < shift; i++){
    _data[i] = *pos;
    pos++;
  }
  _size = shift;
}

template <typename T>
void Vector<T>::assign(std::initializer_list<T> init_list){
    std::size_t count = init_list.size();

    if (count > _capacity)
        extend(count);

    std::size_t i = 0;
    for (const T& value : init_list) {
        _data[i++] = value;
    }

    _size = count;
}

template <typename T>
template <typename... Args>
void Vector<T>::insert_many_back(Args&&... args){
	(push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
typename Vector<T>::iterator Vector<T>::insert_many(iterator pos, Args&&... args) {
    ((pos = emplace(pos, std::forward<Args>(args)), ++pos), ...);
    return pos;
}