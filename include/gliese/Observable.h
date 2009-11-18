#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "list"
#include "string"


class Observer;


/**
 * La clase Observable provee el mecanismo para que el estado de un objeto
 * pueda ser supervisado por otros llamados observadores.
 * @see Observer
 */
class Observable
{
public:
	typedef std::string NotifyPoint;

public:
    Observable();

    Observable(const Observable & other);

    virtual ~Observable();

    Observable & operator = (const Observable & other);

    void addObserver(Observer * observer);

    void removeObserver(Observer * observer);

    void notifyAll(const NotifyPoint & notifyPoint);

private:
    std::list<Observer *> observers;
};

#endif /*OBSERVABLE_H_*/
