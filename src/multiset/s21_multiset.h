#ifndef CPP2_S21_CONTAINERS_S21_MULTISET_H_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_S21_MULTISET_H_S21_MULTISET_H_

#include "../rb_tree/s21_RBTree.h"

namespace s21 {
template <typename Key, typename Compare = std::less<Key> >
class multiset : public RBTree<Key> {
 public:
  using RBTree<Key>::RBTree;
  using RBTree<Key>::lower_bound;
  using RBTree<Key>::upper_bound;
  using RBTree<Key>::count;
  using RBTree<Key>::equal_range;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator = typename s21::RBTree<key_type>::RBTreeConstIterator;
  using iterator = const_iterator;
  using size_type = size_t;
  using node_type = RBTreeNode<key_type>;
  using node_pointer = RBTreeNode<key_type> *;

  explicit multiset(std::initializer_list<key_type> const &items)
      : RBTree<Key>::RBTree() {
    for (const auto &element : items) {
      RBTree<key_type>::InsertMulti(element);
    }
  }

  iterator insert(const_reference key) {
    return RBTree<key_type>::InsertMulti(key).first;
  }

 private:
  std::pair<iterator, bool> InsertNode(const_reference key) override {
    return RBTree<Key>::InsertMulti(key);
  };
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MULTISET_H_S21_MULTISET_H_