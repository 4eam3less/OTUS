#pragma once

#include "shape.hpp"

enum class Shapes {
    circle, rectangle
};

class Factory {
public:
    template<typename ... Args>
    std::unique_ptr<IShape> create(Shapes shape, Args &&...args) {
        switch (shape) {
            case Shapes::circle:
                return create<Circle>(std::forward<Args>(args)...);
            case Shapes::rectangle:
                return create<Rectangle>(std::forward<Args>(args)...);
        }
    }

private:
    template<typename T, typename ... Args>
    std::unique_ptr<T> create(Args &&...args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }
};
