#ifndef CPP2_S21_CONTAINERS_RBTREE_S21_RBTREE_ITERATOR_H_
#define CPP2_S21_CONTAINERS_RBTREE_S21_RBTREE_ITERATOR_H_

namespace s21 {
template <typename Key, typename Compare>
class RBTree<Key, Compare>::RBTreeIterator {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = RBTreeIterator;
  using const_iterator = RBTreeConstIterator;
  using size_type = size_t;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;
  using const_node_pointer = const RBTreeNode<key_type> *;

 public:
  RBTreeIterator() : nil_(nullptr), node_(nullptr) {}

  explicit RBTreeIterator(node_pointer nil, node_pointer node)
      : nil_(nil), node_(node) {}

  reference operator*() { return *(node_->key_); }

  bool operator==(const iterator &other) const noexcept {
    return node_ == other.node_;
  }

  bool operator!=(const iterator &other) const noexcept {
    return !(*this == other);
  }

  bool operator==(const const_iterator &other) const noexcept {
    return node_ == other.get_node_pointer();
  }

  bool operator!=(const const_iterator &other) const noexcept {
    return !(*this == other);
  }

  iterator &operator++() {
    RBTreeIncrement();
    return *this;
  }

  iterator &operator--() {
    RBTreeDecrement();
    return *this;
  }

  iterator operator++(int) {
    iterator tmp{*this};
    RBTreeIncrement();
    return tmp;
  }
  iterator operator--(int) {
    iterator tmp{*this};
    RBTreeDecrement();
    return tmp;
  }

  node_pointer get_node_pointer() const { return node_; }

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
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = RBTreeIterator;
  using const_iterator = RBTreeConstIterator;
  using size_type = size_t;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;
  using const_node_pointer = const RBTreeNode<key_type> *;

 public:
  RBTreeConstIterator() : nil_(nullptr), node_(nullptr) {}

  explicit RBTreeConstIterator(const_node_pointer nil, const_node_pointer node)
      : nil_(nil), node_(node) {}

  const_reference operator*() const noexcept { return *(node_->key_); }

  bool operator==(const const_iterator &other) const noexcept {
    return node_ == other.node_;
  }

  bool operator!=(const const_iterator &other) const noexcept {
    return node_ != other.node_;
  }

  bool operator==(const iterator &other) const noexcept {
    return node_ == other.get_node_pointer();
  }

  bool operator!=(const iterator &other) const noexcept {
    return !(*this == other);
  }

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

  const_node_pointer get_node_pointer() const { return node_; }

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
  const_node_pointer nil_;
  const_node_pointer node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_RBTREE_S21_RBTREE_ITERATOR_H_