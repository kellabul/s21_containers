#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_H_

#include "s21_BRTree_node.h"

namespace s21 {
template <typename Key, typename T>
class BRTree {
 public:
  using key_type = Key;
  using value_type = T;
  using node_type = BRTreeNode<key_type, value_type>;
  const bool kRed = true;
  const bool kBlack = false;

 public:
  BRTree() : root_(nullptr){};

  BRTree(key_type key, value_type value) : root_(new node_type(key, value)){};

  ~BRTree() { Clear(); }

  void Insert(const key_type &key, const value_type &value) {
    InsertNode(root_, key, value);
  }

  node_type *Find(const key_type &key) { return FindNode(root_, key); }

  value_type GetValue(const key_type key) { return Find(key)->value_; }

  void Clear() { ClearTree(root_); }

 private:
  void ClearTree(node_type *node) {
    if (node == nullptr) return;
    ClearTree(node->left_);
    ClearTree(node->right_);
    delete node;
  }

  node_type *FindNode(node_type *node, const key_type &key) {
    if (node == nullptr) return nullptr;
    if (node->key_ == key) return node;
    if (key < node->key_) {
      return FindNode(node->left_, key);
    } else {
      return FindNode(node->right_, key);
    }
  }

  void InsertNode(node_type *&node, const key_type &key,
                  const value_type &value) {
    if (node == nullptr) {
      node = new node_type(key, value);
    } else if (key < node->key_) {
      InsertNode(node->left_, key, value);
    } else {
      InsertNode(node->right_, key, value);
    }
  }

 private:
  node_type *root_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_H_