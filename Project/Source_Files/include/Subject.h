#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"

class Subject{
public:
    virtual void registerObserver(Observer*) = 0;
    virtual void removeObserver(Observer*) = 0;

protected:
    virtual void updateObservers() = 0;
};

#endif