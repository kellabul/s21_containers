#ifndef CPP2_S21_CONTAINERS_S21_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_LIST_ITERATOR_H_

#include "s21_list_node.h"

namespace s21 {
template <typename T>
class ListIterator {
 public:
  using value_type = T;
  using node_type = ListNode<T>;

 public:
  ListIterator(node_type node) : node_(node) {}
  value_type operator*() { return node_->value_; }
  bool operator!=(const ListIterator &iter) { return node_ != iter.node; }
  void operator++() { node_ = node_->next_; }  // do we need an exception here?
  void operator--() { node_ = node_->prev_; }

 private:
  node_type node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_