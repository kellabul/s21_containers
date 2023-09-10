#ifndef CPP2_S21_CONTAINERS_MAP_H_S21_MAP_H_
#define CPP2_S21_CONTAINERS_MAP_H_S21_MAP_H_

#include "../rb_tree/s21_RBTree.h"
#include "s21_pair.h"

namespace s21 {
template <typename Key, typename T,
          typename Compare = std::less<s21::pair<const Key, T>>>
class map : public RBTree<s21::pair<const Key, T>, Compare> {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = s21::pair<const key_type, mapped_type>;
  using std_type = std::pair<const key_type, mapped_type>;
  using tree_type = RBTree<value_type, Compare>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using const_std_reference = const std_type &;
  using const_iterator = typename tree_type::RBTreeConstIterator;
  using iterator = typename tree_type::RBTreeIterator;
  using size_type = size_t;
  using node_type = RBTreeNode<value_type>;
  using node_pointer = RBTreeNode<value_type> *;
  using tree_type::begin;
  using tree_type::end;
  using tree_type::RBTree;

  map(std::initializer_list<value_type> const &items) : tree_type::RBTree() {
    for (const auto &element : items) {
      insert(element);
    }
  }

  map(const_std_reference key) : tree_type::RBTree() {
      tree_type::InsertMapPair(key);
  }


  std::pair<iterator, bool> insert(const_reference key) {
    return tree_type::InsertMapPair(key);
  }

  std::pair<iterator, bool> insert(const_std_reference key) {
    return tree_type::InsertMapPair(key);
  }

  std::pair<iterator, bool> insert(const Key &key, const T &obj) {
    return tree_type::InsertMapPair(value_type{key, obj});
  }

  mapped_type &operator[](const Key &key) {
    auto mapped = insert(key, mapped_type{});
    return (*mapped.first).second;
  }

  iterator begin() { return tree_type::NonConstBegin(); }

  iterator end() { return tree_type::NonConstEnd(); }

  mapped_type &at(const Key &key) {
    auto node = tree_type::FindNode(value_type(key, mapped_type{}));
    if (node == tree_type::GetNil()) throw std::out_of_range("No such key");
    return node->key_->second;
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj) {
    auto iter_and_status = tree_type::InsertMapPair(value_type{key, obj});
    (*iter_and_status.first).second = obj;
    return iter_and_status;
  }

  bool contains(const Key &key) const {
    return tree_type::contains(value_type(key, mapped_type{}));
  }
};

// overloading for print()
template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const s21::pair<const Key, T> &p) {
  return os << "[" << p.first << "] = " << p.second << "";
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_H_S21_MAP_H_
