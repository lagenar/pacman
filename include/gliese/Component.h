#ifndef COMPONENT_H_
#define COMPONENT_H_

#include "Observable.h"
#include "Observer.h"

#include "set"
#include "string"


class ComponentManager;
class PriorityComponentManager;


/**
 * La clase Component representa el tipo base de todos los elementos que forman
 * parte de la lógica de un juego y que deben ser gestionados por la plataforma.
 * Muchos de los tipos de datos más importantes se derivan de este tipo básico:
 * - objetos lógicos
 * - objetos visuales
 * - procesos que representan las reglas del juego y controles lógicos
 * - manejadores de eventos
 *
 * Una de las características más importantes de los componentes lógicos es la
 * gran flexibilidad de configuración que brinda el hecho de poder vincularse,
 * en tiempo de ejecución, en forma dinámica a cualquier otro componente a
 * través de los mecanismos de comunicación provistos por las clases Observable
 * y Observer.
 *
 * @see ComponentManager
 * @see Observable
 * @see Observer
 */
class Component : public Observable, public Observer
{
	friend class ComponentManager;
	friend class PriorityComponentManager;

public:
	static const NotifyPoint DESTROY;
	static const NotifyPoint UPDATE;

public:
    /**
     * Tipo de datos correspondiente a las clases o tipos asociados a los
     * componentes, utilizado para distinguir las diversas configuraciones
     * de los mismos, existentes en tiempo de ejecución.
     */
    class Type {
		public:
			Type();
			Type(std::set<std::string> subtypes);
			Type(const std::string & type, std::set<std::string> subtypes = std::set<std::string>());
			Type(const char * type, std::set<std::string> subtypes = std::set<std::string>());
			Type(const Type & other);

			virtual ~Type();

			Type & operator = (const Type & other);

			Type & operator = (const std::string & type);

			bool operator == (const Type & other) const;

			bool operator != (const Type & other) const;

			bool operator < (const Type & other) const;

			std::string toString() const;

			std::set<std::string> getSubtypes() const;

		private:
			std::string type;
			std::set<std::string> subtypes;
    };

public:
    Component(const Type & type = "");

    Component(const Component & other);

    virtual ~Component();

    virtual Component & operator = (const Component & other);

    virtual bool operator == (const Component & other) const;

    bool operator != (const Component & other) const;

    virtual bool operator < (const Component & other) const;

    virtual Component * newInstance() const = 0;

    /**
     * Devuelve el número de identificación único del componente.
     * @return número de indetificación.
     */
    unsigned int getId() const;

    /**
     * Devuelve el tipo del componente.
     * @return tipo del component.
     * @see setType
     */
    const Type & getType() const;

    /**
     * Verifica si el objeto se encuentra activo o fue destruido a nivel
     * lógico.
     * @return true si el componente está activo, false en caso contrario.
     */
    bool isActive (void) const;

    /**
     * Lleva a cabo la destrucción lógica del objeto.
     * Este método no invoca directamente al destructor, por lo que el objeto
     * puede seguir siendo manipulado hasta el siguiente ciclo de actualización
     * del juego en el que el gestor de componentes se encargará de liberar los
     * recursos y a partir de ese momento todas las referencias al mismo se
     * invalidarán.
     * @see ComponentManager
     */
    virtual void destroy();

protected:
    virtual void update(unsigned int time) = 0;

    virtual void onProcessChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint);

private:
    static unsigned int currentId;

protected:
    const unsigned int id;
    bool active;

    Type type;
};

#endif /*COMPONENT_H_*/
