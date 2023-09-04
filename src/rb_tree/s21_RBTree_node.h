#ifndef CPP2_S21_CONTAINERS_RBTREE_S21_RBTREE_NODE_H_
#define CPP2_S21_CONTAINERS_RBTREE_S21_RBTREE_NODE_H_

namespace s21 {
template <typename Key>
class RBTreeNode {
 public:
  using key_type = Key;

  using node_pointer = RBTreeNode<key_type> *;

  RBTreeNode() = delete;

  RBTreeNode(node_pointer parent, node_pointer left, node_pointer right,
             key_type key, bool color)
      : parent_(parent),
        left_(left),
        right_(right),
        key_(new key_type(key)),
        color_(color) {}

  RBTreeNode(const RBTreeNode &other)
      : parent_(other.parent),
        left_(other.left),
        right_(other.right),
        key_(new key_type(other.key)),
        color_(other.color) {}

  RBTreeNode(RBTreeNode &&other)
      : parent_(other.parent),
        left_(other.left),
        right_(other.right),
        key_(other.key),
        color_(other.color) {
    other.key_ = nullptr;
  }

  RBTreeNode operator=(const RBTreeNode &other) {
    RBTreeNode temp(other);
    std::swap(temp, *this);
    return *this;
  }

  RBTreeNode operator=(RBTreeNode &&other) {
    parent_ = other.parent_;
    left_ = other.left_;
    right_ = other.right_;
    key_ = other.key_;
    color_ = other.color_;
    other.key_ = nullptr;
    return *this;
  }

  ~RBTreeNode() {
    delete key_;
    key_ = nullptr;
  }

  node_pointer parent_;
  node_pointer left_;
  node_pointer right_;
  key_type *key_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_RBTREE_S21_RBTREE_NODE_H_