#pragma once

#include <iostream>
#include <map>

class SimpleMemoryManager {
public:

    void create(size_t size) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        data_ = std::malloc(size);
        if (!data_)
            throw std::bad_alloc();
        pointer_ = data_;
        size_ = size;
    }

    void clear() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        std::free(data_);
    }

    void *get(size_t size) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        // add check
        void *tmp = pointer_;
        map_.insert({tmp, true});
        pointer_ = reinterpret_cast<char *>(pointer_) + size;
        return tmp;
    }

    void destroy(void *ptr) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (auto res = map_.find(ptr); res != map_.end())
            if (res->second) {
                res->second = false;
                return;
            }
        throw std::runtime_error("not allocate");
    }

    bool state() {
        return data_;
    }

private:

    void *data_ = nullptr;
    void *pointer_ = nullptr;
    size_t size_ = 0;
    std::map<void *, bool> map_;
};

template<typename T, size_t ReserveSize>
class MyAllocator {
public:
    using value_type = T;

    T *allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (!memory_manager_.state())
            memory_manager_.create(ReserveSize * sizeof(T));
        auto res = reinterpret_cast<T *>(memory_manager_.get(n * sizeof(T)));
        return res;
    }

    void deallocate(T *, size_t) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        //memory_manager_.clear();
    }

    template<typename U>
    struct rebind {
        using other = MyAllocator<U, ReserveSize>;
    };

    template<typename U, typename... Args>
    void construct(U *p, Args &&...args) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        new(p) U(std::forward<Args>(args)...);
    };

    template<typename U>
    void destroy(U *p) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        p->~U();
    }

private:

    SimpleMemoryManager memory_manager_;
};