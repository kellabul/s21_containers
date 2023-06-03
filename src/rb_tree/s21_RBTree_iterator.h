#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_

#include "s21_RBTree.h"
#include "s21_RBTree_node.h"

namespace s21 {
template <typename T>
class RBTree;

template <typename Key>
class RBTreeIterator {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using iterator = RBTreeIterator<key_type>;
  using rbtree = RBTree<key_type>;

 public:
  RBTreeIterator() = delete;

  explicit RBTreeIterator(rbtree *tree, node_type *node)
      : nil_(tree->GetNil()), node_(node) {}

  template <typename U>
  explicit RBTreeIterator(const RBTreeIterator<U> &other)
      : nil_(other.nil_), node_(other.node_) {}

  template <typename U>
  explicit RBTreeIterator(const RBTreeIterator<U> &&other)
      : nil_(other.nil_), node_(other.node_) {}

  iterator &operator=(const iterator &other) {
    if (this == &other) return *this;
    if (nil_ != other.nil_)
      throw std::logic_error("can't assign iterator from different objects");
    node_ = other.node_;
    return *this;
  }

  iterator &operator=(const iterator &&other) {
    if (this == &other) return *this;
    if (nil_ != other.nil_)
      throw std::logic_error("can't assign iterator from different objects");
    node_ = std::move(other.node_);
    return *this;
  }

  ~RBTreeIterator(){};

  key_type operator*() const noexcept { return node_->key_; }

  bool operator==(const iterator &other) const noexcept {
    return node_ == other.node_;
  }

  bool operator!=(const iterator &other) const noexcept {
    return node_ != other.node_;
  }

  void SetBegin() { node_ = nil_->right_; }
  void SetEnd() { node_ = nil_; }

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
      node_type *tmp = node_->parent_;
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
      node_type *tmp = node_->parent_;
      while (node_ == tmp->left_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
  }

 private:
  node_type *const nil_;
  node_type *node_;
};

template <typename Key>
class RBTreeConstIterator {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using const_iterator = RBTreeConstIterator<key_type>;
  using rbtree = RBTree<key_type>;

 public:
  RBTreeConstIterator() = delete;

  explicit RBTreeConstIterator(rbtree *tree, node_type *node)
      : nil_(tree->GetNil()), node_(node) {}

  template <typename U>
  explicit RBTreeConstIterator(const RBTreeConstIterator<U> &iter)
      : nil_(iter.nil_), node_(iter.node_) {}

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
      node_type *tmp = node_->parent_;
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
      node_type *tmp = node_->parent_;
      while (node_ == tmp->left_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
  }

 private:
  node_type *const nil_;
  node_type const *node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_