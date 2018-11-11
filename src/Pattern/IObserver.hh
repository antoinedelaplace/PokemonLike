//
// Created by Benoît - Xavier HOUVET on 16/03/2017.
//

#ifndef C_IOBSERVER_HH
class IObservable;

#define C_IOBSERVER_HH

class IObserver {
public:
    IObserver() {}
    virtual ~IObserver() {}
    virtual void Notify(char) = 0;
};

#endif //C_IOBSERVER_HH


