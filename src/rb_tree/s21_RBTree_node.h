#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_

namespace s21 {
template <typename Key>
struct RBTreeNode {
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;

  node_type* parent_;
  node_type* left_;
  node_type* right_;
  key_type key_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_