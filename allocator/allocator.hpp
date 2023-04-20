#pragma once

#include "simple-memory-manager.hpp"

template<typename T, size_t ReserveSize>
class ReserveAllocator {
public:
    using value_type = T;

    T *allocate(std::size_t n) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        if (!memory_manager_.state())
            memory_manager_.create(ReserveSize * sizeof(T));
        return reinterpret_cast<T *>(memory_manager_.get(n * sizeof(T)));
    }

    void deallocate(T *p, size_t) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        memory_manager_.destroy(p);
    }

    template<typename U>
    struct rebind {
        using other = ReserveAllocator<U, ReserveSize>;
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
