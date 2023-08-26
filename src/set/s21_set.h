#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_SET_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_SET_H_

#include "../rb_tree/s21_RBTree.h"

namespace s21 {
template <typename Key, typename Compare = std::less<Key> >
class set : public RBTree<Key> {
 public:
  using RBTree<Key>::RBTree;
  using key_type = Key;
  using value_type = Key;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<key_type>::RBTreeIterator;
  using const_iterator = typename RBTree<key_type>::RBTreeConstIterator;
  using size_type = size_t;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_SET_H_