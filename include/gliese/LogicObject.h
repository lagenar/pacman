#ifndef LOGICOBJECT_H_
#define LOGICOBJECT_H_

#include "Action.h"
#include "Component.h"
#include "Shape.h"
#include "Variables.h"

#include "list"
#include "map"
#include "string"


class Game;

/**
 * La clase LogicObject representa a todos los objetos que forman parte de la
 * lógica de un juego.
 *
 * Las características principales de los objetos lógicos
 * son:
 * - El tipo o clase, el cual representa configuraciones de objetos lógicos que
 * se desea clasificar, para poder asociar diversas representaciones visuales,
 * aplicar reglas de juego y asociar controladores para su comportamiento.
 * - Las acciones que puede realizar, las cuales encapsulan las porciones de la
 * lógica del juego a través de la cual se modifican los atributos de un objeto
 * y su entorno.
 * - Su forma y coordenadas en el espacio de juego.
 */
class LogicObject : public Component
{
public:
    typedef std::list<const Action *> Actions;

    static const Action::Type NOACTION;

    static const NotifyPoint PERFORMACTION;
    static const NotifyPoint FINISHACTION;

public:
    LogicObject(const Type & type, Shape * shape);

    LogicObject(const LogicObject & other);

    virtual ~LogicObject();

    /**
     * Devuelve un objeto lógico nuevo con una configuración idéntica al
     * original.
     *
     * El objeto resultante tendrá los mismo valores para sus atributos
     * principales de tipo, forma, estado de activo y configuración de las
     * acciones (exceptuando el ID y las referencias a los observadores y los
     * objetos observados).
     * @return un clon del objeto.
     */
    virtual Component * newInstance() const;

    /**
     * Operator de asignación.
     *
     * Configura el estado del objeto para reflejar la configuración exacta
     * del objeto indicado (excepto por el id y las referencias a los
     * observadores y los objetos observados).
     * @param other objeto del cual se copiará el estado.
     * @return
     */
    virtual Component & operator = (const Component & other);

    /**
     * Operador de comparación de igualdad entre objetos lógicos.
     *
     * Dos objetos lógicos se consideran iguales si coinciden en los valores de
     * sus atributos principales: tipo, forma, estado de activo y configuración
     * de las acciones.
     * @param other objeto lógico.
     * @return true si los objetos son iguales, false en caso contrario.
     */
    virtual bool operator == (const Component & other) const;

    /**
     * Devuelve la forma o figura que representa la posición y dimensiones del
     * objeto lógico.
     * @return la forma del objeto.
     */
    const Shape * getShape() const;

    /**
     * Devuelve los identificadores de las acciones que puede realizar el
     * objeto lógico en un momento determinado.
     *
     * Hay que tener en cuenta que la lista incluye las acciones disponibles,
     * y que antes de realizarlas hay que verificar si efectivamente se pueden
     * ejecutar utilizando el método canPerform.
     * @param actions las acciones que puede realizar el objeto.
     * @see canPerform
     * @see performAction
     */
    void getActions(std::list<Action::Type> & actions) const;

    /**
     * Verifica si el objeto lógico cuenta con la acción indicada.
     *
     * Esto es, el método verifica que el objeto haya sido configurado con la
     * acción a través del método addAction.
     * @param actionType tipo de la acción que se quiere verificar
     * @return true si el objeto tiene la acción, false en caso contrario.
     * @see addAction
     */
    bool hasAction(const Action::Type & actionType) const;

    /**
     * Devuelve el objeto correspondiente al tipo de la acción indicado.
     * @param actionType tipo de la acción.
     * @return acción constante si el objeto fue configurado previamente
     * con la misma, o NULL en caso contrario.
     * @see addAction
     */
    const Action * getAction(const Action::Type & actionType) const;

    /**
     * Devuelve el objeto correspondiente al tipo de la acción indicado.
     * @param actionType tipo de la acción.
     * @return acción si el objeto fue configurado previamente
     * con la misma, o NULL en caso contrario.
     * @see addAction
     */
    Action * getAction(const Action::Type & actionType);

    /**
     * Verifica si el objeto lógico se encuentra en condiciones de ejecutar la
     * acción indicada en el contexto del juego actual.
     * @param actionType tipo de la acción.
     * @return true si es posible comenzar a realizar la acción en forma
     * inmediata, false en caso contrario.
     */
    bool canPerform(const Action::Type & actionType) const;

