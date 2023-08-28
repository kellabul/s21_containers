#ifndef CPP2_S21_CONTAINERS_S21_LIST_LIST_ITERATOR_H_
#define CPP2_S21_CONTAINERS_S21_LIST_LIST_ITERATOR_H_

namespace s21 {
template <typename T>
class list<T>::ListIterator {
 public:
  using value_type = T;
  using node_type = ListNode<T>;
  using node_pointer = ListNode<T> *;
  using const_node_pointer = const ListNode<T> *;
  using reference = T &;
  using const_reference = const T &;
  using iterator = ListIterator;
  using const_iterator = ListConstIterator;

 public:
  ListIterator() : node_pointer_(nullptr){};

  explicit ListIterator(node_pointer node) : node_pointer_(node) {}

  operator ListConstIterator() const {
    return ListConstIterator(const_cast<node_pointer>(node_pointer_));
  }

  reference operator*() { return node_pointer_->value_; }

  bool operator==(const iterator &iterator) const {
    return node_pointer_ == iterator.node_pointer_;
  }

  bool operator!=(const iterator &iterator) const {
    return !(*this == iterator);
  }

  iterator &operator++() {
    node_pointer_ = node_pointer_->next_;
    return *this;
  }

  iterator &operator--() {
    node_pointer_ = node_pointer_->prev_;
    return *this;
  }

  iterator operator++(int) {
    iterator buffer(node_pointer_);
    node_pointer_ = node_pointer_->next_;
    return buffer;
  }

  iterator operator--(int) {
    iterator buffer(node_pointer_);
    node_pointer_ = node_pointer_->prev_;
    return buffer;
  }

  iterator operator+(int n) {
    while (n--) node_pointer_ = node_pointer_->next_;
    return *this;
  }

  iterator &operator+=(int n) {
    while (n--) node_pointer_ = node_pointer_->next_;
    return *this;
  }

  iterator operator-(int n) {
    while (n--) node_pointer_ = node_pointer_->prev_;
    return *this;
  }

  void DeleteNode() {
    node_pointer_->prev_->next_ = node_pointer_->next_;
    node_pointer_->next_->prev_ = node_pointer_->prev_;
    delete node_pointer_;
  }

  iterator AddNode(const_reference value) {
    node_type *new_one = new node_type;
    new_one->value_ = value;
    new_one->next_ = node_pointer_;
    new_one->prev_ = node_pointer_->prev_;
    // there is always some node at node_pointer_->prev_
    node_pointer_->prev_->next_ = new_one;
    node_pointer_->prev_ = new_one;
    return iterator(new_one);
  }

  void BindNode(const iterator &iter) {
    BindNodeNext(iter);
    iter.node_pointer_->prev_ = node_pointer_;
  }

  void BindNodeNext(const iterator &iter) {
    node_pointer_->next_ = iter.node_pointer_;
  }

  bool NextNodeNotEqual(const iterator &iter) {
    return node_pointer_->next_ != iter.node_pointer_;
  }

  bool NextNextNodeNotEqual(const iterator &iter) {
    return node_pointer_->next_->next_ != iter.node_pointer_;
  }

  void BindNodeAndGoForward(iterator &iter) {
    BindNode(iter);
    ++(*this);
    ++iter;
  }

  void SwapNodePointers() {
    std::swap(node_pointer_->next_, node_pointer_->prev_);
  }

  const_node_pointer get_node_pointer() const { return node_pointer_; }

 private:
  node_pointer node_pointer_;
};

template <typename T>
class list<T>::ListConstIterator {
 public:
  using value_type = T;
  using node_type = ListNode<T>;
  using node_pointer = ListNode<T> *;
  using const_node_pointer = const ListNode<T> *;
  using const_reference = const T &;
  using const_iterator = ListConstIterator;
  using iterator = ListIterator;

 public:
  ListConstIterator() : node_pointer_(nullptr){};

  explicit ListConstIterator(const const_node_pointer node)
      : node_pointer_(node) {}

  operator ListIterator() const {
    return ListIterator(const_cast<node_pointer>(node_pointer_));
  }

  const_reference operator*() { return node_pointer_->value_; }
  bool operator!=(const const_iterator &iter) {
    return node_pointer_ != iter.node_pointer_;
  }
  bool operator==(const const_iterator &iter) {
    return node_pointer_ == iter.node_pointer_;
  }

  const_iterator &operator++() {
    node_pointer_ = node_pointer_->next_;
    return *this;
  }

  const_iterator &operator--() {
    node_pointer_ = node_pointer_->prev_;
    return *this;
  }

  const_node_pointer get_node_pointer() const { return node_pointer_; }

 private:
  const_node_pointer node_pointer_;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_H_