#pragma once

#include <deque>
#include "shape.hpp"

class Memento {
public:
    Memento(const std::deque<std::shared_ptr<IShape>> &shapes);

    std::deque<std::shared_ptr<IShape>> get_shapes();

private:
    std::deque<std::shared_ptr<IShape>> shapes_;
};

void save(std::unique_ptr<Memento> snapshot, const std::string &path);

std::unique_ptr<Memento> load(const std::string &path);
