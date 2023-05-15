#include <iostream>
#include "factory.hpp"

template<typename T>
void f(T) {

}

int main() {

    Circle c(Point{1, 1}, 5);
    Rectangle r(Point{1, 1}, 5, 5);
    Factory ff;
    Point p{1, 1};
    auto res = ff.create(Shapes::circle, p, 5);
    auto res1 = ff.create(Shapes::rectangle);
    std::unique_ptr<Circle> c1;
    std::unique_ptr<Rectangle> r1;
    //auto res1 = ff.create<Circle>(p, 5);


    //Controller.add_shape(circle, 5, Point{1, 1});

    //Controller.add_shape(std::make_unique<Circle>(5, Point{1, 1}));


    f(c);
    f(r);
    return 0;
}
