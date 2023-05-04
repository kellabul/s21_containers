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
  using size_type = unsigned long long;

 public:
  ListIterator() = delete;
  explicit ListIterator(node_type *node) : node_pointer_(node) {}
  reference operator*() { return node_pointer_->value_; }

  bool operator!=(const iterator &iterator) const {
    return node_pointer_ != iterator.node_pointer_;
  }
  bool operator==(const iterator &iterator) const {
    return node_pointer_ == iterator.node_pointer_;
  }

  // do we need an exception here?
  iterator &operator++() {
    node_pointer_ = node_pointer_->next_;
    return *this;
  }

  iterator &operator--() {
    node_pointer_ = node_pointer_->prev_;
    return *this;
  }

  void DeleteNode() {
    node_pointer_->prev_->next_ = node_pointer_->next_;
    node_pointer_->next_->prev_ = node_pointer_->prev_;
    delete node_pointer_;
  }

  iterator AddNode(const_reference value) {
    node_type *new_one = new node_type;
    new_one->value_ = value;
    new_one->next_ = node_pointer_;
    new_one->prev_ = node_pointer_->prev_;
    // there is always some node at node_pointer_->prev_
    node_pointer_->prev_->next_ = new_one;
    node_pointer_->prev_ = new_one;
    return iterator(new_one);
  }

  void BindNode(const iterator &iter) {
    node_pointer_->next_ = iter.node_pointer_;
    iter.node_pointer_->prev_ = node_pointer_;
  }

  node_type *get_node_pointer() const { return node_pointer_; }

 private:
  node_type *node_pointer_;
};

template <typename T>
class ListConstIterator {
 public:
  using value_type = T;
  using node_type = ListNode<T>;
  using const_reference = const T &;
  using const_iterator = ListConstIterator<T>;
  using iterator = ListIterator<T>;
  using size_type = unsigned long long;

 public:
  ListConstIterator() = delete;
  explicit ListConstIterator(const node_type *node) : node_pointer_(node) {}
  ListConstIterator(const iterator &iter)
      : node_pointer_(iter.get_node_pointer()) {}

  const_reference operator*() { return node_pointer_->value_; }
  bool operator!=(const const_iterator &iter) {
    return node_pointer_ != iter.node_pointer_;
  }
  bool operator==(const const_iterator &iter) {
    return node_pointer_ == iter.node_pointer_;
  }

  // do we need an exception here?
  const_iterator &operator++() {
    node_pointer_ = node_pointer_->next_;
    return *this;
  }

  const_iterator &operator--() {
    node_pointer_ = node_pointer_->prev_;
    return *this;
  }

  operator iterator() const {
    return iterator(const_cast<node_type *>(node_pointer_));
  }

 private:
  const node_type *node_pointer_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_