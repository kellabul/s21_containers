#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_

#include <iostream>
#include <string>

#include "s21_RBTree_node.h"

namespace s21 {
template <typename Key>
class RBTree {
  class RBTreeIterator;
  class RBTreeConstIterator;

 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;
  using iterator = RBTreeIterator;
  using const_iterator = RBTreeConstIterator;

  const bool kRed = true;
  const bool kBlack = false;
  const bool kLeft = true;
  const bool kRight = false;

 public:
  RBTree()
      : nil_{new node_type{nullptr, nullptr, nullptr, key_type{}, kBlack}},
        root_(),
        size_(0U) {
    AssignRootToNil();
  }

  RBTree(const RBTree &other) : RBTree() {
    ImportElements(other.root_, other.nil_);
  }

  RBTree &operator=(RBTree &other) {
    if (this == &other) return *this;
    clear();
    ImportElements(other.root_, other.nil_);
    return *this;
  }

  ~RBTree() {
    clear();
    delete nil_;
    nil_ = nullptr;
  }

  RBTree(std::initializer_list<key_type> const &items) : RBTree() {
    for (auto &element : items) {
      insert(element);
    }
  }

  iterator begin() { return iterator(nil_, nil_->right_); }

  iterator end() { return iterator(nil_, nil_); }

  const_iterator begin() const { return const_iterator(nil_, nil_->right_); }

  const_iterator end() const { return const_iterator(nil_, nil_); }

  void insert(const key_type &key) { InsertNode(root_, key, nil_); }

  node_pointer Find(const key_type &key) { return FindNode(root_, key); }

  // what if Find(key) == nil_?
  key_type GetValue(const key_type key) { return Find(key)->key_; }

  void clear() {
    ClearTree(root_);
    AssignRootToNil();
    size_ = 0U;
  }

  key_type MaxKey() { return nil_->left_->key_; }

  key_type MinKey() { return nil_->right_->key_; }

  void Delete(key_type key) { DeleteNode(Find(key)); }

  void Print() { PrintTree(root_, ""); }

  void PrintValues() {
    PrintValuesRec(root_);
    std::cout << std::endl;
  }

  node_pointer GetNil() const { return root_; }

  size_t size() { return size_; }

  bool empty() { return size_ == 0; }

 private:
  void AssignRootToNil() {
    root_ = nil_;
    nil_->left_ = nil_;
    nil_->right_ = nil_;
  }

  void ImportElements(node_pointer const &other_node,
                      node_pointer const &other_nil) {
    if (other_node == other_nil) return;
    insert(other_node->key_);
    ImportElements(other_node->left_, other_nil);
    ImportElements(other_node->right_, other_nil);
  }

  void PrintValuesRec(node_pointer node) {
    if (node == nil_) return;
    PrintValuesRec(node->left_);
    std::cout << node->key_ << " ";
    PrintValuesRec(node->right_);
  }

  void PrintTree(node_pointer node, std::string space,
                 bool which_child_is_node = true) {
    if (node == nil_) {
      // std::cout << space << "[ nil_ ]" << std::endl;
      return;
    }
    std::cout << space
              // << "[" << (which_child_is_node == kRight ? "<" : ">") << "]"
              << "[ " << node->key_ << " ]"
              << "(" << (node->color_ ? "+" : "-") << ")" << std::endl;
    std::string arrow = "   └————— ";
    std::string blank =
        (which_child_is_node == kRight) ? "   │      " : "          ";
    size_t start_pos = space.find(arrow);
    if (start_pos != std::string::npos)
      space.replace(start_pos, arrow.size(), blank);
    space += arrow;
    PrintTree(node->right_, space, kRight);
    PrintTree(node->left_, space, kLeft);
    // std::cout << node->key_ << " ";
  }

  void DeleteNode(node_pointer node) {
    if (node == nil_) return;
    if (node->left_ != nil_ && node->right_ != nil_) {
      node_pointer max_child = MaxChild(node->left_);
      std::swap(max_child->key_, node->key_);
      DeleteNode(max_child);
    } else if (node->left_ != nil_) {
      DeleteBlackWithOneChild(node, kLeft);
    } else if (node->right_ != nil_) {
      DeleteBlackWithOneChild(node, kRight);
    } else if (node == root_) {
      AssignRootToNil();
      delete node;
    } else {
      node_pointer parent = node->parent_;
      bool which_child_is_node;
      if (node == parent->left_) {
        parent->left_ = nil_;
        which_child_is_node = kLeft;
      } else {
        parent->right_ = nil_;
        which_child_is_node = kRight;
      }
      CheckMinMaxDeletion(parent, node);
      if (node->color_ == kBlack)
        BalanceAfterDeletion(parent, which_child_is_node);
      delete node;
      size_--;
    }
  }

