#include "simple-memory-manager.hpp"

template<class Iterator>
Iterator find_by_key(const Iterator &begin, const Iterator &end, void *ptr);

void SimpleMemoryManager::create(size_t chunk_size) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    void *new_chunk_ = std::malloc(chunk_size);
    if (!new_chunk_)
        throw std::bad_alloc();
    data_.push_back(new_chunk_);
    map_.emplace_back();
    pointer_ = new_chunk_;
    size_ = chunk_size;
}

void SimpleMemoryManager::clear() {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    std::for_each(data_.begin(), data_.end(), [](auto ptr) { free(ptr); });
    data_.clear();
}

void *SimpleMemoryManager::get(size_t size) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    if (!state())
        throw std::runtime_error("SimpleMemoryManager has not been initialized");
    if (size > size_)
        throw std::runtime_error("an attempt to allocate an amount of memory that exceeds the size of the chunk");
    if (size <= 0)
        return nullptr;

    size_t memory_used = reinterpret_cast<char *>(pointer_) - reinterpret_cast<char *>(data_.back());
    size_t ost = size_ - memory_used;
    if (size > ost) {
        auto res = try_reuse_memory(size);
        if (res != nullptr)
            return res;
        create(size_);
    }
    void *tmp = pointer_;
    map_.back().emplace_back(tmp, true);
    pointer_ = reinterpret_cast<char *>(pointer_) + size;
    return tmp;
}

void SimpleMemoryManager::destroy(void *ptr) {
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    size_t chunk = find_chunk(ptr);
    if (auto res = find_by_key(map_[chunk].begin(), map_[chunk].end(), ptr); res != map_[chunk].end())
        if (res->second) {
            auto next = std::next(res);
            if (next != map_[chunk].end() && !next->second)
                map_[chunk].erase(next);
            if (res != map_[chunk].begin()) {
                auto prev = std::prev(res);
                if (!prev->second) {
                    map_[chunk].erase(res);
                    return;
                }
            }
            res->second = false;
            return;
        }
    throw std::runtime_error("not allocate");
}

bool SimpleMemoryManager::state() {
    return !data_.empty();
}

size_t SimpleMemoryManager::find_chunk(void *ptr) {
    for (size_t i = 0; i < data_.size(); ++i)
        if (reinterpret_cast<char *>(ptr) >= reinterpret_cast<char *>(data_[i]) &&
            reinterpret_cast<char *>(ptr) < (reinterpret_cast<char *>(data_[i]) + size_)) {
            return i;
        }
    throw std::runtime_error("not found");
}

void *SimpleMemoryManager::try_reuse_memory(size_t size) {
    for (auto chunk = map_.begin(); chunk != map_.end(); ++chunk)
        for (auto it = chunk->begin(); it != chunk->end(); ++it) {
            if (it->second)
                continue;

            auto next = std::next(it);
            size_t free_size = next != chunk->end() ?
                               reinterpret_cast<char *>(next->first) - reinterpret_cast<char *>(it->first) :
                               reinterpret_cast<char *>(chunk->begin()->first) - reinterpret_cast<char *>(it->first);
            if (free_size >= size) {
                it->second = true;
                return it->first;
            }
        }
    return nullptr;
}

template<class Iterator>
Iterator find_by_key(const Iterator &begin, const Iterator &end, void *ptr) {
    for (auto it = begin; it != end; ++it) {
        if (it->first == ptr)
            return it;
    }
    return end;
}