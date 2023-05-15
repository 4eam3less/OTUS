#pragma once

#include "reserve-allocator.hpp"
#include <vector>

template<typename U>
struct Node {
    explicit Node(const U &value) : data(value) {};

    Node(Node &other) = default;

    Node<U> *next = nullptr;
    Node<U> *prev = nullptr;
    U data;
};

template<typename T, typename Allocator = ReserveAllocator<Node<T>, 10>>
class List {
    template<typename U>
    class Iterator {
    public:
        friend class List;

        explicit Iterator(U *begin) : pos_(begin) {}

        Iterator(const Iterator<U> &other) = default;

        Iterator(const Iterator<U> &&other) noexcept = default;

        ~Iterator() = default;

        Iterator &operator++() {
            pos_ = pos_->next;
            return *this;
        }

        Iterator &operator--() {
            pos_ = pos_->prev();
            return *this;
        }

        Iterator operator++(int) &{
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        Iterator operator--(int) &{
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator!=(const Iterator<U> &it) const { return pos_ != it.pos_; }

        bool operator==(const Iterator<U> &it) const { return pos_ == it.pos_; }

        T &operator*() const { return pos_->data; }

    private:
        U *pos_;
    };

    using iterator = Iterator<Node<T>>;
    using const_iterator = Iterator<const Node<T>>;
    using reverse_iterator = std::reverse_iterator<Node<T>>;

public:

    List() : data_(nullptr), size_(0) {};

    explicit List(const T &value) : size_(1) {
        data_ = create(value);
        last_ = data_;
    }

    void push_back(const T &value) {
        Node<T> *ptr = create(value);
        last_->next = ptr;
        ptr->prev = last_;
        last_ = last_->next;
        ++size_;
    }

    void pop_back() {
        auto ptr = last_;
        last_ = last_->prev;
        remove(ptr, 1);
        --size_;
    }

    void push_front(const T &value) {
        Node<T> *ptr = create(value);
        auto tmp = data_;
        tmp->prev = ptr;
        data_ = ptr;
        data_->next = tmp;
        ++size_;
    }

    void pop_front() {
        auto ptr = data_;
        data_ = data_->next;
        data_->prev = nullptr;

        remove(ptr, 1);
        --size_;
    }

    template<class ListIterator>
    Iterator<Node<T>> insert(ListIterator &it, const T &value) {
        Node<T> *new_node = create(value);

        auto old = it.pos_->next;
        new_node->next = old;
        new_node->prev = it.pos_;

        old->prev = new_node;
        it.pos_->next = new_node;
        ++size_;
        return Iterator<Node<T>>(it.pos_->next);
    }

    template<class ListIterator>
    Iterator<Node<T>> erase(ListIterator &it) {
        it.pos_->next->prev = it.pos_->prev;
        it.pos_->prev->next = it.pos_->next;
        Iterator<Node<T>> res(it.pos_->next);

        remove(it.pos_, 1);
        --size_;
        return res;
    }

    [[nodiscard]] bool empty() const {
        return size_;
    }

    [[nodiscard]] size_t size() const {
        return size_;
    }

    iterator begin() noexcept {
        return iterator(data_);
    }

    iterator end() noexcept {
        return iterator({});
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(data_);
    }

    const_iterator cend() const noexcept {
        return const_iterator(nullptr);
    }

    reverse_iterator rbegin() { return std::make_reverse_iterator(this->end()); }

    reverse_iterator rend() { return std::make_reverse_iterator(this->begin()); }

private:

    template<typename ... Args>
    Node<T> *create(Args &&...args) {
        auto ptr = allocator_.allocate(1);
        allocator_.construct(ptr, std::forward<Args>(args)...);
        return ptr;
    }

    void remove(Node<T> *ptr, size_t size) {
        allocator_.destroy(ptr);
        allocator_.deallocate(ptr, size);
    }

    Allocator allocator_;
    Node<T> *data_;
    Node<T> *last_;
    size_t size_;
};
