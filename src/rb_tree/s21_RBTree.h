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

  // what if Find(key) == nil_?
  key_type GetValue(const key_type key) { return Find(key)->key_; }

  void Clear() { ClearTree(root_); }

  key_type MaxKey() { return nil_->left_->key_; }

  key_type MinKey() { return nil_->right_->key_; }

  void Delete(key_type key) { DeleteNode(Find(key)); }

  void Print() { PrintTree(root_, ""); }

  void PrintTree(node_type *node, std::string space,
                 bool which_child_is_node = true) {
    if (node == nil_) {
      // std::cout << space << "[ nil_ ]" << std::endl;
      return;
    }
    std::cout << space << "[ " << node->key_ << " ]"
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

  void PrintValues() {
    PrintValuesRec(root_);
    std::cout << std::endl;
  }

  void PrintValuesRec(node_type *node) {
    if (node == nil_) return;
    PrintValuesRec(node->left_);
    std::cout << node->key_ << " ";
    PrintValuesRec(node->right_);
  }

 private:
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
      nil_->left_ = nil_;
      nil_->right_ = nil_;
      delete node;
    } else {
      node_type *parent = node->parent_;
      bool node_is_black = (node->color_ == kBlack);
      bool which_child_is_node;
      if (node == parent->left_) {
        parent->left_ = nil_;
        which_child_is_node = kLeft;
      } else {
        parent->right_ = nil_;
        which_child_is_node = kRight;
      }
      CheckMinMaxDeletion(parent, node);
      delete node;
      if (node_is_black) BalanceAfterDeletion(parent, which_child_is_node);
    }
  }

  void BalanceAfterDeletion(node_type *parent, bool which_child_was_deleted) {
    node_type *other_child;
    node_type *first_grandchild;
    node_type *second_grandchild;
    node_type *grandgrandchild;
    bool direction_to_turn;
    if (which_child_was_deleted == kRight) {
      other_child = parent->left_;
      first_grandchild = other_child->left_;
      second_grandchild = other_child->right_;
      grandgrandchild = second_grandchild->left_;
      direction_to_turn = kRight;
    } else {
      other_child = parent->right_;
      first_grandchild = other_child->right_;
      second_grandchild = other_child->left_;
      grandgrandchild = second_grandchild->right_;
      direction_to_turn = kLeft;
    }
    if (parent->color_ == kRed) {  // other_child->color_ == kBlack
      std::cout << 1 << std::endl;
      parent->color_ = kBlack;
      other_child->color_ = kRed;
      if (first_grandchild->color_ == kRed) {
        std::cout << 2 << std::endl;
        first_grandchild->color_ = kBlack;
        TurnTreeBranches(parent, direction_to_turn);
      }
    } else {  // parent->color_ == kBlack
      if (other_child->color_ == kRed) {
        if (second_grandchild != nil_ &&
            second_grandchild->left_->color_ == kBlack &&
            second_grandchild->right_->color_ == kBlack) {
          std::cout << 3 << std::endl;
          other_child->color_ = kBlack;
          second_grandchild->color_ = kRed;
          TurnTreeBranches(parent, direction_to_turn);
        } else if (second_grandchild != nil_ &&
                   grandgrandchild->color_ == kRed) {
          std::cout << 4 << std::endl;
          second_grandchild->color_ = kBlack;
          TurnTreeBranches(other_child, !direction_to_turn);
          TurnTreeBranches(parent, direction_to_turn);
        }
      } else {  // parent->color_ == kBlack, other_child->color_ == kBlack
        if (second_grandchild->color_ == kRed) {
          std::cout << 5 << std::endl;
          second_grandchild->color_ = kBlack;
          TurnTreeBranches(other_child, !direction_to_turn);
          TurnTreeBranches(parent, direction_to_turn);
        } else if (first_grandchild->color_ ==
                   kRed) {  // this part wasn't in istructions
          std::cout << 6 << std::endl;
          first_grandchild->color_ = kBlack;
          TurnTreeBranches(parent, direction_to_turn);
        } else {
          std::cout << 7 << std::endl;
          other_child->color_ = kRed;
          if (parent == parent->parent_->left_) {
            which_child_was_deleted = kLeft;
          } else {
            which_child_was_deleted = kRight;
          }
          BalanceAfterDeletion(parent->parent_, which_child_was_deleted);
        }
      }
    }
  }

  void CheckMinMaxDeletion(node_type *node) {
    if (node == nil_->right_)
      nil_->right_ = MinChild(root_);
    else if (node == nil_->left_)
      nil_->left_ = MaxChild(root_);
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

  // node_type *FindNode(node_type *node, const key_type &key) {
  //   if (node == nil_) return nil_;
  //   if (key > node->key_) {
  //     return FindNode(node->right_, key);
  //   } else if (key < node->key_) {
  //     return FindNode(node->left_, key);
  //   } else {
  //     return node;
  //   }
  // }

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
      bool direction_for_turn;
      bool node_makes_zigzag;
      if (node->parent_ == node->parent_->parent_->left_) {
        node_uncle = node->parent_->parent_->right_;
        direction_for_turn = kLeft;
        node_makes_zigzag = (node == node->parent_->right_);
      } else {
        node_uncle = node->parent_->parent_->left_;
        direction_for_turn = kRight;
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
        TurnTreeBranches(node, direction_for_turn);
      } else {  // uncle is black, node makes a line with his parent and
                // grandparent
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
  // nil_->parent_ can't be used anywhere because of  TurnTreeBranches
  node_type *nil_;
  node_type *root_;
  size_t size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_H_