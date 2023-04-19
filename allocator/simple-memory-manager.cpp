#include "simple-memory-manager.hpp"
#include <ranges>

template<class Iterator>
Iterator find_by_key(const Iterator &begin, const Iterator &end, void *ptr);

void SimpleMemoryManager::create(size_t chunk_size) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    current_chunk_ = std::malloc(chunk_size);
    if (!current_chunk_)
        throw std::bad_alloc();
    master_data_.push_back(current_chunk_);
    pointer_ = current_chunk_;
    size_ = chunk_size;
}

void SimpleMemoryManager::clear() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::for_each(master_data_.begin(), master_data_.end(), [](auto ptr) { free(ptr); });
    master_data_.clear();
}

void *SimpleMemoryManager::get(size_t size) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (!state())
        throw std::runtime_error("SimpleMemoryManager has not been initialized");
    if (size > size_)
        throw std::runtime_error("an attempt to allocate an amount of memory that exceeds the size of the chunk");
    if (size <= 0)
        return nullptr;

    size_t memory_used = reinterpret_cast<char *>(pointer_) - reinterpret_cast<char *>(current_chunk_);
    size_t ost = size_ - memory_used;
    if (size > ost) {
        create(size_);
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

size_t SimpleMemoryManager::find_chunk(void *ptr) {
    for (size_t i = 0; i < master_data_.size(); ++i) {
        if (reinterpret_cast<char *>(ptr) >= reinterpret_cast<char *>(master_data_[i]) &&
            reinterpret_cast<char *>(ptr) < reinterpret_cast<char *>(master_data_[i + 1])) {
            return i;
        }
    }
    return -1;
}

bool SimpleMemoryManager::try_reuse_memory(size_t) {

    for (auto it = map_.begin(); it != map_.end(); ++it) {
        if (it->second)
            continue;
        //auto next = std::next(it);
        //auto free_size = reinterpret_cast<char *>(it->first); //- *it;
    }
    return false;
}

template<class Iterator>
Iterator find_by_key(const Iterator &begin, const Iterator &end, void *ptr) {
    for (auto it = begin; it != end; ++it) {
        if (it->first == ptr)
            return it;
    }
    return end;
}