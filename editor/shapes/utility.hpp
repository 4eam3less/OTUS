#pragma once

#include <cstdint>

struct Point {
    uint32_t x = 0;
    uint32_t y = 0;
};

struct Line {
    Point p1 = Point{};
    Point p2 = Point{};
};

struct Color {
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
};

