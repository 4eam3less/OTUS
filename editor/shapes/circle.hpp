#pragma once

#include "shape.hpp"


class Circle : public IShape {
public:
    explicit Circle(const Point &coordinates = Point{}, double radius = 1,
                    Color color = Color{}) : radius_(radius),
                                             coordinates_(coordinates),
                                             color_(color) {}

    Circle(Circle &other) = default;

    Circle(Circle &&other) = default;

    ~Circle() override = default;

    void set_color(const Color &color) override {
        color_ = color;
    };

    Color get_color() override {
        return color_;
    }

    void move(const Point &) override {
    }

    std::vector<Line> lines() override {
        return std::vector<Line>{};
    }

    void resize(double coefficient) override {
        radius_ *= coefficient;
        // calculate new coordinates
    }

    virtual std::string serialize() override {
        return {};
    }

private:
    double radius_;
    Point coordinates_;
    Color color_;
};