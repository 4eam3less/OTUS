#include "simple-memory-manager.hpp"

template<class Iterator>
Iterator find_by_key(const Iterator &begin, const Iterator &end, void *ptr);


void SimpleMemoryManager::create(size_t size) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    data_ = std::malloc(size);
    if (!data_)
        throw std::bad_alloc();
    pointer_ = data_;
    size_ = size;
}

void SimpleMemoryManager::clear() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::free(data_);
}

void *SimpleMemoryManager::get(size_t size) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (!state())
        throw std::runtime_error("SimpleMemoryManager has not been initialized");
    if (size <= 0)
        return nullptr;

    size_t memory_used = reinterpret_cast<char *>(pointer_) - reinterpret_cast<char *>(data_);
    size_t ost = size_ - memory_used;
    if (size > ost) {

    }

    void *tmp = pointer_;
    map_.emplace_back(tmp, true);
    pointer_ = reinterpret_cast<char *>(pointer_) + size;
    return tmp;
}

void SimpleMemoryManager::destroy(void *ptr) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (auto res = find_by_key(map_.begin(), map_.end(), ptr); res != map_.end())
        if (res->second) {
            auto next = std::next(res);
            if (next != map_.end() && !next->second)
                map_.erase(next);
            if (res != map_.begin()) {
                auto prev = std::prev(res);
                if (!prev->second) {
                    map_.erase(res);
                } else {
                    res->second = false;
                }
            } else {
                res->second = false;
            }
            return;
        }
    throw std::runtime_error("not allocate");
}

template<class Iterator>
Iterator find_by_key(const Iterator &begin, const Iterator &end, void *ptr) {
    for (auto it = begin; it != end; ++it) {
        if (it->first == ptr)
            return it;
    }
    return end;
}