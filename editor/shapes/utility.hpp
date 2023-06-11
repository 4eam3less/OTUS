#pragma once

#include <cstdint>

/** @brief The structure for coordinate */
struct Point {
    uint32_t x = 0;
    uint32_t y = 0;
};

/** @brief The structure for line */
struct Line {
    Point p1 = Point{};
    Point p2 = Point{};
};

/** @brief The structure for RGB color */
struct Color {
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
};

