#ifndef ACTION_H_
#define ACTION_H_

#include "Observer.h"

#include "string"


class LogicObject;

/**
 * La clase Action representa la parte de la lógica del juego relacionada con
 * los procesos y reglas, bajo los cuales los elementos del juego u objetos
 * lógicos modifican su estado y el de su entorno.
 * @see LogicObject
 */
class Action : Observer
{
public:

	/**
     * Tipo de datos correspondiente a las clases o tipos asociados a las
     * acciones, utilizado para distinguir las diversas configuraciones
     * de las mismas, existentes en tiempo de ejecución.
	 */
    class Type {
		public:
			Type();
			Type(const Type & other);

			Type(const std::string & s);
			Type(const char * s);

			virtual ~Type();

			Type & operator = (const std::string & s);

			bool operator == (const Type & other) const;

			bool operator != (const Type & other) const;

			bool operator < (const Type & other) const;

			std::string toString() const;

		private:
			std::string type;
    };

	static const Type NoAction;

public:
	Action(const Type & type, unsigned int cycles);

	Action(const Action & other);

    virtual ~Action();

    virtual Action * newInstance() const = 0;

    virtual Action & operator = (const Action & other);

    virtual bool operator == (const Action & other) const;

    bool operator != (const Action & other) const;

    Type getType() const;

    virtual bool canPerform() const = 0;

    unsigned int getCycles() const;

    unsigned int getCurrentCycle() const;

    bool isCompleted() const;

    virtual void setObject(LogicObject * obj);

    void update();

    virtual void finish();

protected:
    virtual void processCycle() = 0;

    virtual void onProcessChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint);

protected:
    Type type;
    unsigned int cycles;
    unsigned int currentCycle;

    LogicObject * obj;
};


std::ostream & operator << (std::ostream & output, const Action::Type & type);

std::ostream & operator << (std::ostream & output, const Action & action);


class NoAction : public Action
{
public:
	NoAction(const Type & type);

	NoAction(const NoAction & other);

	virtual ~NoAction();

	Action * newInstance() const;

    virtual Action & operator = (const Action & other);

    bool canPerform() const;

protected:
    void processCycle();
};

#endif /*ACTION_H_*/
