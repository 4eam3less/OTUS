#pragma once

#include "shape.hpp"

class Rectangle : public IShape {
public:
    explicit Rectangle(const Point &coordinates = Point{}, size_t width = 1,
                       size_t height = 1, Color color = Color{}) : coordinates_(coordinates),
                                                                   width_(width),
                                                                   height_(height),
                                                                   color_(color) {};

    ~Rectangle() override = default;

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
        width_ *= coefficient;
        height_ *= coefficient;
        // calculate new coordinates
    }

    virtual std::string serialize() override {
        return {};
    }

    void deserialize(const std::string &) override {}

private:
    Point coordinates_;
    size_t width_;
    size_t height_;
    Color color_;
};