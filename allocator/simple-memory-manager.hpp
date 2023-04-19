#pragma once

#include <iostream>
#include <vector>

class SimpleMemoryManager {
public:
    void create(size_t size);

    void clear();

    void *get(size_t size);

    void destroy(void *ptr);

    bool state() {
        return current_chunk_;
    }

private:

    size_t find_chunk(void *ptr);

    bool try_reuse_memory(size_t size);

    void *current_chunk_ = nullptr;
    void *pointer_ = nullptr;
    size_t size_ = 0;
    std::vector<std::pair<void *, bool>> map_;
    std::vector<void *> master_data_;
};
