#ifndef PRIORITYCOMPONENTMANAGER_H_
#define PRIORITYCOMPONENTMANAGER_H_

#include "ComponentManager.h"

#include "hash_map"
#include "map"


class PriorityComponentManager;


class PriorityComponentManagerIterator
{
	friend class PriorityComponentManager;

public:
	PriorityComponentManagerIterator();
	virtual ~PriorityComponentManagerIterator();

	bool operator ==(const PriorityComponentManagerIterator & i) const;
	bool operator !=(const PriorityComponentManagerIterator & i) const;

	Component * operator *();
	Component * * operator ->();

	PriorityComponentManagerIterator & operator ++();
	PriorityComponentManagerIterator & operator ++(int unused);

private:
	PriorityComponentManagerIterator(PriorityComponentManager * manager,const bool & isBeginIterator);

private:
	PriorityComponentManager * manager;
	std::multimap<unsigned int, unsigned int>::iterator iterator;
};


class ConstPriorityComponentManagerIterator
{
	friend class PriorityComponentManager;

public:
	ConstPriorityComponentManagerIterator();
	virtual ~ConstPriorityComponentManagerIterator();

	bool operator ==(const ConstPriorityComponentManagerIterator & i) const;
	bool operator !=(const ConstPriorityComponentManagerIterator & i) const;

	const Component * operator *();
	Component * const * operator ->();

	ConstPriorityComponentManagerIterator & operator ++();
	ConstPriorityComponentManagerIterator & operator ++(int unused);

private:
	ConstPriorityComponentManagerIterator(const PriorityComponentManager * manager,const bool & isBeginIterator);

private:
	const PriorityComponentManager * manager;
	std::multimap<unsigned int, unsigned int>::const_iterator iterator;
};


/**
 * La clase PriorityComponentManager es un gestor de componentes del juego que
 * permite asociar a los mismos una prioridad que será tenida en cuenta al
 * momento actualizar los mismos.
 *
* @see ComponentManager
 */
class PriorityComponentManager : public ComponentManager
{
	friend class PriorityComponentManagerIterator;
	friend class ConstPriorityComponentManagerIterator;

public:
	typedef PriorityComponentManagerIterator iterator;
	typedef ConstPriorityComponentManagerIterator const_iterator;

	static const unsigned int DEFAULT_PRIORITY;

public:
	PriorityComponentManager();

	virtual ~PriorityComponentManager();

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

	void add(Component * component, unsigned int priority = DEFAULT_PRIORITY);

	void remove(iterator component);

	void remove(unsigned int id);

	void update(unsigned int time, bool deleteInactive = true);

private:
	std::multimap<unsigned int, unsigned int> componentIndex;
	std::hash_map<unsigned int, unsigned int> priorityIndex;
};

#endif /*PRIORITYCOMPONENTMANAGER_H_*/
