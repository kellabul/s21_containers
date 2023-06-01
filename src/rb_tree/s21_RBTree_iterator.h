#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_

#include "s21_RBTree.h"
#include "s21_RBTree_node.h"

namespace s21 {
class RBTreeIterator {
 public:
//  template <typename Tey>
//   class RBTree;
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using iterator = RBTreeIterator;
  using tree_type = RBTree<key_type>;

 public:
  RBTreeIterator(){};
  explicit RBTreeIterator(tree_type *tree)
      : nil_(tree->GetNil()), node_(tree->GetNil()->right) {}

  key_type operator*() const noexcept { return node_->value_; }

  iterator &operator++() noexcept {
    if (node_->right_ != nil_ || node_ == nil_->left_) {
      node_ = node_->right_;
      while (node_->left_ != nil_) {
        node_ = node_->left_;
      }
    } else {
      node_type *tmp = node_->parent_;
      while (tmp != nil_ && node_ == tmp->right_) {
        node_ = tmp;
        tmp = tmp->parent_;
      }
      node_ = tmp;
    }
    return *this;
  }

 private:
  node_type *const nil_;
  node_type *node_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_