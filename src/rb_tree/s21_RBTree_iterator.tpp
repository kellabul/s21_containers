#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_

#include "s21_RBTree.h"

namespace s21 {
template <typename Key, typename Compare>
class RBTree<Key, Compare>::RBTreeIterator {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;
  using iterator = RBTreeIterator;
  using rbtree = RBTree<Key, Compare>;

 public:
  RBTreeIterator() = delete;

  explicit RBTreeIterator(node_pointer nil, node_pointer node)
      : nil_(nil), node_(node) {}

  key_type operator*() const noexcept { return node_->key_; }

  bool operator==(const iterator &other) const noexcept {
    return node_ == other.node_;
  }

  bool operator!=(const iterator &other) const noexcept {
    return !(*this == other);
  }

  iterator &operator++() noexcept {
    RBTreeIncrement();
    return *this;
  }

  iterator &operator--() noexcept {
    RBTreeDecrement();
    return *this;
  }

  iterator operator++(int) noexcept {
    iterator tmp{*this};
    RBTreeIncrement();
    return tmp;
  }
  iterator operator--(int) noexcept {
    iterator tmp{*this};
    RBTreeDecrement();
    return tmp;
  }

  node_pointer get_node() const { return node_; }

 private:
  void RBTreeIncrement() {
    if (node_->right_ != nil_) {
      node_ = node_->right_;
      while (node_->left_ != nil_) {
        node_ = node_->left_;
      }
      // nil_->left_ always points to max element
    } else if (node_ == nil_->left_) {
      node_ = nil_;
    } else {
      node_pointer tmp = node_->parent_;
      while (node_ == tmp->right_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
  }

  void RBTreeDecrement() {
    if (node_->left_ != nil_) {
      node_ = node_->left_;
      while (node_->right_ != nil_) {
        node_ = node_->right_;
      }
      // nil_->right_ always points to min element
    } else if (node_ == nil_->right_) {
      node_ = nil_;
    } else {
      node_pointer tmp = node_->parent_;
      while (node_ == tmp->left_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
  }

 private:
  node_pointer nil_;
  node_pointer node_;
};

template <typename Key, typename Compare>
class RBTree<Key, Compare>::RBTreeConstIterator {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;
  using const_iterator = RBTreeConstIterator;
  using rbtree = RBTree<Key, Compare>;

 public:
  RBTreeConstIterator() = delete;

  explicit RBTreeConstIterator(node_pointer nil, node_pointer node)
      : nil_(nil), node_(node) {}

  key_type operator*() const noexcept { return node_->key_; }

  bool operator==(const const_iterator &other) const noexcept {
    return node_ == other.node_;
  }

  bool operator!=(const const_iterator &other) const noexcept {
    return node_ != other.node_;
  }

  void SetBegin() { node_ = nil_->right_; }
  void SetEnd() { node_ = nil_; }

  const_iterator &operator++() noexcept {
    RBTreeIncrement();
    return *this;
  }
  const_iterator &operator--() noexcept {
    RBTreeDecrement();
    return *this;
  }

  const_iterator operator++(int) noexcept {
    const_iterator tmp{*this};
    RBTreeIncrement();
    return tmp;
  }
  const_iterator operator--(int) noexcept {
    const_iterator tmp{*this};
    RBTreeDecrement();
    return tmp;
  }

  node_pointer get_node() const { return node_; }

 private:
  void RBTreeIncrement() {
    if (node_->right_ != nil_) {
      node_ = node_->right_;
      while (node_->left_ != nil_) {
        node_ = node_->left_;
      }
      // nil_->left_ always points to max element
    } else if (node_ == nil_->left_) {
      node_ = nil_;
    } else {
      node_pointer tmp = node_->parent_;
      while (node_ == tmp->right_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
  }

  void RBTreeDecrement() {
    if (node_->left_ != nil_) {
      node_ = node_->left_;
      while (node_->right_ != nil_) {
        node_ = node_->right_;
      }
      // nil_->right_ always points to min element
    } else if (node_ == nil_->right_) {
      node_ = nil_;
    } else {
      node_pointer tmp = node_->parent_;
      while (node_ == tmp->left_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
  }

 private:
  node_type const *const nil_;
  node_type const *node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_