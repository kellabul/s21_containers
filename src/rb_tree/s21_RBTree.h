#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTREE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTREE_H_

#include <cstring>
#include <iostream>
#include <vector>

#include "s21_RBTree_node.h"

namespace s21 {

template <typename Key, typename Compare = std::less<Key>>
class RBTree {
 public:
  class RBTreeConstIterator;

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator = RBTreeConstIterator;
  using iterator = const_iterator;
  using size_type = size_t;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;

  const static bool kRed = true;
  const static bool kBlack = false;
  const static bool kLeft = true;
  const static bool kRight = false;

 public:
  RBTree()
      : nil_{new node_type{nullptr, nullptr, nullptr, key_type{}, kBlack}},
        root_{},
        size_{0U} {
    AssignRootToNil();
  }

  explicit RBTree(std::initializer_list<key_type> const &items) : RBTree() {
    for (const auto &element : items) {
      insert(element);
    }
  }

  RBTree(const RBTree &other) : RBTree() {
    ImportElements(other.root_, other.nil_);
  }

  RBTree(RBTree &&other)
      : nil_(other.nil_), root_(other.root_), size_(other.size_) {
    other.root_ = nullptr;
    other.nil_ = nullptr;
    other.size_ = 0U;
  }

  ~RBTree() {
    ClearTree(root_);
    size_ = 0U;
    delete nil_;
    root_ = nullptr;
    nil_ = nullptr;
  }

  RBTree &operator=(const RBTree &other) {
    if (this == &other) return *this;
    RBTree tmp(other);
    swap(tmp);
    return *this;
  }

  RBTree &operator=(RBTree &&other) {
    swap(other);
    return *this;
  }

  const_iterator begin() const { return const_iterator(nil_, nil_->right_); }

  const_iterator end() const { return const_iterator(nil_, nil_); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  // TODO check again
  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() - sizeof(node_type) -
            sizeof(bool) * 4) /
           2 / sizeof(node_type);
  };

  void clear() {
    ClearTree(root_);
    AssignRootToNil();
    size_ = 0U;
  }

  std::pair<iterator, bool> insert(const_reference key) {
    node_pointer node = root_;
    node_pointer parent = nil_;
    while (node != nil_ && node->key_ != key) {
      parent = node;
      if (compare_(key, node->key_))
        node = node->left_;
      else
        node = node->right_;
    }
    if (node == nil_) {
      node = new node_type{parent, nil_, nil_, key, kRed};
      CheckParent(node, parent);
      CheckMinMaxInsertion(node);
      BalanceTree(node);
      ++size_;
      return std::make_pair(iterator(nil_, node), true);
    }
    return std::make_pair(iterator(nil_, node), false);
  }

  iterator find(const_reference key) const {
    node_pointer node = root_;
    while (node != nil_ && node->key_ != key) {
      if (compare_(key, node->key_))
        node = node->left_;
      else
        node = node->right_;
    }
    return iterator(nil_, node);
  }

  bool contains(const_reference key) const { return find(key) != end(); }

  void print() { PrintTree(root_, ""); }

  void print_values() {
    PrintValuesRec(root_);
    std::cout << std::endl;
  }
  void swap(RBTree &other) {
    if (this == &other) return;
    std::swap(root_, other.root_);
    std::swap(nil_, other.nil_);
    std::swap(size_, other.size_);
  }

  void merge(const RBTree &other) { ImportElements(other.root_, other.nil_); }

  void erase(iterator pos) { DeleteNode(const_cast<node_pointer>(pos.get_node_pointer())); }

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    // std::vector<std::pair<iterator, bool>> result;
    std::vector result{insert(args)...};
    return result;
  }

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
    size_type start_pos = space.find(arrow);
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
      --size_;
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
      --size_;
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
    --size_;
  }

  void CheckMinMaxDeletion(node_pointer node, const node_pointer child) {
    if (nil_->right_ == child)
      nil_->right_ = node;
    else if (nil_->left_ == child)
      nil_->left_ = node;
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

  void CheckParent(const node_pointer node, node_pointer parent) {
    if (parent == nil_) {
      root_ = node;
    } else if (compare_(parent->key_, node->key_)) {
      parent->right_ = node;
    } else {
      parent->left_ = node;
    }
  }

  void CheckMinMaxInsertion(node_pointer node) {
    if (node == root_) {
      nil_->left_ = node;
      nil_->right_ = node;
    } else if (compare_(nil_->left_->key_, node->key_)) {
      nil_->left_ = node;
    } else if (compare_(node->key_, nil_->right_->key_)) {
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
      } else if (node_makes_zigzag) {
        // uncle is black, node makes zigzag with
        // his parent and grandparent
        node = node->parent_;
        TurnTree(node, direction_to_turn);
      } else {
        // uncle is black, node makes a line with his parent and
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
  Compare compare_{};
  node_pointer nil_;
  node_pointer root_;
  size_type size_;
};
}  // namespace s21

#include "s21_RBTree_iterator.tpp"

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTREE_H_