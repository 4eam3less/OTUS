#include "document.hpp"
#include "circle.hpp"
#include "rectangle.hpp"
#include "view.hpp"

int main() {

    View view;
    Document document;
    document.attach(&view);

    document.push_shape(std::make_shared<Circle>(Point{10, 10}, 5.0));
    document.push_shape(std::make_shared<Circle>(Point{20, 10}, 8.0));
    document.repaint_shape(Color{128, 77, 225});

    document.push_shape(std::make_shared<Rectangle>());
    if (!document.capture_shape(Point{10, 10}))
        throw std::runtime_error("shape not found");
    document.move_shape(Point{50, 85});
    document.resize_shape(2);
    document.repaint_shape(Color{50, 140, 255});

    save_file("document", document.serialize());

    return 0;
}
