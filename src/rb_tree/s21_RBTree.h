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
  const bool kLeft = true;
  const bool kRight = false;

 public:
  RBTree()
      : nil_{new node_type{key_type{}, nullptr, nullptr, nullptr, kBlack}},
        root_(nil_) {
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

  key_type MaxKey() { return nil_->left_->key_; }

  key_type MinKey() { return nil_->right_->key_; }

  void Delete(key_type key) { DeleteNode(root_, key); }

  void Print() { PrintTree(root_, ""); }

  void PrintTree(node_type *node, std::string space,
                 bool is_which_child = true) {
    if (node == nil_) return;
    std::cout << space << "[ " << node->key_ << " ]"
              << "(" << (node->color_ ? "+" : "-") << ")" << std::endl;
    std::string arrow = "   └————— ";
    std::string blank = (is_which_child == kLeft) ? "   │      " : "          ";
    size_t start_pos = space.find(arrow);
    if (start_pos != std::string::npos)
      space.replace(start_pos, arrow.size(), blank);
    space += arrow;
    PrintTree(node->left_, space, kLeft);
    // std::cout << node->key_ << " ";
    PrintTree(node->right_, space, kRight);
  }

 private:
  void DeleteNode(node_type *node, const key_type &key) {
    if (node == nil_) return;
    if (key < node->key_) {
      DeleteNode(node->left_, key);
    } else if (key > node->key_) {
      DeleteNode(node->right_, key);
      // here key == node->key_
    } else if (node->left_ != nil_ && node->right_ != nil_) {
      node_type *max_child = MaxChild(node->left_);
      std::swap(max_child->key, node->key);
      DeleteNode(node->left_, max_child->key_);
    } else if (node->left_ != nil_) {
      DeleteBlackWithOneChild(node, kLeft);
    } else if (node->right_ != nil_) {
      DeleteBlackWithOneChild(node, kRight);
    } else {
      bool node_is_black = (node->color_ == kBlack);
      node_type *parent = node->parent_;
      if (node == parent->left_)
        parent->left_ = nil_;
      else
        parent->right_ = nil_;
      delete node;
      if (node_is_black) BalanceAfterDeletionBlackWithNoChlidren(parent);
    }
  }

  void BalanceAfterDeletionBlackWithNoChlidren(node_type *parent) {}

  void DeleteBlackWithOneChild(node_type *node, bool is_which_child) {
    node_type *child = (is_which_child == kLeft) ? node->left_ : node->right_;
    std::swap(child->key_, node->key_);
    delete child;
    node->left_ = nil_;
    node->right_ = nil_;
  }

  node_type *MinChild(node_type *node) {
    while (node->left_ != nil_) node = node->left_;
    return node;
  }

  node_type *MaxChild(node_type *node) {
    while (node->right_ != nil_) node = node->right_;
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
      CheckMinMax(node);
      BalanceTree(node);
    } else if (key < node->key_) {
      InsertNode(node->left_, key, node);
    } else if (key > node->key_) {
      InsertNode(node->right_, key, node);
    }
  }

  void CheckMinMax(node_type *node) {
    if (node == root_) {
      nil_->left_ = node;
      nil_->right_ = node;
    } else if (node->key_ > nil_->left_->key_) {
      nil_->left_ = node;
    } else if (node->key_ < nil_->right_->key_) {
      nil_->right_ = node;
    }
  }

  void BalanceTree(node_type *node) {
    while (node->parent_->color_ == kRed) {
      node_type *grandparent = node->parent_->parent_;
      node_type *node_uncle;
      bool direction_for_turn;
      bool node_makes_a_line;
      if (node->parent_ == node->parent_->parent_->left_) {
        node_uncle = node->parent_->parent_->right_;
        direction_for_turn = kLeft;
        node_makes_a_line = (node == node->parent_->right_);
      } else {
        node_uncle = node->parent_->parent_->left_;
        direction_for_turn = kRight;
        node_makes_a_line = (node == node->parent_->left_);
      }
      if (node_uncle->color_ == kRed) {
        node->parent_->color_ = kBlack;
        node_uncle->color_ = kBlack;
        grandparent->color_ = kRed;
        node = grandparent;
      } else if (node_makes_a_line) {  // uncle is black
        node = node->parent_;
        TurnTreeBranches(node, direction_for_turn);
      } else {
        node->parent_->color_ = kBlack;
        grandparent->color_ = kRed;
        TurnTreeBranches(grandparent, !direction_for_turn);
      }
    }
    root_->color_ = kBlack;
  }

  void TurnTreeBranches(node_type *node, bool which_side) {
    node_type *child_node;
    if (which_side == kLeft) {
      child_node = node->right_;
      node->right_ = node->left_;
      node->right_ = child_node->left_;
      child_node->left_->parent_ = node;
      child_node->left_ = node;
      child_node->parent_ = node->parent_;
    } else {
      child_node = node->left_;
      node->left_ = child_node->right_;
      child_node->right_->parent_ = node;
      child_node->right_ = node;
      child_node->parent_ = node->parent_;
    }
    if (node == root_) {
      root_ = child_node;
    } else if (node == node->parent_->left_) {
      node->parent_->left_ = child_node;
    } else {
      node->parent_->right_ = child_node;
    }
    node->parent_ = child_node;
  }

 private:
  // nil_->left_ points to max value, nil->right_ pints to min value
  // nil_->parent_ can't be used anywhere because of TurnTreeBranches
  node_type *nil_;
  node_type *root_;
  size_t size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_