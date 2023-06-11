#pragma once

#include "shape.hpp"

/**
* @brief The rectangle class
*/
class Rectangle : public IShape {
public:
    /**
    * @brief Create the rectangle
    * @param coordinates a rectangle position
    * @param width a rectangle width
    * @param height a rectangle height
    * @param color a rectangle color
    */
    explicit Rectangle(const Point &coordinates = Point{}, size_t width = 1,
                       size_t height = 1, Color color = Color{}) : coordinates_(coordinates),
                                                                   width_(width),
                                                                   height_(height),
                                                                   color_(color) {};

    ~Rectangle() override = default;

    /**
    * @brief Set rectangle color
    * @param color an RGB color
    */
    void set_color(const Color &color) override {
        color_ = color;
    };

    /**
    * @brief Get rectangle color
    */
    Color get_color() override {
        return color_;
    }

    /**
    * @brief Move rectangle
    * @param point a displacement direction
    */
    void move(const Point &) override {
    }

    /**
    * @brief Get lines of rectangle
    */
    std::vector<Line> lines() override {
        return std::vector<Line>{};
    }

    /**
    * @brief Resize rectangle
    * @param coefficient a shape scaling factor
    */
    void resize(double coefficient) override {
        width_ *= coefficient;
        height_ *= coefficient;
        // calculate new coordinates
    }

    /**
    * @brief A rectangle serialization
    */
    virtual std::string serialize() override {
        return {};
    }

    /**
    * @brief A rectangle deserialize
    * @param data a data for deserialize
    */
    void deserialize(const std::string &) override {}

private:
    Point coordinates_;
    size_t width_;
    size_t height_;
    Color color_;
};