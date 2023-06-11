#pragma once

#include "shape.hpp"
#include "observer.hpp"
#include <list>
#include <deque>

/** @mainpage   Vector Editor
*
* @brief  Vector editor created using the MVC (Model View Controller ) pattern
* The editor can save, load the document.
* add and remove shapes.
* recolor, move and scale shapes.
*/

/**
* @brief Load document
* @param path a path to file
*/
inline std::string load_file(const std::string &path);

/**
* @brief Save document
* @param path a path to file
* @param data a data for saving
*/
inline void save_file(const std::string &/*path*/, const std::string &/*data*/) {}

/**
* @brief The document class.
* to work with a shape, you first need to capture it
*/
class Document : public ISubject {
public:

    Document() = default;

    /**
    * @brief subscribe
    * @param observer a view
    */
    void attach(IObserver *observer) override {
        observers_.push_back(observer);
    }

    /**
    * @brief unsubscribe
    * @param observer a view
    */
    void detach(IObserver *observer) override {
        observers_.remove(observer);
    }


    /**
    * @brief Serialize document.
    * @param coordinates a displacement direction
    */
    std::string serialize() {
        return {};
    }

    /**
    * @brief Deserialize document
    * @param data a data of document
    */
    void deserialize(const std::string &data);

    /**
    * @brief Add a new shape
    * @param shape pointer to new shape
    */
    void push_shape(std::shared_ptr<IShape> shape) {
        shapes_.push_back(shape);
        capture_shape_ = (--shapes_.end());
        notify();
    }

    /**
    * @brief Try to capture the shape. return true on success
    * @param coordinates a displacement direction
    */
    bool capture_shape(const Point &/*coordinates*/) {
        return true;
    }

    /**
    * @brief Move a captured shape
    * @param coordinates a displacement direction
    */
    void move_shape(const Point &coordinates) {
        capture_shape_->get()->move(coordinates);
        notify();
    }

    /**
    * @brief Repaint a captured shape
    * @param coordinates an RGB color
    */
    void repaint_shape(const Color color) {
        capture_shape_->get()->set_color(color);
        notify();
    }

    /**
    * @brief Resize a captured shape
    * @param coefficient a shape scaling factor
    */
    void resize_shape(double coefficient) {
        capture_shape_->get()->resize(coefficient);
        notify();
    }

    /**
    * @brief Remove a captured shape
    */
    void remove_shape() {
        capture_shape_ = shapes_.erase(capture_shape_);
        repaint_all();
    }

private:

    /**
    * @brief notify view
    */
    void notify() override {
        for (const auto &it: observers_) {
            it->update(*capture_shape_);
        }
    }

    /**
    * @brief Repaint all shapes
    */
    void repaint_all() {
        auto tmp = capture_shape_;
        for (auto it = shapes_.cbegin(); it != shapes_.cend(); ++it) {
            notify();
        }
        capture_shape_ = tmp;
    }

    std::deque<std::shared_ptr<IShape>> shapes_;
    std::deque<std::shared_ptr<IShape>>::iterator capture_shape_;
    std::list<IObserver *> observers_;
};