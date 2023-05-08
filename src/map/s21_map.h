#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_

#include <limits>

#include "s21_map_iterator.h"
#include "s21_map_node.h"

namespace s21 {
template <typename T>
class map {
 public:
  using value_type = T;
  using node_type = MapNode<T>;
  using reference = T &;
  using const_reference = const T &;
  using iterator = MapIterator<T>;
  using const_iterator = MapConstIterator<T>;
  using size_type = unsigned long long;

 public:
 

 private:
  node_type end_node_;
  node_type *tail_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_