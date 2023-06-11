#pragma once

#include "observer.hpp"
#include "shape.hpp"

/**
* @brief class View
*/
class View : public IObserver {
public:

    /**
    * @brief This function is called by the ISubject when scene changed
    */
    void update(std::shared_ptr<IShape> shape) override {
        redraw(shape);
    }

    /**
    * @brief redraw a shape
    * @param shape shape to be redrawn
    */
    void redraw(std::shared_ptr<IShape> shape) {
        rendering(shape->lines(), shape->get_color());
    }

private:
    /**
    * @brief rendering a picture
    * @param observer a view
    */
    void rendering(const std::vector<Line> &/*lines*/, const Color &/*color*/) {}

};