  void BalanceAfterDeletion(node_pointer parent, bool which_child_was_deleted) {
    node_pointer sibling;
    node_pointer first_nephew;
    node_pointer second_nephew;
    bool direction_to_turn;
    if (which_child_was_deleted == kRight) {
      sibling = parent->left_;
      first_nephew = sibling->left_;
      second_nephew = sibling->right_;
      direction_to_turn = kRight;
    } else {
      sibling = parent->right_;
      first_nephew = sibling->right_;
      second_nephew = sibling->left_;
      direction_to_turn = kLeft;
    }
    if (sibling->color_ == kBlack) {
      if (first_nephew->color_ == kRed) {
        sibling->color_ = parent->color_;
        first_nephew->color_ = kBlack;
        parent->color_ = kBlack;
        TurnTree(parent, direction_to_turn);
      } else if (second_nephew->color_ == kRed) {
        sibling->color_ = kRed;
        second_nephew->color_ = kBlack;
        TurnTree(sibling, !direction_to_turn);
        BalanceAfterDeletion(parent, which_child_was_deleted);
      } else {  // first_nephew->color_ == kBlack && second_nephew->color_ ==
                // kBlack
        sibling->color_ = kRed;
        if (parent->color_ == kRed || parent == root_) {
          parent->color_ = kBlack;
        } else {
          which_child_was_deleted =
              (parent->parent_->left_ == parent) ? kLeft : kRight;
          BalanceAfterDeletion(parent->parent_, which_child_was_deleted);
        }
      }
    } else {  // sibling.color_ == kRed
      parent->color_ = kRed;
      sibling->color_ = kBlack;
      TurnTree(parent, direction_to_turn);
      BalanceAfterDeletion(parent, which_child_was_deleted);
    }
  }

  void DeleteBlackWithOneChild(node_pointer node, bool which_child_has_node) {
    node_pointer child =
        (which_child_has_node == kLeft) ? node->left_ : node->right_;
    std::swap(child->key_, node->key_);
    node->left_ = nil_;
    node->right_ = nil_;
    CheckMinMaxDeletion(node, child);
    delete child;
  }

  void CheckMinMaxDeletion(node_pointer node, node_pointer child) {
    if (nil_->right_ == child)
      nil_->right_ = node;
    else if (nil_->left_ == child)
      nil_->left_ = node;
  }

  // never used
  node_pointer MinChild(node_pointer node) {
    while (node->left_ != nil_) node = node->left_;
    return node;
  }

  node_pointer MaxChild(node_pointer node) {
    while (node->right_ != nil_) node = node->right_;
    return node;
  }

  void ClearTree(node_pointer node) {
    if (node == nil_) return;
    ClearTree(node->left_);
    ClearTree(node->right_);
    delete node;
  }

  node_pointer FindNode(node_pointer node, const key_type &key) {
    while (node != nil_ && node->key_ != key) {
      if (node->key_ > key)
        node = node->left_;
      else
        node = node->right_;
    }
    return node;
  }

  void InsertNode(node_pointer &node, const key_type &key,
                  node_pointer parent) {
    if (node == nil_) {
      node = new node_type{parent, nil_, nil_, key, kRed};
      CheckMinMaxInsertion(node);
      BalanceTree(node);
      size_++;
    } else if (key < node->key_) {
      InsertNode(node->left_, key, node);
    } else if (key > node->key_) {
      InsertNode(node->right_, key, node);
    }
  }

  void CheckMinMaxInsertion(node_pointer node) {
    if (node == root_) {
      nil_->left_ = node;
      nil_->right_ = node;
    } else if (node->key_ > nil_->left_->key_) {
      nil_->left_ = node;
    } else if (node->key_ < nil_->right_->key_) {
      nil_->right_ = node;
    }
  }

  void BalanceTree(node_pointer node) {
    while (node->parent_->color_ == kRed) {
      node_pointer grandparent = node->parent_->parent_;
      node_pointer node_uncle;
      bool direction_to_turn;
      bool node_makes_zigzag;
      if (node->parent_ == node->parent_->parent_->left_) {
        node_uncle = node->parent_->parent_->right_;
        direction_to_turn = kLeft;
        node_makes_zigzag = (node == node->parent_->right_);
      } else {
        node_uncle = node->parent_->parent_->left_;
        direction_to_turn = kRight;
        node_makes_zigzag = (node == node->parent_->left_);
      }
      if (node_uncle->color_ == kRed) {
        node->parent_->color_ = kBlack;
        node_uncle->color_ = kBlack;
        grandparent->color_ = kRed;
        node = grandparent;
      } else if (node_makes_zigzag) {  // uncle is black, node makes zigzag with
                                       // his parent and grandparent
        node = node->parent_;
        TurnTree(node, direction_to_turn);
      } else {  // uncle is black, node makes a line with his parent and
                // grandparent
        node->parent_->color_ = kBlack;
        grandparent->color_ = kRed;
        TurnTree(grandparent, !direction_to_turn);
      }
    }
    root_->color_ = kBlack;
  }

  void TurnTree(node_pointer node, bool which_side) {
    node_pointer child_node;
    if (which_side == kLeft) {
      child_node = node->right_;
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
  // nil_->left_ points to max value, nil->right_ points to min value because of
  // iterator logic;
  // nil_->parent_ can't be used anywhere because of  TurnTree
  node_pointer nil_;
  node_pointer root_;
  size_t size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_