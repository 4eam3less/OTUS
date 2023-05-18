#pragma once

#include "observer.hpp"
#include "shape.hpp"

class View : public IObserver {
public:
    void update(std::shared_ptr<IShape> shape) override {
        redraw(shape);
    }

    void redraw(std::shared_ptr<IShape>) {

    }

private:
};