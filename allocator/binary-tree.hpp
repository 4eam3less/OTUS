#pragma once

#include "reserve-allocator.hpp"

template<typename U>
struct Node {
    explicit Node(U value) {
        data = value;
    }

    Node(Node &other) = default;

    Node<U> *left = nullptr;
    Node<U> *right = nullptr;
    Node<U> *parent = nullptr;
    U data;
};

template<typename T, typename Allocator = ReserveAllocator<Node<T>, 10>>
class BinarySearchTree {

//    template<typename U>
//    struct Node {
//        explicit Node(U value) {
//            data = value;
//        }
//
//        Node(Node &other) = default;
//
//        Node<U> *left = nullptr;
//        Node<U> *right = nullptr;
//        Node<U> *parent = nullptr;
//        U data;
//    };

public:

    ~BinarySearchTree() = default;

    explicit BinarySearchTree(T value) : size_(1), root_(value) {}

    void insert(T value) {
        f(value, &root_);
    }

    void f(T &value, Node<T> *ptr) {
        if (value > ptr->data) {
            if (!ptr->right) {
                auto p = allocator_.allocate(1);
                allocator_.construct(p, value);
                ptr->right = p;
                ptr->right->parent = ptr;
                ++size_;
                return;
            }
            ptr = ptr->right;
        } else if (value < ptr->data) {
            if (!ptr->left) {
                auto p = allocator_.allocate(1);
                allocator_.construct(p, value);
                ptr->left = p;
                ptr->left->parent = ptr;
                ++size_;
                return;
            }
            ptr = ptr->left;
        } else {
            auto new_value = new Node<T>(*ptr);

            if (new_value->right)
                new_value->right->parent = new_value;

            if (new_value->left)
                new_value->left->parent = new_value;

            new_value->parent = ptr->parent;

            if (ptr->parent->right && ptr->parent->right == ptr)
                ptr->parent->right = new_value;
            else if (ptr->parent->left && ptr->parent->left == ptr)
                ptr->parent->left = new_value;

            allocator_.destroy(ptr);
            allocator_.deallocate(ptr, 1);
            return;

        }
        f(value, ptr);
    }

    // Удаление элемента из бинарного дерева
    void erase(const T &value);

    // Поиск элемента в бинарном дереве
    bool find(const T &value) const;


    // Очистка бинарного дерева
    void clear();

    [[nodiscard]] size_t size() const {
        return size_;
    }

    [[nodiscard]] bool empty() const {
        return root_;
    }

    // Обход бинарного дерева в префиксном порядке
//    void preorderTraversal() const;
//
//    // Обход бинарного дерева в инфиксном порядке
//    void inorderTraversal() const;
//
//    // Обход бинарного дерева в постфиксном порядке
//    void postorderTraversal() const;


    class Iterator {
        friend class CustomContainer;

    };

private:

    size_t size_;
    Node<T> root_;
    Allocator allocator_;
};