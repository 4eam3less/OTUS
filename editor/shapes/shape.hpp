#pragma once

#include "utility.hpp"
#include <string>
#include <vector>

/**
 * @brief The interface class for shapes
 */
class IShape {
public:

    virtual ~IShape() = default;

    /**
    * @brief Set shape color
    * @param color an RGB color
    */
    virtual void set_color(const Color &color) = 0;

    /**
    * @brief Get shape color
    */
    virtual Color get_color() = 0;

    /**
    * @brief Move a shape
    * @param point a displacement direction
    */
    virtual void move(const Point &point) = 0;

    /**
    * @brief Get lines of shape
    */
    virtual std::vector<Line> lines() = 0;

    /**
    * @brief Resize a shape
    * @param coefficient a shape scaling factor
    */
    virtual void resize(double coefficient) = 0;

    /**
    * @brief Shape serialization
    */
    virtual std::string serialize() = 0;

    /**
    * @brief  Shape deserialize
    * @param data a data for deserialize
    */
    virtual void deserialize(const std::string &data) = 0;
};