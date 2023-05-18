#include "controller.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "view.hpp"

int main() {

    View view;
    Controller controller(view);

    controller.push_shape(std::make_shared<Circle>(Point{10, 10}, 5.0));
    controller.push_shape(std::make_shared<Circle>(Point{20, 10}, 8.0));
    controller.repaint_shape(Color{128, 77, 225});

    controller.push_shape(std::make_shared<Rectangle>());
    if (!controller.capture_shape(Point{10, 10}))
        throw std::runtime_error("shape not found");
    controller.move_shape(Point{50, 85});
    controller.resize_shape(2);
    controller.repaint_shape(Color{50, 140, 255});

    return 0;
}
