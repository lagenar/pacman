#ifndef GAMESIMULATOR_H_
#define GAMESIMULATOR_H_

#include "Game.h"
#include "GameSpace.h"
#include "GameState.h"
#include "LogicObject.h"
#include "Rule.h"

#include "TranspositionTable.h"

#include "list"
#include "hash_map"


/**
 * La clase GameSimulator permite simular un juego, proveyendo facilidades
 * para la gestión de los estados por los cuales atraviesa el mismo.
 * El simulador es el encargado de actualizar todos los procesos que involucra
 * un juego de modo que sea posible:
 * - Avanzar el estado del juego hasta que nos toque el turno nuevamente.
 * - Posibilitar continuar la simulación desde cualquier estado que se haya
 * generado anteriormente.
 * - Deshacer los cambios realizados sobre un estado del juego, retornando a
 * una configuración previa.
 *
 * @see update
 * @see setState
 * @see undoUpdate
 */
class GameSimulator : public Observer
{
public:
    typedef std::string GameOverResult;

	class SimulatorController;

public:
    static const GameOverResult WIN;
    static const GameOverResult LOSE;
    static const GameOverResult DRAW;

public:
    GameSimulator();

    virtual ~GameSimulator();

    /**
     * Verifica si el juego terminó.
     * @return true si el juego finalizó, o false en caso contrario.
     */
    bool isGameOver() const;

    /**
     * Devuelve el estado de finalización del juego.
     * El estado de finalización puede ser:
     *  - GameSimulator::WIN: el jugador que controlamos ganó
     *  - GameSimulator::LOSE el jugador que controlamos perdió
     *  - GameSimulator::DRAW: el jugador que controlamos empató
     * @return el estado de finalización del juego.
     */
    GameOverResult getGameOverResult() const;

    /**
     * Devuelve el estado actual de la simulación
     * @return referencia constante al estado actual.
     */
    const GameState * getCurrentState() const;

    /**
     * Verifica si un estado de simulación dado ya fue visitado.
     * Un estado se considera visitado si fue previamente marcado como tal, a
     * través del método addVisited.
     * @param state el estado a verificar.
     * @return true si el estado ya fue visitado, false en caso contrario.
     * @see addVisited
     */
    unsigned int getVisited(const GameState * state) const;

    /**
     * Realiza todos los procesos de actualización del juego necesarios para
     * procesar las acciones del jugador controlado, hasta que le toque el turno
     * nuevamente. En dicho ciclo de actualización, se pasa el turno del jugador
     * controlado ejecutando efectivamente las acciones que se indicaron a
     * través del método performAction y luego se simula el turno de los demás
     * jugadores hasta que se le otorga el turno nuevamente a nuestro jugador.
     * @return estado del juego luego de la actualización.
     * @see LogicObject::performAction
     */
    const GameState * update();

    /**
     * Revierte la última actualización del juego realizada utilizando los
     * métodos update o setState.
     * @see update
     * @see setState
     */
    void undoUpdate();

    /**
     * Lleva al estado actual de la simulación a una configuración idéntica a
     * la del estado indicado.
     * @param state estado cuya configuración se convertirá en el estado
     * actual.
     */
    void setState(const GameState * state);

    /**
     * Marca como visitado el estado de simulación indicado.
     * A partir del momento en el que se marca como visitado un estado, el
     * método isVisited dará una respuesta positiva cada vez que se lo invoque
     * pasándole una referencia a un estado con una configuración similar.
     * @param state el estado a marcar.
     * @see isVisited
     * @see State::operator==
     */
    void addVisited(const GameState * state);

    /**
     * Determina el objeto lógico que representa al jugador que
     * controlamos.
     * @param player la referencia al jugador.
     */
    void setPlayer(LogicObject * player);

    /**
     * Devuelve una referencia al objeto lógico que representa al jugador que
     * controlamos.
     * @return la referencia al jugador.
     */
    LogicObject * getPlayer(); //TODO: reemplazandolo por getLogicObject se puede
    //armar uno GameSimulator Genérico.

    /**
     * Configura el objeto que representa al juego.
     * El simulador construirá su estado inicial a partir del estado actual del juego.
     * @param game objeto que representa al juego.
     */
    void setGame(Game * game);

    /**
     * Devuelve el objeto que representa al juego, en base al cual se configuró el simulador.
     * @return referencia al juego.
     */
    Game * getGame();

    void clear();

	void setSimulatorController(SimulatorController * controller);
	SimulatorController * getSimulatorController();

    /**
     * Devuelve los estados que fueron visitados durante la simulación.
     * @return lista constantes de estados visitados.
     */
	const TranspositionTable & getVisitedStates() const;

    /**
     * Devuelve los estados que fueron generados durante la simulación.
     * @return lista constantes de estados generados.
     */
	const std::list<GameState *> & getGeneratedStates() const;

	bool isInPath(const GameState * state) const;

	void setStateValue(unsigned int stateId, unsigned int value);
	
	unsigned int getStateValue(unsigned int stateId) const;

protected:
    void onProcessChange(const Observable * observable, const Observable::NotifyPoint & notifyPoint);

public:
    class SimulatorController : public Rule
    {
    	friend class GameSimulator;

    public:
    	SimulatorController();
    	SimulatorController(const SimulatorController & other);
    	~SimulatorController();
    	Component * newInstance() const;
    	Component & operator = (const Component & other);

    private:
    	void onUpdate(unsigned int time);
    	void finishTurn();
    };

protected:
    Game * game;

    bool processPlayerTurns;
    std::list<GameState *> generatedStates;
    std::list<GameState *> previousStates;
    TranspositionTable visitedStates;
    LogicObject * player;
    SimulatorController * simulatorController;
    typedef std::hash_map<unsigned int, unsigned int> StateValues;
    StateValues stateValues;
};


#endif /* GAMESIMULATOR_H_ */
