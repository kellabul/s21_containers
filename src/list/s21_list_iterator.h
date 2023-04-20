#ifndef CPP2_S21_CONTAINERS_S21_LIST_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_LIST_LIST_ITERATOR_H_

#include "s21_list_node.h"

namespace s21 {
template <typename T>
class ListIterator {
 public:
  using value_type = T;
  using node_type = ListNode<T>;
  using iterator = ListIterator;

 public:
  ListIterator(node_type *node) : node_(node) {}
  value_type operator*() { return node_->value(); }
  bool operator!=(const ListIterator &iterator) {
    return node_ != iterator.node;
  }

   // do we need an exception here?
  iterator operator++() {
    node_ = node_->next_;
    return *this;
  } 
  iterator operator--() {
    node_ = node_->prev_;
    return *this;
  }

 private:
  node_type *node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_