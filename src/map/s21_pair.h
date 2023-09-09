#ifndef CPP2_S21_CONTAINERS_MAP_H_S21_PAIR_H_
#define CPP2_S21_CONTAINERS_MAP_H_S21_PAIR_H_

namespace s21 {

template <typename Key, typename Value>
class pair {
  using std_pair = std::pair<Key, Value>;

 public:
  pair() : first(Key{}), second(Value{}) {}

  pair(const pair& other) : first(other.first), second(other.second) {}

  pair(pair&& other) : first(other.first), second(other.second) {}

  pair& operator=(const pair& other) noexcept {
    // const_cast<Key&>(first) = other.first;
    first = other.first;
    second = other.second;
    return *this;
  }

  pair& operator=(pair&& other) noexcept {
    first = other.first;
    second = other.second;
    return *this;
  }

  pair(Key key, Value value) : first(key), second(value) {}

  pair(const std_pair& other) : first(other.first), second(other.second) {}

  operator std_pair() const { return std::make_pair(first, second); }

  bool operator==(const pair& other) const { return first == other.first; }

  bool operator!=(const pair& other) const { return first != other.first; }

  bool operator<(const pair& other) const { return first < other.first; }

  bool operator<=(const pair& other) const { return first <= other.first; }

  bool operator>(const pair& other) const { return first > other.first; }

  bool operator>=(const pair& other) const { return first >= other.first; }

  Key first;
  Value second;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_H_S21_PAIR_H_
