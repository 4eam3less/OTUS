#pragma once

#include <list>

class IObserver {
public:
    virtual ~IObserver() = default;

    virtual void update(std::shared_ptr<IShape> shape) = 0;
};


class ISubject {
public:

    virtual ~ISubject() = default;

    virtual void attach(IObserver *observer) = 0;

    virtual void detach(IObserver *observer) = 0;

    virtual void notify() = 0;
};
