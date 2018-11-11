//
// Created by Benoît - Xavier HOUVET on 16/03/2017.
//

#ifndef C_IOBSERVABLE_HH
#define C_IOBSERVABLE_HH

#include <list>
#include "IObserver.hh"

class IObservable {
public:
    IObservable(){}
    virtual ~IObservable() {}
    virtual void AddObserver(IObserver *obs) = 0;
    virtual void RemoveObserver(IObserver *obs) = 0;
    std::list<IObserver *> observers;
};

#endif //C_IOBSERVABLE_HH

