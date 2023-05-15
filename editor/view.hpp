#pragma once

#include "observer.hpp"
#include "document.hpp"

class View : public IObserver {
public:
    void update() override;

    void redraw();
    
private:
    std::list<Document> documents_;
};