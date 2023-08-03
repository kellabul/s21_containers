#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_ITERATOR_H_

#include "s21_map_node.h"

namespace s21 {
template <typename T>
class MapIterator {
 public:
  using value_type = T;
  using node_type = MapNode<T>;
  using reference = T &;
  using const_reference = const T &;
  using iterator = MapIterator<T>;
  using size_type = unsigned long long;

 public:
 private:
  node_type *node_pointer_;
};

template <typename T>
class MapConstIterator {
 public:
  using value_type = T;
  using node_type = MapNode<T>;
  using const_reference = const T &;
  using const_iterator = MapConstIterator<T>;
  using iterator = MapIterator<T>;
  using size_type = unsigned long long;

 public:
 private:
  const node_type *node_pointer_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_