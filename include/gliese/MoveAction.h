#ifndef MOVEACTION_H_
#define MOVEACTION_H_


#include "Action.h"

#include "iostream"


class MoveAction : public Action
{
	friend std::ostream & operator << (std::ostream & output, const MoveAction & action);

public:
	static const Type MoveUp;
	static const Type MoveDown;
	static const Type MoveLeft;
	static const Type MoveRight;

public:
	MoveAction(const Type & type, unsigned int cycles, unsigned int distance);

	MoveAction(const MoveAction & other);

	virtual ~MoveAction();

	virtual Action & operator = (const Action & other);

	virtual Action * newInstance() const;

	virtual bool operator == (const Action & other) const;

	virtual bool canPerform() const;

	virtual void setObject(LogicObject * obj);

	// Se devuelve 0, 1 o -1 para indicar el desplazamiento en cada eje
	virtual int getXDirection() const;
	virtual int getYDirection() const;

	// La distancia que se va a desplazar en total
	virtual unsigned int getDistance() const;

protected:
	virtual void processCycle();

	virtual void onProcessChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint);

protected:
	int dx, dy;
	int origX, origY;
	unsigned int distance;
};


std::ostream & operator << (std::ostream & output, const MoveAction & action);


#endif // MOVEACTION_H_
