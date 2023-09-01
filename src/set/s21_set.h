#ifndef CPP2_S21_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SET_S21_SET_H_

#include "../rb_tree/s21_RBTree.h"

namespace s21 {
template <typename Key, typename Compare = std::less<Key> >
class set : public RBTree<Key> {
 public:
  using RBTree<Key>::RBTree;
  using RBTree<Key>::find;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator = typename RBTree<key_type>::RBTreeConstIterator;
  using iterator = const_iterator;
  using size_type = size_t;

  std::pair<iterator, bool> insert(const_reference key) {
    return RBTree<Key>::InsertUniq(key);
  }
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SET_S21_SET_H_