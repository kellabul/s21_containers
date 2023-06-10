#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_

namespace s21 {
template <typename Key>
struct RBTreeNode {
  using key_type = Key;
  using node_pointer = RBTreeNode<key_type>*;

  node_pointer parent_;
  node_pointer left_;
  node_pointer right_;
  key_type key_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_NODE_H_