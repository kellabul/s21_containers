#ifndef CPP2_S21_CONTAINERS_S21_LIST_LIST_NODE_H_
#define CPP2_S21_CONTAINERS_S21_LIST_LIST_NODE_H_

namespace s21 {
template <typename T>
class ListNode {
 public:
  using value_type = T;

 public:
  ListNode() = default;
  explicit ListNode(const value_type value) : value_(value) {}
  value_type &get_value() { return value_; }

  value_type value_ = 0;
  ListNode<T> *prev_ = nullptr;
  ListNode<T> *next_ = nullptr;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_NODE_H_