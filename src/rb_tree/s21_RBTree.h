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

    std::cout << "node: " << node->key_ << " [" << node->color_;
    if (node->parent_ != nil_) std::cout << " parent: " << node->parent_->key_;
    if (node->left_ != nil_) std::cout << " left: " << node->left_->key_;
    if (node->right_ != nil_) std::cout << " right: " << node->right_->key_;
    std::cout << std::endl;

    PrintTree(node->left_);
    // std::cout << node->key_ << " ";
    PrintTree(node->right_);
  }

  void LeftTurn(node_type *parent_node, node_type *child_node) {
    // here parent_node->right_ == child_node

    parent_node->right_ = child_node->left_;
    if (child_node->left_ != nil_) child_node->left_->parent_ = parent_node;
    child_node->parent_ = parent_node->parent_;
    if (parent_node->parent_ == nil_)
      root_ = child_node;
    else if (parent_node == parent_node->parent_->left_)
      parent_node->parent_->left_ = child_node;
    else
      parent_node->parent_->right_ = child_node;
    child_node->left_ = parent_node;
    parent_node->parent_ = child_node;

    // node_type *tmp = child_node->left_;
    // child_node->left_ = parent_node;
    // child_node->parent_ = parent_node->parent_;
    // parent_node->parent_ = child_node;
    // parent_node->right_ = tmp;
    // child_node->color_ = parent_node->color_;
    // parent_node->color_ = kRed;
  }
  void RightTurn(node_type *parent_node, node_type *child_node) {
    parent_node->left_ = child_node->right_;
    if (child_node->right_ != nil_) child_node->right_->parent_ = parent_node;
    child_node->parent_ = parent_node->parent_;
    if (parent_node->parent_ == nil_)
      root_ = child_node;
    else if (parent_node == parent_node->parent_->right_)
      parent_node->parent_->right_ = child_node;
    else
      parent_node->parent_->left_ = child_node;
    child_node->right_ = parent_node;
    parent_node->parent_ = child_node;
  }

  // void RightTurn(node_type *parent_node, node_type *child_node) {
  //   // here parent_node->left_ == child_node
  //   node_type *tmp = child_node->right_;
  //   child_node->right_ = parent_node;
  //   child_node->parent_ = parent_node->parent_;
  //   parent_node->parent_ = child_node;
  //   parent_node->left_ = tmp;
  //   child_node->color_ = parent_node->color_;
  //   parent_node->color_ = kRed;
  // }

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
    if (node == nil_) return nil_;
    if (key > node->key_) {
      return FindNode(node->right_, key);
    } else if (key < node->key_) {
      return FindNode(node->left_, key);
    } else {
      return node;
    }
  }

  void InsertNode(node_type *&node, const key_type &key, node_type *parent) {
    if (node == nil_) {
      node = new node_type(key, parent, nil_, nil_);
      BalanceTree(node);
    } else if (key < node->key_) {
      InsertNode(node->left_, key, node);
    } else {
      InsertNode(node->right_, key, node);
    }
  }

  void BalanceTree(node_type *node) {
    while (node->parent_->color_ == kRed) {
      if (node->parent_ == node->parent_->parent_->left_) {
        LeftBalance(node);
      } else {
        RightBalance(node);
      }
    }
    root_->color_ = kBlack;
  }

  void LeftBalance(node_type *&node) {
    node_type *node_uncle = node->parent_->parent_->right_;
    node_type *grandparent = node->parent_->parent_;
    if (node_uncle->color_ == kRed) {
      node->parent_->color_ = kBlack;
      node_uncle->color_ = kBlack;
      grandparent->color_ = kRed;
      node = grandparent;
    } else if (node == node->parent_->right_) {  // uncle is black
      node = node->parent_;
      LeftTurn(node, node->right_);
    } else {  // uncle is black, node is left child
      node->parent_->color_ = kBlack;
      grandparent->color_ = kRed;
      RightTurn(grandparent, node->parent_);
    }
  }

  void RightBalance(node_type *&node) {
    node_type *node_uncle = node->parent_->parent_->left_;
    node_type *grandparent = node->parent_->parent_;
    if (node_uncle->color_ == kRed) {
      node->parent_->color_ = kBlack;
      node_uncle->color_ = kBlack;
      grandparent->color_ = kRed;
      node = grandparent;
    } else if (node == node->parent_->left_) {  // uncle is black
      node = node->parent_;
      RightTurn(node, node->left_);
    } else {  // uncle is black, node is left child
      node->parent_->color_ = kBlack;
      grandparent->color_ = kRed;
      LeftTurn(grandparent, node->parent_);
    }
  }

 private:
  node_type *nil_;
  node_type *root_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_