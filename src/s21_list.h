#ifndef CPP2_S21_CONTAINERS_S21_LIST_H_
#define CPP2_S21_CONTAINERS_S21_LIST_H_

namespace s21 {

template <typename T>
class list {
 public:
  using size_type = std::size_t;
  using value_type = T;

 public:
  list() private : struct NodeList {
    ListNode() = default;
    explicit ListNode(const value_type value) : value_(value) {}
    value_type value_ = 0;
    NodeList *prev_ = nullptr;
    NodeList *next_ = nullptr;
  };

  NodeList node_;
  std::list<int>::size_t
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_LIST_H_