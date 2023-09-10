#include <initializer_list>
#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
class queue {
 private:
  struct Node {
    T data;
    std::unique_ptr<Node> next;
    explicit Node(const T& data) : data(data), next(nullptr) {}
  };

  std::unique_ptr<Node> head_;
  Node* tail_;
  std::size_t node_count = 0;

 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  queue(const queue& other) : queue() {
    Node* current_other = other.head_.get();
    while (current_other) {
      push(current_other->data);
      current_other = current_other->next.get();
    }
  }
  queue(std::initializer_list<value_type> const& items)
      : head_(nullptr), tail_(nullptr), node_count(0) {
    for (const auto& item : items) {
      push(item);
    }
  }
  queue(queue&& other) noexcept
      : head_(std::move(other.head_)),
        tail_(other.tail_),
        node_count(other.node_count) {
    other.tail_ = nullptr;
    other.node_count = 0;
  }
  queue() : head_(nullptr), tail_(nullptr), node_count(0){};
  ~queue() = default;
  queue& operator=(const queue& other) {
    if (this != &other) {
      while (!empty()) {
        pop();
      }

      Node* current_other = other.head_.get();
      while (current_other) {
        push(current_other->data);
        current_other = current_other->next.get();
      }
    }
    return *this;
  }
  queue& operator=(queue&& other) noexcept {
    if (this != &other) {
      head_ = std::move(other.head_);
      tail_ = other.tail_;
      node_count = other.node_count;

      other.tail_ = nullptr;
      other.node_count = 0;
    }
    return *this;
  }
  bool empty() const { return !head_; }
  size_type size() const { return node_count; }
  template <typename... Args>
  void insert_many_back(Args&&... args) {
    (push(std::forward<Args>(args)), ...);
  }
  void push(const_reference value) {
    auto new_node = std::make_unique<Node>(value);
    Node* new_tail = new_node.get();
    if (tail_) {
      tail_->next = std::unique_ptr<Node>(new_node.release());
    } else {
      head_ = std::move(new_node);
    }

    tail_ = new_tail;
    node_count++;
  }

  void pop() {
    if (!head_) throw std::out_of_range("Queue is empty");
    head_ = std::move(head_->next);
    if (!head_) tail_ = nullptr;
    node_count--;
  }

  reference front() {
    if (!head_) throw std::out_of_range("Queue is empty");
    return head_->data;
  }

  const_reference front() const {
    if (!head_) throw std::out_of_range("Queue is empty");
    return head_->data;
  }

  reference back() {
    if (!tail_) throw std::out_of_range("Queue is empty");
    return tail_->data;
  }
  const_reference back() const {
    if (!tail_) throw std::out_of_range("Queue is empty");
    return tail_->data;
  }
  void swap(queue& other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
    std::swap(node_count, other.node_count);
  }
  friend bool operator==(const queue& lhs, const queue& rhs) {
    Node* current_lhs = lhs.head_.get();
    Node* current_rhs = rhs.head_.get();

    while (current_lhs && current_rhs) {
      if (current_lhs->data != current_rhs->data) {
        return false;
      }
      current_lhs = current_lhs->next.get();
      current_rhs = current_rhs->next.get();
    }

    return (!current_lhs && !current_rhs);
  }

  friend bool operator!=(const queue& lhs, const queue& rhs) {
    return !(lhs == rhs);
  }

  friend bool operator<(const queue& lhs, const queue& rhs) {
    Node* current_lhs = lhs.head_.get();
    Node* current_rhs = rhs.head_.get();

    while (current_lhs && current_rhs) {
      if (current_lhs->data != current_rhs->data) {
        return current_lhs->data < current_rhs->data;
      }
      current_lhs = current_lhs->next.get();
      current_rhs = current_rhs->next.get();
    }

    return (current_lhs == nullptr && current_rhs != nullptr);
  }

  friend bool operator<=(const queue& lhs, const queue& rhs) {
    return !(lhs > rhs);
  }

  friend bool operator>(const queue& lhs, const queue& rhs) {
    return rhs < lhs;
  }

  friend bool operator>=(const queue& lhs, const queue& rhs) {
    return !(lhs < rhs);
  }
  class iterator {
   private:
    Node* current;

   public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    iterator(Node* ptr) : current(ptr) {}

    reference operator*() { return current->data; }
    pointer operator->() { return &current->data; }

    iterator& operator++() {
      if (current) {
        current = current->next.get();
      }
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }
    iterator& operator--() {
      current = current->prev;
      return *this;
    }
    friend bool operator==(const iterator& a, const iterator& b) {
      return a.current == b.current;
    }

    friend bool operator!=(const iterator& a, const iterator& b) {
      return a.current != b.current;
    }
  };

  iterator begin() { return iterator(head_.get()); }
  iterator end() { return iterator(nullptr); }
};

}  // namespace s21
