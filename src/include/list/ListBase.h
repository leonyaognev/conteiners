#pragma once
#include <utility>

template <typename T>
class ListBase {
 private:
  class node {
   public:
    T data;
    node* next;
    node* prev;

    node() : next(this), prev(this) {};
    node(const T& value) : data(value) {}
    node(T&& value) : data(std::move(value)) {}
  };

  class iterator {
   public:
    using valueType = T;
    using pointer = T*;
    using reference = T&;

    node* current;

    iterator() : current(nullptr) {}
    iterator(node* ptr) : current(ptr) {}
    iterator(const iterator& it) : current(it.current) {}

    reference operator*() const { return current->data; }
    pointer operator->() const { return &current->data; }

    inline iterator& operator++() {
      current = current->next;
      return *this;
    }
    inline iterator operator++(int) {
      iterator tmp = *this;
      current = current->next;
      return tmp;
    };

    inline iterator& operator--() {
      current = current->prev;
      return *this;
    }
    inline iterator operator--(int) {
      iterator tmp = *this;
      current = current->prev;
      return tmp;
    }

    inline bool operator==(const iterator& other) const {
      return current == other.current;
    }
    inline bool operator!=(const iterator& other) const {
      return current != other.current;
    }
  };

  node dummy;

  std::size_t _size = 0;

 public:
  ListBase();
  ListBase(const ListBase& other);
  ListBase(ListBase&& other) noexcept;
  ~ListBase() noexcept { clear(); };

  iterator insert(iterator pos, const T& data);
  iterator insert(iterator pos, T&& data);
  iterator insert(iterator pos, std::size_t count, const T& data);
  template <typename InputIt>
  iterator insert(iterator pos, InputIt first, InputIt last);

  iterator erase(iterator pos);
  iterator erase(iterator first, iterator last);

  void pushFront(T&& data);
  void pushFront(const T& data);

  void pushBack(T&& data);
  void pushBack(const T& data);

  void popFront();
  void popBack();

  inline iterator begin() noexcept { return iterator(dummy.next); }
  inline iterator end() noexcept { return iterator(dummy); }
  inline iterator rbegin() noexcept { return iterator(dummy.prev); }
  inline iterator rend() noexcept { return iterator(dummy); }

  inline std::size_t size() const noexcept { return _size; };
  void clear() noexcept;
  inline bool empty() const noexcept { return _size == 0; };

  ListBase& operator=(const ListBase& other);
  ListBase& operator=(ListBase&& other) noexcept;
};
