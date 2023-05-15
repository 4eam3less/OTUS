#pragma once

#include <deque>
#include "shape.hpp"
#include "memento.hpp"

class Document {
public:
    Document();

    Document(const Memento &snapshot);

    std::unique_ptr<Memento> snapshot();

    void restore(std::unique_ptr<Memento> snapshot);

    void insert_shape(std::shared_ptr<IShape> shaip);

    void remove_shape(std::deque<std::shared_ptr<IShape>>::iterator &it);

    void move_shaip(const Point &point);

private:
    std::deque<std::shared_ptr<IShape>> shapes_;
};