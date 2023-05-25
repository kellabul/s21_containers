#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_

#include "s21_RBTree_node.h"

namespace s21 {
template <typename Key>
class RBTree {
 public:
  using key_type = Key;
  using value_type = T;
  using node_type = RBTreeNode<key_type, value_type>;

  const bool kRed = true;
  const bool kBlack = false;
  const node_type kNill{value_type{}, kBlack};

 public:
  RBTree() : root_(nullptr){};

  RBTree(key_type key) : root_(new node_type(key)){};

  ~RBTree() { Clear(); }

  void Insert(const key_type &key, const value_type &value) {
    InsertNode(root_, key, nullptr);
  }

  node_type *Find(const key_type &key) { return FindNode(root_, key); }

  // what if Find(key) == nullptr?
  value_type GetValue(const key_type key) { return Find(key); }

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
    // std::cout << "node: " << node->key_;
    // if (node->left_) std::cout << " left: " << node->left_->key_;
    // if (node->right_) std::cout << " right: " << node->right_->key_;
    // if (node->parent_) std::cout << " parent: " << node->parent_->key_;
    // std::cout << std::endl;
    PrintTree(node->left_);
    std::cout << node->key_ << " ";
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
      std::swap(tmp.key, node.key);
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
    if (key > node->key_) {
      return FindNode(node->right_, key);
    } else if (key < node->key_) {
      return FindNode(node->left_, key);
    } else {
      return node;
    }
  }

  void InsertNode(node_type *&node, const key_type &key, node_type *parent) {
    if (node == nullptr) {
      node = new node_type(key);
      node->parent_ = parent;
    } else if (key < node->key_) {
      InsertNode(node->left_, key, node);
    } else {
      InsertNode(node->right_, key, node);
    }
  }

 private:
  node_type *root_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_