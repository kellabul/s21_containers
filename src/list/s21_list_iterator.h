#ifndef CPP2_S21_CONTAINERS_S21_LIST_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_LIST_LIST_ITERATOR_H_

#include "s21_list_node.h"

namespace s21 {
template <typename T>
class ListIterator {
 public:
  using value_type = T;
  using node_type = ListNode<T>;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  // using const_iterator = const ListIterator;
  using size_type = unsigned long long;

 public:
  ListIterator() = default;
  ListIterator(node_type *node) : pointed_node_(node) {}
  value_type operator*() { return pointed_node_->value_; }
  bool operator!=(const ListIterator &iterator) {
    return pointed_node_ != iterator.pointed_node_;
  }

  // do we need an exception here?
  iterator operator++() {
    pointed_node_ = pointed_node_->next_;
    return *this;
  }
  iterator operator--() {
    pointed_node_ = pointed_node_->prev_;
    return *this;
  }

  void DeleteNode() {
    pointed_node_->prev_->next_ = pointed_node_->next_;
    pointed_node_->next_->prev_ = pointed_node_->prev_;
    delete pointed_node_;
  }

  iterator AddNode(const_reference value) {
    node_type *new_one = new node_type;
    new_one->value_ = value;
    new_one->next_ = pointed_node_;
    new_one->prev_ = pointed_node_->prev_;
    // there is always some node at pointed_node_->prev_
    pointed_node_->prev_->next_ = new_one;
    pointed_node_->prev_ = new_one;
    return iterator(new_one);
  }

 private:
  node_type *pointed_node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_