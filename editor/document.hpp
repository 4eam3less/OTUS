#pragma once

#include <deque>
#include "shape.hpp"
#include "memento.hpp"
#include "observer.hpp"


class Document : public ISubject {
public:

    Document() = default;

    void attach(IObserver *observer) override {
        observers_.push_back(observer);
    }

    void detach(IObserver *observer) override {
        observers_.remove(observer);
    }

    void notify() override {
        for (const auto &it: observers_) {
            it->update(*capture_shape_);
        }
    }

    void push_shape(std::shared_ptr<IShape> shape) {
        shapes_.push_back(shape);
        capture_shape_ = (--shapes_.end());
        notify();
    }

    bool try_capture_shape(const Point &coordinates);

    void move_shape(const Point &coordinates) {
        capture_shape_->get()->move(coordinates);
        notify();
    }

    void repaint_shape(const Color color) {
        capture_shape_->get()->set_color(color);
        notify();
    }

    void resize_shape(double coefficient) {
        capture_shape_->get()->resize(coefficient);
        notify();
    }

    void remove_shape() {
        capture_shape_ = shapes_.erase(capture_shape_);
        notify();
    }

private:
    std::deque<std::shared_ptr<IShape>> shapes_;
    std::deque<std::shared_ptr<IShape>>::iterator capture_shape_;
    std::list<IObserver *> observers_;
};