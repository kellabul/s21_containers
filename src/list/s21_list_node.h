#ifndef CPP2_S21_CONTAINERS_S21_LIST_LIST_NODE_H_
#define CPP2_S21_CONTAINERS_S21_LIST_LIST_NODE_H_

namespace s21 {
template <typename T>
struct ListNode {
  //  public:
  T value_{};
  ListNode<T> *prev_ = nullptr;
  ListNode<T> *next_ = nullptr;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_LIST_NODE_H_