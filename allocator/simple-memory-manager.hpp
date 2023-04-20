#pragma once

#include <iostream>
#include <vector>

class SimpleMemoryManager {
public:
    void create(size_t size);

    void clear();

    void *get(size_t size);

    void destroy(void *ptr);

    bool state();

    ~SimpleMemoryManager() {
        if (!data_.empty())
            clear();
    }

private:

    size_t find_chunk(void *ptr);

    void *try_reuse_memory(size_t size);

    void *pointer_ = nullptr;
    size_t size_ = 0;
    std::vector<std::vector<std::pair<void *, bool>>> map_;
    std::vector<void *> data_;
};
