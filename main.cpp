
#include <iostream>
#include <memory>
#include <optional>

template <typename T>
class DoublyLinkedList {
private:
    // Node structure definition
    struct Node {
        T value;
        std::shared_ptr<Node> next;
        std::weak_ptr<Node> prev;

        Node(const T& val) : value(val), next(nullptr) {}
    };

    std::shared_ptr<Node> head;
    std::weak_ptr<Node> tail;
    size_t length;

public:
    // Iterator class
    class iterator {
    private:
        std::shared_ptr<Node> current;

    public:
        iterator(std::shared_ptr<Node> node) : current(node) {}

        // Dereference operator to get value
        T& operator*() {
            // 注：对空迭代器调用此函数是未定义行为，测试数据中不会出现
            return current->value;
        }

        // Pre-increment operator
        iterator& operator++() {
            // 注：对空迭代器调用此函数是未定义行为，测试数据中不会出现
            current = current->next;
            return *this;
        }

        // Post-increment operator
        iterator operator++(int) {
            // 注：对空迭代器调用此函数是未定义行为，测试数据中不会出现
            iterator temp = *this;
            current = current->next;
            return temp;
        }

        // Equality operators
        bool operator==(const iterator& other) const {
            // 注：比较属于不同容器的非空迭代器是未定义行为，测试数据中不会出现
            return current == other.current;
        }

        bool operator!=(const iterator& other) const {
            return current != other.current;
        }
    };

    // Constructor
    DoublyLinkedList() : head(nullptr), length(0) {}

    // No destructor needed, memory managed by shared_ptr

    // Check if list is empty
    bool empty() const {
        return length == 0;
    }

    // Get the size of the list
    size_t size() const {
        return length;
    }

    // Add element to the front
    void push_front(const T& value) {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
        
        if (!head) {
            // List is empty
            head = new_node;
            tail = new_node;
        } else {
            // List has elements
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        length++;
    }

    // Add element to the back
    void push_back(const T& value) {
        std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
        
        if (!head) {
            // List is empty
            head = new_node;
            tail = new_node;
        } else {
            // List has elements
            std::shared_ptr<Node> tail_node = tail.lock();
            tail_node->next = new_node;
            new_node->prev = tail_node;
            tail = new_node;
        }
        length++;
    }

    // Remove and return the first element
    std::optional<T> pop_front() {
        if (!head) {
            return std::nullopt;
        }
        
        T value = head->value;
        
        if (length == 1) {
            // Only one element
            head = nullptr;
            tail.reset();
        } else {
            // Multiple elements
            head = head->next;
            head->prev.reset();
        }
        length--;
        
        return value;
    }

    // Remove and return the last element
    std::optional<T> pop_back() {
        if (empty()) {
            return std::nullopt;
        }
        
        std::shared_ptr<Node> tail_node = tail.lock();
        T value = tail_node->value;
        
        if (length == 1) {
            // Only one element
            head = nullptr;
            tail.reset();
        } else {
            // Multiple elements
            std::shared_ptr<Node> prev_node = tail_node->prev.lock();
            prev_node->next = nullptr;
            tail = prev_node;
        }
        length--;
        
        return value;
    }

    // Iterators
    iterator begin() {
        return iterator(head);
    }

    iterator end() {
        return iterator(nullptr);
    }
};

// Dummy main function to satisfy linker - will be overridden by OJ test harness
int main() {
    return 0;
}

