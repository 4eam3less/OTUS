#include "controller.hpp"
#include <memory>
#include "circle.hpp"
#include "rectangle.hpp"
#include "view.hpp"

template<typename T>
void f(T) {
}

int main() {

    View view;
    Circle c(Point{1, 1}, 5);
    Rectangle r(Point{1, 1}, 5, 5);

    std::unique_ptr<Circle> c1;
    std::unique_ptr<Rectangle> r1;

    Controller con;
    con.push_shape(std::make_shared<Circle>());
    con.push_shape(std::make_shared<Rectangle>());
    f(c);
    f(r);
    return 0;
}
