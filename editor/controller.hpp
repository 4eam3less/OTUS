#pragma once

#include "document.hpp"
#include "observer.hpp"
#include "factory.hpp"

class ModelDocuments : public ISubject {
public:

    void attach(IObserver *observer) override {
        observers_.push_back(observer);
    }

    void detach(IObserver *observer) override {
        observers_.remove(observer);
    }

    void notify() override {
        for (const auto &it: observers_) {
            it->update();
        }
    }

    void create_document(const std::string &name);

    void erase_document();

    void load_document(const std::string &path) {
        std::unique_ptr<Memento> snapshot = load(path);
        documents_.restore(std::move(snapshot));
    }

    void save_document(const std::string &path) {
        save(documents_.snapshot(), path + name_);
    }

    template<typename ... Args>
    void insert_shape(Shapes shape, Args ... args) {
        Factory f;
        auto res = f.create(shape, std::forward<Args>(args)...);
        documents_.insert_shape(res);
    }

private:

    std::list<IObserver *> observers_;
    Document documents_;
    std::string name_;
};

class Controller {
public:
    void create(const std::string &name) {
        model_.create_document(name);
    }

    void erase() {
        model_.erase_document();
    }

    void load(const std::string &path) {
        model_.load_document(path);
    }

    void save(const std::string &path) {
        model_.save_document(path);
    }

    template<typename ... Args>
    void insert_shape(Shapes shape, Args ... args) {
        model_.insert_shape(shape, std::forward<Args>(args)...);
    }

    void remove_shape();

    void move_shape();

    void repaint_shape();


private:
    ModelDocuments model_;
};