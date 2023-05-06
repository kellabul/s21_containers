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
  list() : end_node_(), tail_(&end_node_), size_(0U) { BindTailToItself(); }

  void BindTailToItself() {
    tail_->next_ = tail_;
    tail_->prev_ = tail_;
  }

  // list(size_type n)	parameterized constructor, creates the list of size n
  explicit list(size_type n) : list() {
    while (n--) push_back(value_type());
  }
  // 	initializer list
  explicit list(std::initializer_list<value_type> const &items) : list() {
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

  // assignment operator overload for moving object
  list &operator=(list &&l) {
    if (this != &l) {
      swap(l);
      l.clear();
    }
    return *this;
  }

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

  iterator EraseAndGoBack(iterator pos) {
    iterator buffer = pos;
    --buffer;
    erase(pos);
    return buffer;
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
  void merge(list &other) {
    if (this != &other) {
      splice(begin(), other);
      sort();
    }
  }

  // transfers elements from list other starting from pos
  void splice(const_iterator pos, list &other) { SpliceNonConst(pos, other); }

  void SpliceNonConst(iterator pos, list &other) {
    if (!other.empty()) {
      auto next_pos = pos;
      ++next_pos;
      pos.BindNode(other.begin());
      (--other.end()).BindNode(next_pos);
      size_ += other.size_;
      other.size_ = 0;
      other.BindTailToItself();
    }
  }

  // 	reverses the order of the elements
  void reverse() {
    auto pointer = tail_;
    do {
      std::swap(pointer->next_, pointer->prev_);
      pointer = pointer->next_;
    } while (pointer != tail_);
  }

  // 	removes consecutive duplicate elements
  void unique() {
    auto iter = begin();
    while (iter != end()) {
      if (*iter == *(++iter)) {
        iter = EraseAndGoBack(iter);
      }
    }
  }

  // merge sort
  void sort() {
    if (size_ > 1) {
      // MergeSort returns pointer to the first element in sorted element
      tail_->next_ = MergeSort(tail_->next_);
      // seek to the last element in the sorted array
      node_type *max_node = tail_->next_;
      while (max_node->next_ != tail_) max_node = max_node->next_;
      // and attach it to the tail, so list will be looped
      tail_->prev_ = max_node;
    }
  }

  node_type *MergeSort(node_type *begin) {
    // if there is no elements or one element, return pointer to it's begin
    if (begin == tail_ || begin->next_ == tail_) return begin;
    // find the middle
    node_type *middle = DevideIntoTwoParts(begin);
    // devide each until there is only one element
    begin = MergeSort(begin);
    middle = MergeSort(middle);
    // then sort and merge those two elements (if there only one element in
    // every half, it means that those arrays are sorted) and then every other
    // half will be sorted
    return MergeSortedArrays(begin, middle);
  }

  node_type *MergeSortedArrays(node_type *first, node_type *second) {
    // if there is no elements in one of the half, return other half
    if (first == tail_) return second;
    if (second == tail_) return first;

    if (first->value_ < second->value_) {
      // at last MergeSortedArrays will yeild part of second array with every
      //  element bigger than (or equal to) the biggest element of first array
      first->next_ = MergeSortedArrays(first->next_, second);
      // attach current node to that part
      first->next_->prev_ = first;
      // attach smallest element to tail_
      first->prev_ = tail_;
      // return smallest element with element of two halfs attachend to it
      return first;
    } else {
      // same logic if second value is smaller or equal to first value
      second->next_ = MergeSortedArrays(first, second->next_);
      second->next_->prev_ = second;
      second->prev_ = tail_;
      return second;
    }
  }

  // go to the middle of the list and attach that node to the tail_
  // return address of the middle + 1 node (start of the second half)
  node_type *DevideIntoTwoParts(node_type *begin) {
    node_type *fast_pointer = begin;
    node_type *slow_pointer = begin;
    while (fast_pointer->next_ != tail_ &&
           fast_pointer->next_->next_ != tail_) {
      fast_pointer = fast_pointer->next_->next_;
      slow_pointer = slow_pointer->next_;
    }
    node_type *tmp = slow_pointer->next_;
    slow_pointer->next_ = tail_;
    return tmp;
  }

 private:
  node_type end_node_;
  node_type *tail_;
  size_type size_;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_