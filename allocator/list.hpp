#pragma once

#include "reserve-allocator.hpp"
#include <stdexcept>
#include <memory>

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

        Iterator(const Iterator<U> &other) noexcept = default;

        Iterator(Iterator<U> &&other) noexcept = default;

        ~Iterator() = default;

        Iterator &operator++() noexcept {
            pos_ = pos_->next;
            return *this;
        }

        Iterator &operator--() noexcept {
            pos_ = pos_->prev();
            return *this;
        }

        Iterator operator++(int) & noexcept {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        Iterator operator--(int) & noexcept {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator!=(const Iterator<U> &it) const noexcept { return pos_ != it.pos_; }

        bool operator==(const Iterator<U> &it) const noexcept { return pos_ == it.pos_; }

        U &operator*() const noexcept { return *pos_; }

        U *operator->() const noexcept { return pos_; }

    private:
        U *pos_;
    };

    using iterator = Iterator<Node<T>>;
    using const_iterator = Iterator<const Node<T>>;
    using reverse_iterator = std::reverse_iterator<Node<T>>;

public:

    List() : head_(nullptr), size_(0) {};

    explicit List(const T &value) {
        init(value);
    }

    List(List &other) {
        for (auto it = other.begin(); it != other.end(); ++it) {
            push_back(it->data);
        }
    }

    ~List() {
        clear();
    }

    void push_back(const T &value) {
        if (!size_) [[unlikely]] {
            init(value);
            return;
        }
        Node<T> *ptr = create(value);
        tail_->next = ptr;
        ptr->prev = tail_;
        tail_ = tail_->next;
        ++size_;
    }

    void pop_back() {
        if (size_ <= 1) {
            clear();
            return;
        }
        auto ptr = tail_;
        tail_ = tail_->prev;
        tail_->next = nullptr;
        remove(ptr, 1);
        --size_;
    }

    void clear() {
        while (head_) {
            auto tmp = head_;
            head_ = head_->next;
            remove(tmp);
        }
        tail_ = nullptr;
        size_ = 0;
    }

    void push_front(const T &value) {
        if (!size_) [[unlikely]] {
            init(value);
            return;
        }
        Node<T> *ptr = create(value);
        auto tmp = head_;
        tmp->prev = ptr;
        head_ = ptr;
        head_->next = tmp;
        ++size_;
    }

    void pop_front() {
        if (size_ <= 1) {
            clear();
            return;
        }
        auto ptr = head_;
        head_ = head_->next;
        head_->prev = nullptr;
        remove(ptr);
        --size_;
    }

    template<class ListIterator>
    Iterator<Node<T>> insert(ListIterator &it, const T &value) {
        if (it == this->end())
            throw std::runtime_error("Incorrect iterator");
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
        if (it == this->end())
            throw std::runtime_error("Incorrect iterator");
        it.pos_->next->prev = it.pos_->prev;
        it.pos_->prev->next = it.pos_->next;
        Iterator<Node<T>> res(it.pos_->next);

        remove(it.pos_);
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
        return iterator(head_);
    }

    iterator end() noexcept {
        return iterator({});
    }

    const_iterator cbegin() const noexcept {
        return const_iterator(head_);
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
#if _LIBCPP_STD_VER <= 17
        allocator_.construct(ptr, std::forward<Args>(args)...);
#else
        std::allocator_traits<Allocator>::construct(allocator_, ptr, std::forward<Args>(args)...);
#endif
        return ptr;
    }

    void remove(Node<T> *ptr, size_t size = 1) {
#if _LIBCPP_STD_VER <= 17
        allocator_.destroy(ptr);
#else
        std::allocator_traits<Allocator>::destroy(allocator_, ptr);
#endif
        allocator_.deallocate(ptr, size);
    }

    void init(const T &value) {
        head_ = create(value);
        tail_ = head_;
        size_ = 1;
    }

    Allocator allocator_;
    Node<T> *head_;
    Node<T> *tail_;
    size_t size_ = 0;
};