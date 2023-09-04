#ifndef CPP2_S21_CONTAINERS_MULTISET_H_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_MULTISET_H_S21_MULTISET_H_

#include "../rb_tree/s21_RBTree.h"

namespace s21 {
template <typename Key, typename Compare = std::less<Key> >
class multiset : public RBTree<Key, Compare> {
 public:
  using tree_type = RBTree<Key, Compare>;
  using tree_type::count;
  using tree_type::equal_range;
  using tree_type::find;
  using tree_type::lower_bound;
  using tree_type::RBTree;
  using tree_type::upper_bound;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator = typename tree_type::RBTreeConstIterator;
  using iterator = const_iterator;
  using size_type = size_t;
  using node_type = RBTreeNode<value_type>;
  using node_pointer = RBTreeNode<value_type> *;

  explicit multiset(std::initializer_list<value_type> const &items)
      : tree_type::RBTree() {
    for (const auto &element : items) {
      tree_type::InsertMulti(element);
    }
  }

  iterator insert(const_reference key) {
    return tree_type::InsertMulti(key).first;
  }

 private:
  std::pair<iterator, bool> InsertNode(const_reference key) override {
    return tree_type::InsertMulti(key);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MULTISET_H_S21_MULTISET_H_