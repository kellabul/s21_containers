#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_

#include "s21_RBTree_node.h"

namespace s21 {
template <typename Key>
class RBTree {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;

  const bool kRed = true;
  const bool kBlack = false;

 public:
  RBTree()
      : nil_{new node_type{key_type{}, nullptr, nullptr, nullptr, kBlack}},
        root_(nil_) {
    nil_->parent_ = nil_;
    nil_->right_ = nil_;
    nil_->left_ = nil_;
  }

  ~RBTree() {
    Clear();
    delete nil_;
  }

  void Insert(const key_type &key) { InsertNode(root_, key, nil_); }

  node_type *Find(const key_type &key) { return FindNode(root_, key); }

  // what if Find(key) == nullptr?
  key_type GetValue(const key_type key) { return Find(key)->key_; }

  void Clear() { ClearTree(root_); }

  key_type MaxKey() { return MaxNode(root_)->key_; }

  key_type MinKey() { return MinNode(root_)->key_; }

  void Delete(key_type key) { DeleteNode(root_, key); }

  void Print() {
    PrintTree(root_);
    std::cout << std::endl;
  }

  void PrintTree(node_type *node) {
    if (node == nil_) return;
    std::cout << "node: " << node->key_;
    if (node->parent_ != nil_)
      std::cout << " parent: " << node->parent_->key_ << " ["
                << node->parent_->color_;
    if (node->left_ != nil_)
      std::cout << " left: " << node->left_->key_ << " ["
                << node->left_->color_;
    if (node->right_ != nil_)
      std::cout << " right: " << node->right_->key_ << " ["
                << node->right_->color_;
    std::cout << std::endl;
    PrintTree(node->left_);
    // std::cout << node->key_ << " ";
    PrintTree(node->right_);
  }

  void LeftTurn(node_type *&parent_node, node_type *&child_node) {
    // here parent_node->right_ == child_node
    node_type *tmp = child_node->left_;
    child_node->left_ = parent_node;
    child_node->parent_ = parent_node->parent_;
    parent_node->parent_ = child_node;
    parent_node->right_ = tmp;
    child_node->color_ = parent_node->color_;
    parent_node->color_ = kRed;
  }

  void RightTurn(node_type *&parent_node, node_type *&child_node) {
    // here parent_node->left_ == child_node
    node_type *tmp = child_node->right_;
    child_node->right_ = parent_node;
    child_node->parent_ = parent_node->parent_;
    parent_node->parent_ = child_node;
    parent_node->left_ = tmp;
    child_node->color_ = parent_node->color_;
    parent_node->color_ = kRed;
  }

  void ColorSwap(node_type *parent_node) {
      parent_node->color_ = kRed;
      parent_node->left.color_ = kBlack;
      parent_node->right.color_ = kBlack;
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
    if (node == nil_) return;
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

  void InsertNode(node_type *&node, const key_type &key, node_type *&parent) {
    if (node == nil_) {
      node = new node_type(key, parent, nil_, nil_);
      if (parent->color_ == kRed || node == root_) BalanceTree(parent);
    } else if (key < node->key_) {
      InsertNode(node->left_, key, node);
    } else {
      InsertNode(node->right_, key, node);
    }
  }

  void BalanceTree(node_type *&node){
    if (node->parent_->right_ == kRed && node->parent_->left_ == kRed) {
      ColorSwap(node->parent_);
      BalanceTree(node->parent_);
    }

    root_->color_ = kBlack;
  }



 private:
  node_type *nil_;
  node_type *root_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_