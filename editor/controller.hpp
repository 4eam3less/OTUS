#pragma once

#include <string>
#include "document.hpp"
#include "observer.hpp"
#include "memento.hpp"

class Controller {
public:

    void load(const std::string &path);

    void save(const std::string &path, const std::string &name);

    void erase();

    void push_shape(std::shared_ptr<IShape> shape) {
        document_.push_shape(shape);
    }

    bool capture_shape(const Point &coordinates) {
        return document_.try_capture_shape(coordinates);
    }

    void move_shape(const Point &coordinates) {
        document_.move_shape(coordinates);
    }

    void repaint_shape(const Color color) {
        document_.repaint_shape(color);
    }

    void resize_shape(double coefficient) {
        document_.resize_shape(coefficient);
    }

    void remove_shape() {
        document_.remove_shape();
    }

private:
    Document document_;
};