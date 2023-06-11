#pragma once

#include "observer.hpp"
#include "shape.hpp"

class View : public IObserver {
public:
    void update(std::shared_ptr<IShape> shape) override {
        redraw(shape);
    }

    void redraw(std::shared_ptr<IShape> shape) {
        rendering(shape->lines(), shape->get_color());
    }

private:
    void rendering(const std::vector<Line> &/*lines*/, const Color &/*color*/) {}

};