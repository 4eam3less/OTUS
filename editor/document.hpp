#pragma once

#include "shape.hpp"
#include "observer.hpp"
#include <deque>
#include <string>

inline std::string load_file(const std::string &path);

inline void save_file(const std::string &/*path*/, const std::string &/*data*/) {}

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

    std::string serialize() {
        return {};
    }

    void deserialize(std::string);

    void push_shape(std::shared_ptr<IShape> shape) {
        shapes_.push_back(shape);
        capture_shape_ = (--shapes_.end());
        notify();
    }

    bool capture_shape(const Point &/*coordinates*/) {
        return true;
    }

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

    void repaint_all() {
        auto tmp = capture_shape_;
        for (auto it = shapes_.cbegin(); it != shapes_.cend(); ++it) {
            notify();
        }
        capture_shape_ = tmp;
    }

    std::deque<std::shared_ptr<IShape>> shapes_;
    std::deque<std::shared_ptr<IShape>>::iterator capture_shape_;
    std::list<IObserver *> observers_;
};