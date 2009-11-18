#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include "Component.h"

#include "hash_map"
#include "map"
#include "string"


#include "iostream"
#include "typeinfo"


/**
 * La clase ComponentManager representa a los contenedores de componentes
 * lógicos utilizados por la plataforma para gestionar los recursos.
 *
 * Este tipo de gestor de recursos se basa principalmente en la
 * manipulación de los recursos a través de su identificador único. Una de las
 * funciones más importantes que realiza, es la de actualización de los
 * componentes, supervisando el estado de los mismos y liberándolos a medida que
 * resulte necesario, facilitando ese aspecto de la gestión de los recursos del
 * juego.
 *
 * @see Component
 */

class ComponentManagerIterator;
class ConstComponentManagerIterator;

class ComponentManager
{
	friend class ComponentManagerIterator;
	friend class ConstComponentManagerIterator;

public:
    typedef ComponentManagerIterator iterator;
    typedef ConstComponentManagerIterator const_iterator;

public:
    ComponentManager();
    virtual ~ComponentManager();

    /*
     * TODO: Implementar los operadores de comparación aprovechando los comparadores de la STL (map, set, list...)
     */

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    virtual unsigned int size() const;

    virtual const Component * get(unsigned int id) const;

    virtual Component * get(unsigned int id);

    virtual void get(const Component::Type & type, std::list<unsigned int> & componentIds) const;

    virtual const Component * get(const Component::Type & type) const;
    virtual Component * get(const Component::Type & type);

    virtual void add(Component * component);

    virtual void remove(unsigned int id);

    virtual void remove(iterator component);

    virtual void update(unsigned int time, bool deleteInactive = true);

    virtual void clear();

protected:
    typedef std::hash_map<unsigned int, Component *> ComponentMap;
    typedef std::list<unsigned int> IdList;
    typedef std::map<Component::Type, IdList> TypeIndex;

    ComponentMap components;
    TypeIndex typeIndex;
};


class ComponentManagerIterator
{
    friend class ComponentManager;

public:
    ComponentManagerIterator();
    virtual ~ComponentManagerIterator();

    bool operator == (const ComponentManagerIterator & i) const;
    bool operator != (const ComponentManagerIterator & i) const;

    Component * operator * ();
    Component * * operator -> ();

    ComponentManagerIterator & operator ++ ();
    ComponentManagerIterator & operator ++ (int unused);

private:
    ComponentManagerIterator(ComponentManager * manager, bool isBeginIterator);

private:
	ComponentManager * manager;
	ComponentManager::ComponentMap::iterator iterator;
};


class ConstComponentManagerIterator
{
    friend class ComponentManager;

public:
    ConstComponentManagerIterator();
    virtual ~ConstComponentManagerIterator();

    bool operator == (const ConstComponentManagerIterator & i) const;
    bool operator != (const ConstComponentManagerIterator & i) const;

    const Component * operator * ();
    Component * const * operator -> ();

    ConstComponentManagerIterator & operator ++ ();
    ConstComponentManagerIterator & operator ++ (int unused);

private:
    ConstComponentManagerIterator(const ComponentManager * manager, bool isBeginIterator);

private:
	const ComponentManager * manager;
	ComponentManager::ComponentMap::const_iterator iterator;
};


#endif /*COMPONENTMANAGER_H_*/
