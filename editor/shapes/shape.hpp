#pragma once

#include "utility.hpp"
#include <string>
#include <vector>

class IShape {
public:

    virtual ~IShape() = default;

    virtual void set_color(const Color &color) = 0;

    virtual Color get_color() = 0;

    virtual void move(const Point &point) = 0;

    virtual std::vector<Line> lines() = 0;

    virtual void resize(double coefficient) = 0;

    virtual std::string serialize() = 0;

    virtual void deserialize(const std::string &data) = 0;
};