#ifndef CPP2_S21_CONTAINERS_S21_LIST_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_LIST_H_

#include <limits>

#include "s21_list_iterator.h"
#include "s21_list_node.h"

namespace s21 {
template <typename T>
class list {
 public:
  using value_type = T;
  using node_type = ListNode<T>;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator<T>;
  // using const_iterator = const ListIterator;
  using size_type = unsigned long long;

 public:
  list() : end_node_(), tail_(&end_node_), size_(0U) {
    tail_->next_ = tail_;
    tail_->prev_ = tail_;
  }

  // list(size_type n)	parameterized constructor, creates the list of size n
  explicit list(size_type n) : list() {
    while (n--) push_back(value_type());
  }
  // 	initializer list
  list(std::initializer_list<value_type> const &items) : list() {
    for (const auto &unit : items) {
      push_back(unit);
    }
  }

  // constructor, creates list initizialized using std::initializer_list

  // list(const list &l)	copy constructor

  // list(list &&l)	move constructor

  ~list() {
    for (auto iter = begin(); iter != end(); iter = begin()) {
      erase(iter);
    }
  }

  // operator=(list &&l)	assignment operator overload for moving object

  // const_reference front()	access the first element

  // const_reference back()	access the last element

  // returns an iterator to the beginning
  iterator begin() { return iterator(tail_->next_); }
  // returns an iterator to the end
  iterator end() { return iterator(tail_); }

  // bool empty()	checks whether the container is empty
  // 	returns the number of elements
  size_type size() const { return size_; }

  // 	returns the maximum possible number of elements
  // size_type max_size() const {return
  // std::numeric_limits<difference_type>::max(); }
  // void clear()	clears the contents

  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    ++size_;
    return pos.AddNode(value);
    ;
  }

  // void erase(iterator pos)	erases element at pos

  void erase(iterator pos) {
    --size_;
    pos.DeleteNode();
  }

  // adds an element to the end
  void push_back(const_reference value) {
    end().AddNode(value);
    ++size_;
  }

  // removes the last element
  void pop_back() {  // do we need exception here
    erase(end());
  }

  // 	adds an element to the head
  void push_front(const_reference value) {
    begin().AddNode(value);
    ++size_;
  }
  // 	removes the first element
  void pop_front() { erase(begin()); }
  // void swap(list& other)	swaps the contents

  // void merge(list& other)	merges two sorted lists

  // void splice(const_iterator pos, list& other)	transfers elements from
  // list other starting from pos

  // void reverse()	reverses the order of the elements

  // void unique()	removes consecutive duplicate elements

  // void sort()

  node_type end_node_;
  node_type *tail_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_