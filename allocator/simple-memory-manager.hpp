#pragma once

#include <iostream>
#include <vector>

class SimpleMemoryManager {
public:

    SimpleMemoryManager() = default;

    SimpleMemoryManager(size_t size);

    SimpleMemoryManager(SimpleMemoryManager &other) = delete;

    SimpleMemoryManager(SimpleMemoryManager &&other) = default;

    ~SimpleMemoryManager();

    void create(size_t size);

    void clear();

    void *get(size_t size);

    void destroy(void *ptr);

    bool state();

private:

    void new_chunk(size_t chunk_size);

    size_t find_chunk(void *ptr);

    void *try_reuse_memory(size_t size);

    void *pointer_ = nullptr;
    size_t size_ = 0;
    std::vector<std::vector<std::pair<void *, bool>>> map_;
    std::vector<void *> data_;
};
