#pragma once

#include <memory>

/**
 * @brief The interface class observer
 * */
class IObserver {
public:
    virtual ~IObserver() = default;

    /**
    * @brief This function is called by the ISubject when the event occurs.
    * @param shape a modified figure
    */
    virtual void update(std::shared_ptr<IShape> shape) = 0;
};

/**
* @brief The interface class subject
*/
class ISubject {
public:

    virtual ~ISubject() = default;

    /**
    * @brief Subscription management: subscribe
    * @param observer a observer
    */
    virtual void attach(IObserver *observer) = 0;

    /**
    * @brief Subscription management: unsubscribe
    * @param observer a observer
    */
    virtual void detach(IObserver *observer) = 0;

    /**
    * @brief Send notification
    */
    virtual void notify() = 0;
};
