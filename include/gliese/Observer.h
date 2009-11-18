#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "Observable.h"

#include "list"


/**
 * La clase Observer provee el mecanismo para que un objeto pueda vincularse a
 * otros objetos denominados observados, en forma dinámica, y ser informado de
 * los cambios de estado de los mismos.
 *
 * @see Observable
 */
class Observer
{
    friend class Observable;

public:
    Observer();

    Observer(const Observer & other);

    virtual ~Observer();

    Observer & operator = (const Observer & other);

protected:
    void processChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint);

    virtual void onProcessChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint) = 0;

protected:
    std::list<Observable *> references;
};

#endif /*OBSERVER_H_*/
