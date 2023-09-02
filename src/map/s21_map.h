#ifndef CPP2_S21_CONTAINERS_MAP_H_S21_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_H_S21_MAP_H_

#include "../rb_tree/s21_RBTree.h"

namespace s21 {

template <typename T>
struct LessMap {
  bool operator()(const T &x, const T &y) const { return x.first < y.first; }
};

template <typename Key, typename T,
          typename Compare = LessMap<std::pair<const Key, T>>>
class map : public RBTree<std::pair<const Key, T>, Compare> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using tree_type = RBTree<value_type, Compare>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_iterator = typename tree_type::RBTreeConstIterator;
  using iterator = const_iterator;
  using size_type = size_t;
  using node_type = RBTreeNode<value_type>;
  using node_pointer = RBTreeNode<value_type> *;
  using tree_type::RBTree;

  explicit map(std::initializer_list<value_type> const &items)
      : tree_type::RBTree() {
    for (const auto &element : items) {
      tree_type::InsertMapPair(element);
    }
  }

  iterator insert(const_reference key) {
    return tree_type::InsertMapPair(key).first;
  }

 private:
  std::pair<iterator, bool> InsertNode(const_reference key) override {
    return tree_type::InsertMapPair(key);
  }

  // access a specified element with bounds checking
  // mapped_type& at(const Key& key);

  // std::pair<iterator, bool> insert(const Key& key, const T& obj) {
  //   return insert(std::make_pair(key, obj));
  // }

  // mapped_type& operator[](const Key& key) {
  //   auto mapped = insert(key, mapped_type{});
  //   return mapped.first.second;
  // }

  // std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

  // std::pair<iterator, bool> InsertNode(const_reference key) override {
  //   return RBTree<Key>::InsertMulti(key);
  // }
};

// overloading for print()
template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const std::pair<Key, T> &p) {
  return os << "[" << p.first << "] = " << p.second << "";
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_H_S21_MAP_H_
