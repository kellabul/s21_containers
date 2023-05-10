#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_H_

#include <limits>

#include "s21_map_iterator.h"
#include "s21_map_node.h"

namespace s21 {
template <typename T>
class map {
 public:
  using value_type = T;
  // key_type	Key the first template parameter (Key)

  // mapped_type	T the second template parameter (T)

  // value_type	std::pair<const key_type,mapped_type> Key-value pair

  // reference	value_type & defines the type of the reference to an element

  // const_reference	const value_type & defines the type of the constant
  // reference

  // iterator	internal class MapIterator<K, T> or BinaryTree::iterator as
  // internal iterator of tree subclass; defines the type for iterating through
  // the container

  // const_iterator	internal class MapConstIterator<K, T> or
  // BinaryTree::const_iterator as internal const iterator of tree subclass;
  // defines the constant type for iterating through the container

  // size_type	size_t defines the type of the container size (standard type is
  // size_t)

  // map()	default constructor, creates an empty map

  // map(std::initializer_list<value_type> const &items)	initializer list
  // constructor, creates the map initizialized using std::initializer_list

  // map(const map &m)	copy constructor

  // map(map &&m)	move constructor

  // ~map()	destructor

  // operator=(map &&m)	assignment operator overload for moving an object

  // T& at(const Key& key)	access a specified element with bounds checking

  // T& operator[](const Key& key)	access or insert specified element

  // iterator begin()	returns an iterator to the beginning

  // iterator end()	returns an iterator to the end

  // bool empty()	checks whether the container is empty

  // size_type size()	returns the number of elements

  // size_type max_size()	returns the maximum possible number of elements

  // void clear()	clears the contents

  // std::pair<iterator, bool> insert(const value_type& value)	inserts a node
  // and returns an iterator to where the element is in the container and bool
  // denoting whether the insertion took place

  // std::pair<iterator, bool> insert(const Key& key, const T& obj)	inserts a
  // value by key and returns an iterator to where the element is in the
  // container and bool denoting whether the insertion took place

  // std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);
  // inserts an element or assigns to the current element if the key already
  // exists

  // void erase(iterator pos)	erases an element at pos

  // void swap(map& other)	swaps the contents

  // void merge(map& other);	splices nodes from another container

  // Lookup	Definition

  // bool contains(const Key& key)	checks if there is an element with key
  // equivalent to key in the container

 public:
 private:
  node_type end_node_;
  node_type *tail_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_H_