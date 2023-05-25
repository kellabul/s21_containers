#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_

namespace s21 {
template <typename Key>
struct RBTreeNode {
 public:
  using key_type = Key;
  using value_type = T;
  using node_type = RBTreeNode<key_type>;

 public:
  RBTreeNode(key_type key = {}, bool isRed = true)
      : left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        key_(key),
        color_(isRed) {}

 public:
  node_type* left_;
  node_type* right_;
  node_type* parent_;
  key_type key_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_