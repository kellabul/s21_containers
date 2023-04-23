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
  ListIterator() = default;
  ListIterator(node_type *node) : node_(node) {}
  value_type operator*() { return node_->value_; }
  bool operator!=(const ListIterator &iterator) {
    return node_ != iterator.node_;
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

  void DeleteNode() {
    if (node_->prev_) node_->prev_->next_ = node_->next_;
    if (node_->next_) node_->next_->prev_ = node_->prev_;
    delete node_;
  }

  void AddNode() {
    node_type *new_node = new ListNode(value);
    if (node_->next_) node_->next_->prev_ = node_;
    node_->next_ = new_node;
    new_node->prev_ = node_;
  }

 private:
  node_type *node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_