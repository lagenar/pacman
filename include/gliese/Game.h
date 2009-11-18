#ifndef GAME_H_
#define GAME_H_

#include "ApplicationState.h"
#include "LogicObject.h"
#include "Rule.h"
#include "Observer.h"
#include "PriorityComponentManager.h"
#include "GameSpace.h"

#include "iostream"
#include "list"
#include "map"


class Application;
class GameOverRule;
class GameSimulator;
class GameState;
class ScenarioBuilder;


/**
 * La clase Game representa los estados de la aplicación correspondientes
 * a la ejecución del ciclo del juego exclusivamente.
 * La característica principal de este tipo de estado es que lleva a cabo el
 * denominado "ciclo del juego" (o game loop). En el mismo, se actualizan
 * periódicamente los objetos lógicos que realizarán sus acciones, y los
 * procesos que contienen los algoritmos con las reglas del juego, el control
 * de los jugadores, etc.
 *
 */
class Game : public ApplicationState, public Observer
{
	friend std::ostream & operator << (std::ostream & output, const Game & game);
	friend class GameSimulator;

public:
	Game(const Game * otherGame, bool simulated = false);
	Game(Application * application, ScenarioBuilder * builder, bool simulated = false);

	virtual ~Game();

	const ComponentManager & getObjectManager() const;
	ComponentManager & getObjectManager();

	const ComponentManager & getStaticObjectManager() const;
	ComponentManager & getStaticObjectManager();

	const PriorityComponentManager & getRuleManager() const;
	PriorityComponentManager & getRuleManager();

	void setGameOverRule(GameOverRule * rule);
	const GameOverRule & getGameOverRule() const;
	GameOverRule & getGameOverRule();

	void addObject(LogicObject * obj, bool isStatic = true);
	void addRule(Rule * obj);

    /**
     * Devuelve los objetos que cumplan con el filtro por tipo indicado.
     * @param type tipo de los objetos
     * @param objects objetos constantes cuya posición se encuentra dentro del area indicada.
     */
    void getObjects(const LogicObject::Type & type, std::list<const LogicObject *> & objects) const;

    /**
     * Devuelve los objetos que cumplan con el filtro por tipo indicado.
     * @param type tipo de los objetos
     * @param objects objetos cuya posición se encuentra dentro del area indicada.
     */
    void getObjects(const LogicObject::Type & type, std::list<LogicObject *> & objects);

    /**
     * Devuelve el objeto correspondiente al tipo del objeto lógico indicado.
     * @param type tipo del objeto lógico.
     * @return referencia constante al objeto lógico si el mismo forma parte de
     * los objetos administrados por el juego, o NULL en caso contrario.
     */
    const LogicObject * getObject(const LogicObject::Type & type) const;

    /**
     * Devuelve el objeto correspondiente al tipo del objeto lógico indicado.
     * @param type tipo del objeto lógico.
     * @return referencia al objeto lógico si el mismo forma parte de
     * los objetos administrados por el juego, o NULL en caso contrario.
     */
    LogicObject * getObject(const LogicObject::Type & type);

    /**
     * Verifica si el juego hay sido configurado con una referencia al espacio del juego.
     *
     * @return true si el juego tiene una referencia al espacio del juego,
     * false en caso contrario.
     * @see setGameSpace
     */
    bool hasGameSpace() const;

    /**
     * Configura el juego con una referencia al espacio del juego.
     * De esta forma el juego puede brindar soporte para el acceso y utilización
     * del espacio del juego.
     *
     * @param gameSpace referencia al espacio del juego
     */
    void setGameSpace(GameSpace * gameSpace);

    /**
     * Devuelve una referencia al espacio del juego.
     *
     * @return referencia constante al espacio del juego
     * @see hasGameSpace
     */
    const GameSpace & getGameSpace() const;

    /**
     * Devuelve una referencia al espacio del juego.
     *
     * @return referencia al espacio del juego
     * @see hasGameSpace
     */
    GameSpace & getGameSpace();

    /**
     * Devuelve una estructura que contiene las variables
     * del juego.
     * @return referencia constante a las variables del juego.
     */
	const Variables & getVariables() const;

    /**
     * Devuelve una estructura que contiene las variables
     * del juego.
     * @return referencia a las variables del juego.
     */
	Variables & getVariables();

	/**
	 * Verifica si el juego se está usando para la simulación.
	 * Si el juego es simulado no se realiza ninguna operación relacionada con
	 * la visualización de las animaciones o con el manejo de los eventos de entrada.
	 *
	 * @return true si el juego es simulado, false en caso contrario.
	 */
	bool isSimulated() const;

	void setCycles(unsigned int cycles);
	const unsigned int getCycles() const;

	virtual Game * newInstance(bool simulated = false) const = 0;

	void setNextState(ApplicationState * nextState);

	virtual GameState * getState();

	virtual void gameSetup(GameSimulator * gameSimulator = 0) = 0;

protected:
	virtual void update(unsigned int time);

	virtual void onGameOver();

	virtual void onProcessChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint);

private:
	void setup();

protected:
	GameOverRule * gameOverRule;
	ScenarioBuilder * scenarioBuilder;
	ComponentManager updatableObjects;
	ComponentManager nonUpdatableObjects;
	PriorityComponentManager rules;
	Variables variables;

	bool simulated;
	GameSpace * gameSpace;

	ApplicationState * nextState;

	unsigned int cycles;
};


std::ostream & operator << (std::ostream & output, const Game & game);


#endif /*GAME_H_*/
