#pragma once

#include <iostream>

struct Point {
    uint32_t x = 0;
    uint32_t y = 0;
};

struct Color {
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
};

class IShape {
public:

    virtual ~IShape() = default;

    virtual void color(const Color &color) = 0;

    virtual Color color() = 0;

    virtual void move(const Point &point) = 0;

};

class Circle : public IShape {
public:
    explicit Circle(const Point &coordinates = Point{}, size_t radius = 1,
                    Color color = Color{}) : radius_(radius),
                                             coordinates_(coordinates),
                                             color_(color) {}

    Circle(Circle &other) = default;

    Circle(Circle &&other) = default;

    ~Circle() override = default;

    void color(const Color &color) override {
        color_ = color;
    };

    Color color() override {
        return color_;
    }

    void move(const Point &) override {
        std::cout << radius_;
    }

private:
    size_t radius_;
    Point coordinates_;
    Color color_;
};

class Rectangle : public IShape {
public:
    explicit Rectangle(const Point &coordinates = Point{}, size_t width = 1,
                       size_t height = 1, Color color = Color{}) : coordinates_(coordinates),
                                                                   width_(width),
                                                                   height_(height),
                                                                   color_(color) {};

    ~Rectangle() override = default;

    void color(const Color &color) override {
        color_ = color;
    };

    Color color() override {
        return color_;
    }

    void move(const Point &) override {
        std::cout << height_ << width_;
    }

private:
    Point coordinates_;
    size_t width_;
    size_t height_;
    Color color_;
};