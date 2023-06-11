#pragma once

#include "shape.hpp"

/**
* @brief The circle class
*/
class Circle : public IShape {
public:

    /**
    * @brief Create the circle
    * @param coordinates a circle position
    * @param radius a circle radius
    * @param color a circle color
    */
    explicit Circle(const Point &coordinates = Point{}, double radius = 1,
                    Color color = Color{}) : radius_(radius),
                                             coordinates_(coordinates),
                                             color_(color) {}

    Circle(Circle &other) = default;

    Circle(Circle &&other) = default;

    ~Circle() override = default;

    /**
    * @brief Set circle color
    * @param color an RGB color
    */
    void set_color(const Color &color) override {
        color_ = color;
    };

    /**
    * @brief Get circle color
    */
    Color get_color() override {
        return color_;
    }

    /**
    * @brief Move circle
    * @param point a displacement direction
    */
    void move(const Point &) override {
    }

    /**
   * @brief Get lines of circle
   */
    std::vector<Line> lines() override {
        return std::vector<Line>{};
    }

    /**
    * @brief Resize circle
    * @param coefficient a circle scaling factor
    */
    void resize(double coefficient) override {
        radius_ *= coefficient;
        // calculate new coordinates
    }

    /**
    * @brief A circle serialization
    */
    std::string serialize() override {
        return {};
    }

    /**
    * @brief A circle deserialize
    * @param data a data for deserialize
    */
    void deserialize(const std::string &) override {}

private:
    double radius_;
    Point coordinates_;
    Color color_;
};