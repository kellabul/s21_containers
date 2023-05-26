#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_

namespace s21 {
template <typename Key>
struct RBTreeNode {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;

 public:
  RBTreeNode(key_type key = {}, node_type* parent = nullptr,
             node_type* left = nullptr, node_type* right = nullptr,
             bool isRed = true)
      : parent_(parent),
        left_(left),
        right_(right),
        key_(key),
        color_(isRed) {}

 public:
  node_type* parent_;
  node_type* left_;
  node_type* right_;
  key_type key_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_