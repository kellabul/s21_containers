#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iterator>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() : arr_(nullptr), size_(0), capacity_(0) {}

  explicit vector(size_type n) : vector() {
    size_ = n;
    capacity_ = n;
    if (size_ > 0) {
      arr_ = new value_type[n];
    }
  }

  vector(std::initializer_list<value_type> const &items) : vector() {
    size_ = items.size();
    capacity_ = items.size();
    arr_ = new value_type[capacity_];
    std::copy(items.begin(), items.end(), arr_);
  }

  vector(const vector &v) : vector() { operator=(v); }

  vector(vector &&v) noexcept : vector() { operator=(std::move(v)); }

  ~vector() { clear_(); }

  vector &operator=(const vector &v) {
    if (this != &v) {
      clear_();
      size_ = v.size_;
      capacity_ = v.capacity_;
      arr_ = nullptr;
      if (size_ > 0) {
        arr_ = new value_type[capacity_];
        for (size_type i = 0; i < size_; i += 1) {
          arr_[i] = *(v.begin() + i);
        }
      }
    }
    return *this;
  }

  vector &operator=(vector &&v) noexcept {
    if (this != &v) {
      clear_();
      size_ = v.size_;
      capacity_ = v.capacity_;
      arr_ = v.arr_;
      v.arr_ = nullptr;
      v.size_ = 0;
      v.capacity_ = 0;
    }
    return *this;
  }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range(
          "Error: Accessing an inaccessible area of memory");
    }
    return arr_[pos];
  }

  const_reference at(size_type pos) const {
    if (pos >= size_) {
      throw std::out_of_range(
          "Error: Accessing an inaccessible area of memory");
    }
    return arr_[pos];
  }

  inline reference operator[](size_type pos) { return at(pos); }

  inline const_reference operator[](size_type pos) const { return at(pos); }

  const_reference front() const {
    if (empty()) {
      throw std::logic_error("Error: Vector is epmty");
    }
    return arr_[0];
  }

  const_reference back() const {
    if (empty()) {
      throw std::logic_error("Error: Vector is epmty");
    }
    return arr_[size_ - 1];
  }

  inline iterator data() { return &arr_[0]; }

  inline iterator begin() { return &arr_[0]; }

  inline const_iterator begin() const { return &arr_[0]; }

  inline iterator end() { return &arr_[size_]; }

  inline const_iterator end() const { return &arr_[size_]; }

  inline bool empty() const { return begin() == end(); }

  inline size_type size() { return std::distance(begin(), end()); }

  inline size_type max_size() {
    return (std::numeric_limits<size_type>::max() / 2) / sizeof(value_type);
  }

  void reserve(size_type size) {
    if (size > max_size()) {
      throw std::length_error(
          "Error: in reserve(size_type size): size > s21::vector::max_size()");
    }
    if (size > capacity_) {
      value_type *temp = arr_;
      arr_ = new value_type[size];
      for (size_t i = 0; i < size_; i++) {
        arr_[i] = temp[i];
      }
      delete[] temp;
      capacity_ = size;
    }
  }

  void resize(size_type size) {
    if (size > max_size()) {
      throw std::length_error(
          "Error: in reserve(size_type size): size > s21::vector::max_size()");
    }
    if (size > capacity_) {
      reserve(size);
      size_ = size;
    }
    if (size < capacity_) {
      value_type *temp = arr_;
      arr_ = new value_type[capacity_];
      for (size_type i = 0; i < size; i += 1) {
        arr_[i] = temp[i];
      }
      delete[] temp;
      size_ = size;
    }
  }

  size_type capacity() { return capacity_; }

  void shrink_to_fit() {
    capacity_ = size_;
    reserve(capacity_);
  }

  inline void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Index out ot range");
    }
    if (pos == end()) {
      push_back(value);
      return arr_ + size() - 1;
    }
    auto newPosIndex = std::distance(begin(), pos);
    push_back(value_type());
    auto temp = arr_[newPosIndex];
    arr_[newPosIndex] = value;
    for (size_t i = newPosIndex + 1; i < size() - 1; i++) {
      std::swap(temp, arr_[i]);
    }
    arr_[size() - 1] = temp;
    return arr_ + newPosIndex;
  }

  void erase(iterator pos) {
    if (pos < begin() || pos > end()) {
      throw std::length_error(
          "Error: erase(): Accessing an inaccessible area of memory");
    }
    for (size_t i = std::distance(begin(), pos); i + 1 < size(); i++) {
      arr_[i] = arr_[i + 1];
    }
    size_ -= 1;
  }

  void push_back(const_reference value) {
    if (size_ >= capacity_) {
      if (capacity_ == 0) {
        reserve(1);
      } else {
        reserve(capacity_ * 2);
      }
    }
    arr_[size_] = value;
    size_ += 1;
  }

  void pop_back() {
    if (size_ > 0) {
      size_ -= 1;
    }
  }

  void swap(vector &other) {
    std::swap(arr_, other.arr_);
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
  }

  void sort() { std::sort(begin(), end()); }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    if (pos < begin() || pos > end()) {
      throw std::length_error("Index out of range");
    }
    size_type position_index = pos - begin();
    insert_values_at(const_cast<iterator>(pos), std::forward<Args>(args)...);

    return begin() + position_index;
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    insert_values_at(end(), std::forward<Args>(args)...);
  }

 private:
  iterator arr_;
  size_type size_;
  size_type capacity_;

  void clear_() {
    if (arr_ != nullptr) {
      delete[] arr_;
      arr_ = nullptr;
      size_ = 0;
      capacity_ = 0;
    }
  }
  template <typename... Args>
  void insert_values_at(iterator pos, Args &&...args) {
    size_type elements_to_insert = sizeof...(args);
    size_type position_index = pos - begin();

    if (size_ + elements_to_insert > capacity_) {
      size_type new_capacity =
          std::max(capacity_ * 2, size_ + elements_to_insert);
      reserve(new_capacity);
    }
    std::move_backward(begin() + position_index, end(),
                       end() + elements_to_insert);
    iterator current_pos = begin() + position_index;
    ((*(current_pos++) = std::forward<Args>(args)), ...);

    size_ += elements_to_insert;
  }
};
}  // namespace s21

#endif