    /**
     * Devuelve la forma o figura utilizada para representar las dimensiones
     * y la ubicación del objeto lógico en el espacio de juego.
     * @return figura asociada al objeto.
     */
    Shape * getShape();

    /**
     * Configura la forma o figura utilizada para representar las dimensiones
     * y la ubicación del objeto lógico en el espacio de juego.
     * @param shape figura asociada al objeto.
     */
    void setShape(Shape * shape);

    /**
     * Devuelve la acción que se encuentra realizando
     * el objeto lógico en un momento determinado.
     * @return acción asociada al objeto.
     */
    const Action * getCurrentAction() const;

    /**
     * Añade a la configuración del objeto una acción que podrá ejecutar y
     * gestiones a través del tipo asociado a la misma (Action::Type).
     * @param action
     */
    void addAction(Action * action);

    /**
     * Elimina de la configuración del objeto la acción indicada.
     * @param actionType tipo de la acción.
     */
    void removeAction(const Action::Type & actionType);

    /**
     * Ejecuta la acción indicada.
     *
     * Es a través de este método que el objeto lógico lleva a cabo las
     * acciones que modificaran su estado y le permitirán  interactuar con su
     * entorno según lo permitan las reglas del juego.
     *
     * La acción indicada debe haber sido agregada a las acciones posibles
     * previamente, a través del método addAction.
     *
     * Antes de ejecutar las acciones es necesario verificar si las mismas
     * pueden realizar en el estado del juego actual, utilizando el método
     * canPerform.
     *
     * @param actionType
     * @see addAction
     * @see canPerform
     */
    virtual void performAction(const Action::Type & actionType);

    /**
     * Configura la acción que debe realizar el objeto lógico por defecto, cuando
     * no se le indica que realice una acción determinada.
     * @param defaultActionType tipo de la acción por defecto.
     */
    void setDefaultActionType(const Action::Type & defaultActionType);

    /**
     * Devuelve el tipo de acción que el objeto lógico debe realizar por defecto,
     * cuando no se le indica que realice una acción determinada.
     * @return referencia constante al tipo de acción por defecto.
     */
    const Action::Type & getDefaultActionType() const;

    template <typename Any> void setAttribute(unsigned int id, const Any & att)
    {
    	attributes.set(id, att);
    }

    template <typename Any> bool getAttribute(unsigned int id, Any & att) const
    {
    	return attributes.get(id, att);
    }

    /**
     *
     */
    virtual void destroy();

    virtual void undoDestroy();

    /**
     * Devuelve el objeto que representa al juego al cual pertenece el objeto lógico.
     * @return referencia constante al juego.
     */
    const Game * getGame() const;

    /**
     * Devuelve el objeto que representa al juego al cual pertenece el objeto lógico.
     * @return referencia al juego.
     */
    Game * getGame();

    /**
     * Configura el objeto que representa al juego, al cual pertenece el objeto lógico.
     * @return referencia al juego.
     */
    void setGame(Game * game);

    /**
     * Verifica si el objeto lógico está realizando alguna acción en el momento.
     *
     * @return true si el objeto está realizando ua acción, false en caso contrario.
     * @see addAction
     */
    bool isPerformingAction() const;

    /**
     * Configura la acción que el objeto lógico debe realizar a continuación.
     * Si el objeto estaba realizando una acción, primero se termina la misma.
     * @param actionType tipo de la acción a realizar.
     */
    void setCurrentAction(const Action::Type & actionType);

    /**
     * Devuelve una estructura que contiene los atributos
     * que tiene configurado el objeto lógico.
     * @return referencia constante a los atributos del objeto lógico.
     */
    const Variables & getAttributes() const;

    /**
     * Configura el objeto lógico con una estructura de atributos.
     * @param attributes estructura que contiene los atributos.
     */
    void setAttributes(const Variables & attributes);

protected:
    virtual void update(unsigned int time);

protected:
    typedef std::map<Action::Type, Action *> ActionsMap;

    Shape * shape;
    ActionsMap actions;
    Action * currentAction;
    Action::Type defaultActionType;
    Variables attributes;

    Game * game;
};


#include "iostream"

std::ostream & operator << (std::ostream & output, const LogicObject & obj);


#endif /*LOGICOBJECT_H_*/
