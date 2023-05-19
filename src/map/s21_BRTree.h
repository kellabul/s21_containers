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

  void Delete(key_type key) { DeleteNode(root_, key); }

  void Print() {
    PrintTree(root_);
    std::cout << std::endl;
  }

  void PrintTree(node_type *node) {
    if (node == nullptr) return;
    // std::cout << "node: " << node->value_;
    // if (node->left_) std::cout << " left: " << node->left_->value_;
    // if (node->right_) std::cout << " right: " << node->right_->value_;
    // if (node->parent_) std::cout << " parent: " << node->parent_->value_;
    // std::cout << std::endl;
    PrintTree(node->left_);
    std::cout << node->value_ << " ";
    PrintTree(node->right_);
  }

 private:
  void DeleteNode(node_type *&node, key_type &key) {
    if (node == nullptr) return;
    if (key < node->key_) {
      DeleteNode(node->left_, key);
    } else if (key > node->key_) {
      DeleteNode(node->right_, key);
      // here key == node->key_
    } else if (node->left_ != nullptr && node->right_ != nullptr) {
      node_type *tmp = MaxNode(node->left_);
      SwapKeyAndValue(tmp, node);
      DeleteNode(node->left_, tmp->key_);
    } else if (node->left_ != nullptr) {
      node_type *tmp = node;
      node = node->left_;
      node->parent_ = tmp->parent_;
      delete tmp;
    } else if (node->right_ != nullptr) {
      node_type *tmp = node;
      node = node->right_;
      node->parent_ = tmp->parent_;
      delete tmp;
      // here node->right_ == nullptr && node->left_ = nullptr
    } else {
      delete node;
      node = nullptr;
    }
  }

  void SwapKeyAndValue(node_type *first, node_type *second) {
    std::swap(first->key_, second->value_);
    std::swap(first->key_, second->key_);
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

  void InsertNode(node_type *&node, const key_type &key,
                  const value_type &value, node_type *parent) {
    if (node == nullptr) {
      node = new node_type(key, value);
      node->parent_ = parent;
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