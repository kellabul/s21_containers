#include <iostream>
#include <iterator>
#include <memory>
#include <stdexcept>
#include <initializer_list>

namespace s21 {

template <typename T>
class stack {
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
        explicit Node(const T& data) : data(data), next(nullptr) {}
    };
    std::unique_ptr<Node> top_node;
    std::size_t node_count = 0;

public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    stack() = default;
    ~stack() = default;
    stack(const stack& other) {
    Node* current_other = other.top_node.get();
    s21::stack<Node*> tempNodes;
    while (current_other) {
        tempNodes.push(current_other);
        current_other = current_other->next.get();
    }

    while (!tempNodes.empty()) {
        push(tempNodes.top()->data);
        tempNodes.pop();
    }
    }
    stack(std::initializer_list<value_type> const &items)
        : top_node(nullptr), node_count(0) {
        for (const auto &item : items) {
            push(item);
        }
    }
    stack& operator=(const stack& other) {
        if (this != &other) { 
            stack temp(other);
            swap(temp);
        }
        return *this;
    }
    bool empty() const {
        return !top_node;
    }
    void swap(stack& other) noexcept {
        std::swap(top_node, other.top_node);
        std::swap(node_count, other.node_count);
    }
    size_type size() const {
        return node_count;
    }
    template<typename... Args>
    void insert_many_front(Args&&... args) {
        (push(std::forward<Args>(args)), ...);
    }
    void push(const_reference value) {
        auto new_node = std::make_unique<Node>(value);
        new_node->next = std::move(top_node);
        top_node = std::move(new_node);
        node_count++;
    }

    void pop() {
        if (!top_node) throw std::out_of_range("Stack is empty");
        top_node = std::move(top_node->next);
        node_count--;
    }

    reference top() {
        if (!top_node) throw std::out_of_range("Stack is empty");
        return top_node->data;
    }

    const_reference top() const {
        if (!top_node) throw std::out_of_range("Stack is empty");
        return top_node->data;
    }

    stack(stack&& other) noexcept
    : top_node(std::move(other.top_node)), node_count(other.node_count) {
    other.node_count = 0;
    }
    stack& operator=(stack&& other) noexcept {
        if (this != &other) {
            top_node = std::move(other.top_node);
            node_count = other.node_count;
        other.node_count = 0;
        }
        return *this;
    }
    friend bool operator==(const stack& lhs, const stack& rhs) {
        if (lhs.node_count != rhs.node_count) {
            return false;
        }
        Node* current_lhs = lhs.top_node.get();
        Node* current_rhs = rhs.top_node.get();
        while (current_lhs && current_rhs) {
            if (current_lhs->data != current_rhs->data) {
                return false;
            }
            current_lhs = current_lhs->next.get();
            current_rhs = current_rhs->next.get();
        }
        return true;
    }

    friend bool operator!=(const stack& lhs, const stack& rhs) {
        return !(lhs == rhs);
    }
};

}  // namespace s21
