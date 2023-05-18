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
    InsertNode(root_, key, value, nullptr);
  }

  node_type *Find(const key_type &key) { return FindNode(root_, key); }

  // what if Find(key) == nullptr?
  value_type GetValue(const key_type key) { return Find(key)->value_; }

  void Clear() { ClearTree(root_); }

  key_type MaxKey() { return MaxNode(root_)->key_; }

  key_type MinKey() { return MinNode(root_)->key_; }

  void Delete(key_type key) { DeleteNode(Find(key)); }

  void PrintTree

 private:
  void DeleteNode(node_type *node) {
    if (node == nullptr) return;
    if (node->left_ != nullptr && node->right_ != nullptr) {
      node_type *tmp = MaxNode(node->left_);
      SwapNodes(tmp, node);
      DeleteNode(tmp);
    } else if (node->left_ != nullptr) {
      node.Swap(node->left_);
      delete node->left_;
      node->left_ = nullptr;
    } else if (node->right_ != nullptr) {
      node.Swap(node->left_);
      delete node->left_;
      node->left_ = nullptr;
    } else {
      if (node->parent_ && node->parent_->left_ == node)
        node->parent_->left_ = nullptr;
      else (node->parent_)
        node->parent_->right_ = nullptr;
      delete node;
    }
  }

  void SwapNodes(node_type *node) {
    std::swap(value_, node->value_);
    std::swap(key_, node->key_);
  }

  node_type *MinNode(node_type *node) {
    while (node->left_ != nullptr) node = node->left_;
    return node;
  }

  node_type *MaxNode(node_type *node) {
    while (node->right_ != nullptr) node = node->right_;
    return node;
  }

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

  void InsertNode( node_type *&node, const key_type &key,
                  const value_type &value, node_type *parent) {
    if (node == nullptr) {
      node = new node_type(key, value);
      node->parent_ = parent
    } else if (key < node->key_) {
      InsertNode(node->left_, key, value, node);
    } else {
      InsertNode(node->right_, key, value, node);
    }
  }

 private:
  node_type *root_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_BRTREE_H_