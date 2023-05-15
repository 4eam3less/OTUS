#pragma once

#include <list>

class IObserver {
public:
    virtual ~IObserver() {};

    virtual void update() = 0;
};


class ISubject {
public:

    virtual void attach(IObserver *observer) = 0;

    virtual void detach(IObserver *observer) = 0;

    virtual void notify() = 0;
};
