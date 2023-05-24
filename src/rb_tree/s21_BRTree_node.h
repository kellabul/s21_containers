#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_NODE_H_

namespace s21 {
template <typename Key>
struct BRTreeNode {
 public:
  using key_type = Key;
  using value_type = T;
  using node_type = BRTreeNode<key_type>;

  // static member is the same for all class objects
  const static bool kRed = true;
  const static bool kBlack = false;

 public:
  BRTreeNode(key_type key = {}, node_type* left = nullptr,
             node_type* right = nullptr, node_type* parent = nullptr,
             bool color = kRed)
      : key_(key), left_(left), right_(right), parent_(parent), color_(color) {}

 public:
  node_type* left_;
  node_type* right_;
  node_type* parent_;
  key_type key_;
  bool color_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_NODE_H_