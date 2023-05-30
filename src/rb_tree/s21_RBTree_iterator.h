#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_

namespace s21 {
template <typename Key>
class RBTreeIterator {
 public:
  using key_type = Key;
  using node_type = RBTreeNode<key_type>;
  using iterator = RBTreeIterator<Key>;
  
 private:
  node_type *node_pointer_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_S21_RBTree_ITERATOR_H_