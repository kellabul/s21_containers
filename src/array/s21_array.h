#ifndef CPP2_S21_CONTAINERS_ARRAY_S21_ARRAY_H_
#define CPP2_S21_CONTAINERS_ARRAY_S21_ARRAY_H_

#include <limits>

namespace s21 {
template <typename T, std::size_t Size>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

 public:
  array() = default;
  ~array() = default;

  array(std::initializer_list<value_type> const &items) : array() {
    if (items.size() > Size) {
      throw std::out_of_range("too many items in initializer list");
    }
    size_type i = 0;
    for (const auto &element : items) {
      arr_[i] = element;
      ++i;
    }
  }

  array(const array &other) {
    for (size_type i = 0; i < Size; ++i) {
      arr_[i] = other.arr_[i];
    }
  }

  array(array &&other)  noexcept {
    if (this != &other) {
      for (size_type i = 0; i < Size; ++i) {
        arr_[i] = std::move(other.arr_[i]);
      }
    }
  }

  array &operator=(const array &other) {
    array tmp(other);
    swap(tmp);
    return *this;
  }

  array &operator=(array &&other)  noexcept {
    array tmp(std::move(other));
    swap(tmp);
    return *this;
  }

  constexpr reference at(size_type pos) {
    if (pos >= Size) {
      throw std::out_of_range("index is out of range");
    }
    return arr_[pos];
  }

  constexpr reference operator[](size_type pos) { return arr_[pos]; }

  constexpr const_reference operator[](size_type pos) const { return arr_[pos]; }

  constexpr const_reference front() const { return arr_[0]; };

  constexpr const_reference back() const { return arr_[Size - 1]; }

  constexpr iterator data() noexcept { return arr_; };

  constexpr iterator begin() noexcept { return arr_; };

  constexpr iterator end() noexcept {
    if (empty()) return arr_;
    return arr_ + Size;
  };

  bool empty() const noexcept { return Size == 0U; };

  constexpr size_type size() const noexcept { return Size; };

  constexpr size_type max_size() const noexcept { return Size; };

  constexpr void swap(array &other) noexcept { std::swap(arr_, other.arr_); }

  constexpr void fill(const_reference value) {
    for (auto &elem : arr_) {
      elem = value;
    }
  }

 private:
  value_type arr_[Size]{};
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_ARRAY_S21_ARRAY_H_
