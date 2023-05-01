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
  using const_iterator = ListConstIterator<T>;
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
    for (const auto &element : items) {
      push_back(element);
    }
  }

  // 	copy constructor
  list(const list &l) : list() {
    for (const auto &element : l) {
      push_back(element);
    }
  }

  // move constructor
  list(list &&l) : list() { swap(l); }

  ~list() { clear(); }

  // operator=(list &&l)	assignment operator overload for moving object

  // 	access the first element
  const_reference front() const { return tail_->next_->value_; }

  // 	access the last element
  const_reference back() const { return tail_->prev_->value_; }

  // returns an iterator to the beginning
  iterator begin() { return iterator(tail_->next_); }
  const_iterator begin() const { return const_iterator(tail_->next_); }

  // returns an iterator to the end
  iterator end() { return iterator(tail_); }
  const_iterator end() const { return const_iterator(tail_); }

  // checks whether the container is empty
  bool empty() { return (size_ == 0); }

  // 	returns the number of elements
  size_type size() const { return size_; }

  // 	returns the maximum possible number of elements
  size_type max_size() const {
    return (std::numeric_limits<size_type>::max() / (sizeof(node_type) * 2));
  }

  // 	clears the contents
  void clear() {
    for (auto iter = begin(); iter != end(); iter = begin()) {
      erase(iter);
    }
  }

  // inserts elements into concrete pos and returns the iterator that points to
  // the new element
  iterator insert(iterator pos, const_reference value) {
    ++size_;
    return pos.AddNode(value);
  }

  // erases element at pos
  void erase(iterator pos) {
    pos.DeleteNode();
    --size_;
  }

  // adds an element to the end
  void push_back(const_reference value) {
    end().AddNode(value);
    ++size_;
  }

  // removes the last element
  void pop_back() {  // do we need exception here
    erase(--end());
  }

  // 	adds an element to the head
  void push_front(const_reference value) {
    begin().AddNode(value);
    ++size_;
  }
  // 	removes the first element
  void pop_front() { erase(begin()); }

  // 	swaps the contents
  // I don't seek for easy ways.
  void swap(list &other) {
    if (this != &other) {
      SwapTails(tail_, other.tail_);
      SwapTails(other.tail_, tail_);
      std::swap(end_node_, other.end_node_);
      std::swap(size_, other.size_);
    }
  }

  void SwapTails(node_type *first, node_type *second) {
    if (first->next_ == first) {
      first->next_ = first->prev_ = second;
    } else {
      first->next_->prev_ = second;
      first->prev_->next_ = second;
    }
  }

  // 	merges two sorted lists
  // void merge(list &other) {
  //   if (this != &other) {

  //   }
  // }

  // void splice(const_iterator pos, list& other)	transfers elements from
  // list other starting from pos

  // 	reverses the order of the elements
void reverse() {
  auto pointer = tail_;
  do {
    std::swap(pointer->next_, pointer->prev_);
    pointer = pointer->next_;
  } while (pointer != tail_);
}

  // void unique()	removes consecutive duplicate elements

  // void sort() {
    
  // }

  node_type end_node_;
  node_type *tail_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_