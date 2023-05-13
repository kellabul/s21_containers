#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_NODE_H_

namespace s21 {
template <typename Key, typename T>
class BRTreeNode {
 public:
  using key_type = Key;
  using value_type = T;
  using node_type = BRTreeNode;
  const bool kRed = true;
  const bool kBlack = false;

 public:
  BRTree(key_type key = {}, value_type value = {})
      : key_(key),
        value_(value_),
        left_(nullptr),
        right_(nullptr),
        parent_(nullptr),
        color_(kRed) {}

 private:
  key_type key_;
  value_type value_;
  node_type* left_;
  node_type* right_;
  node_type* parent_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_NODE_H_