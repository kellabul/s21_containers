#ifndef CPP2_S21_CONTAINERS_S21_MAP_MAP_NODE_H_
#define CPP2_S21_CONTAINERS_S21_MAP_MAP_NODE_H_

namespace s21 {
template <typename T>
struct MapNode {
  //  public:
  T value_{};
  MapNode<T> *prev_ = nullptr;
  MapNode<T> *next_ = nullptr;
};
}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_S21_MAP_MAP_NODE_H_