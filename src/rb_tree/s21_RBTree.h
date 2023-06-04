#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_

#include "s21_RBTree_iterator.h"
#include "s21_RBTree_node.h"

namespace s21 {
template <typename Key>
class RBTree {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using iterator = RBTreeIterator<Key>;
  using cosnt_iterator = RBTreeConstIterator<Key>;

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

  iterator Begin() { return iterator(this, nil_->right_); }

  iterator End() { return iterator(this, nil_); }

  void Insert(const key_type &key) { InsertNode(root_, key, nil_); }

  node_type *Find(const key_type &key) { return FindNode(root_, key); }

  // what if Find(key) == nil_?
  key_type GetValue(const key_type key) { return Find(key)->key_; }

  void Clear() { ClearTree(root_); }

  key_type MaxKey() { return nil_->left_->key_; }

  key_type MinKey() { return nil_->right_->key_; }

  void Delete(key_type key) { DeleteNode(Find(key)); }

  void Print() { PrintTree(root_, ""); }

  void PrintValues() {
    PrintValuesRec(root_);
    std::cout << std::endl;
  }

  node_type *GetNil() const { return nil_; }

 private:
  void PrintValuesRec(node_type *node) {
    if (node == nil_) return;
    PrintValuesRec(node->left_);
    std::cout << node->key_ << " ";
    PrintValuesRec(node->right_);
  }

  void PrintTree(node_type *node, std::string space,
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

  void DeleteNode(node_type *node) {
    if (node == nil_) return;
    if (node->left_ != nil_ && node->right_ != nil_) {
      node_type *max_child = MaxChild(node->left_);
      std::swap(max_child->key_, node->key_);
      DeleteNode(max_child);
    } else if (node->left_ != nil_) {
      DeleteBlackWithOneChild(node, kLeft);
    } else if (node->right_ != nil_) {
      DeleteBlackWithOneChild(node, kRight);
    } else if (node == root_) {
      root_ = nil_;
      delete node;
    } else {
      node_type *parent = node->parent_;
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
    }
  }

  void BalanceAfterDeletion(node_type *parent, bool which_child_was_deleted) {
    node_type *sibling;
    node_type *first_nephew;
    node_type *second_nephew;
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

  void DeleteBlackWithOneChild(node_type *node, bool which_child_has_node) {
    node_type *child =
        (which_child_has_node == kLeft) ? node->left_ : node->right_;
    std::swap(child->key_, node->key_);
    node->left_ = nil_;
    node->right_ = nil_;
    CheckMinMaxDeletion(node, child);
    delete child;
  }

  void CheckMinMaxDeletion(node_type *node, node_type *child) {
    if (nil_->right_ == child)
      nil_->right_ = node;
    else if (nil_->left_ == child)
      nil_->left_ = node;
  }

  // never used
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
    while (node != nil_ && node->key_ != key) {
      if (node->key_ > key)
        node = node->left_;
      else
        node = node->right_;
    }
    return node;
  }

  void InsertNode(node_type *&node, const key_type &key, node_type *parent) {
    if (node == nil_) {
      node = new node_type(key, parent, nil_, nil_);
      CheckMinMaxInsertion(node);
      BalanceTree(node);
    } else if (key < node->key_) {
      InsertNode(node->left_, key, node);
    } else if (key > node->key_) {
      InsertNode(node->right_, key, node);
    }
  }

  void CheckMinMaxInsertion(node_type *node) {
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

  void TurnTree(node_type *node, bool which_side) {
    node_type *child_node;
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
  node_type *const nil_;
  node_type *root_;
  size_t size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_