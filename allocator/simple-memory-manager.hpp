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
        return data_;
    }

private:

    void *data_ = nullptr;
    void *pointer_ = nullptr;
    //void *pointer_find_ = nullptr;
    size_t size_ = 0;
    std::vector<std::pair<void *, bool>> map_;
};
