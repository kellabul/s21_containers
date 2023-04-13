#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

namespace s21 {

template <typename T>
class list {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;

  // iterator	internal class ListIterator<T> defines the type for iterating
  // through the container

  // const_iterator	internal class ListConstIterator<T> defines the constant
  // type for iterating through the container

  using size_type = std::size_t;

 public:
  list() : node_(new node_type()), size_(0) {}
  // list(size_type n)	parameterized constructor, creates the list of size n
  explicit list(size_type n) : head_
  // list(std::initializer_list<value_type> const &items)	initializer list
  
  // constructor, creates list initizialized using std::initializer_list

  // list(const list &l)	copy constructor

  // list(list &&l)	move constructor

  // ~list()	destructor

  // operator=(list &&l)	assignment operator overload for moving object

  // const_reference front()	access the first element

  // const_reference back()	access the last element

  // iterator begin()	returns an iterator to the beginning
  // iterator end()	returns an iterator to the end

  // bool empty()	checks whether the container is empty
  // size_type size()	returns the number of elements
  // size_type max_size()	returns the maximum possible number of elements

  // void clear()	clears the contents

  // iterator insert(iterator pos, const_reference value)	inserts elements
  // into concrete pos and returns the iterator that points to the new element

  // void erase(iterator pos)	erases element at pos

  // void push_back(const_reference value)	adds an element to the end

  // void pop_back()	removes the last element

  // void push_front(const_reference value)	adds an element to the head

  // void pop_front()	removes the first element

  // void swap(list& other)	swaps the contents

  // void merge(list& other)	merges two sorted lists

  // void splice(const_iterator pos, list& other)	transfers elements from list
  // other starting from pos

  // void reverse()	reverses the order of the elements

  // void unique()	removes consecutive duplicate elements

  // void sort()

 private:
  struct NodeList {
    NodeList() = default;
    explicit ListNode(const value_type value) : value_(value) {}
    value_type value_ = 0;
    NodeList *prev_ = nullptr;
    NodeList *next_ = nullptr;
  };

  NodeList node_;
  size_type size_ = 0;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_