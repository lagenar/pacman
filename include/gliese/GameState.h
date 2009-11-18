#ifndef GAMESTATE_H_
#define GAMESTATE_H_

#include "Game.h"

#include "iostream"
#include "map"


class PacmanGame;
class GameSimulator;
class PacmanGameSimulator;
class MazeGame;

class PacmanGameState;

/**
 * La clase State representa los estados del juego en momentos específicos del mismo.
 * Un estado es la configuración completa del juego en un momento dado.
 * El mismo contiene la información de todos los objetos lógicos con el estado de cada unos
 * de sus atributos y las acciones que se encuentran realizando,
 * así como el estado de los jugadores, la asignación de turnos y demás.
 */
class GameState
{
	friend std::ostream & operator << (std::ostream & output, const GameState & state);

private:
	static unsigned int currentId;

public:
	GameState();
	virtual ~GameState();

	unsigned int getId() const;

	/**
	 * Operador de comparación de igualdad entre estados.
	 * Dos estados se consideran iguales si el estado de los atributos de
	 * todos los objetos lógicos que lo componen es similar. Además otros
	 * aspectos de la configuración como la asignación de los turnos y
	 * demás deber ser iguales.
	 * @param other estado de simulación.
	 * @return true si los estados son iguales, false en caso contrario.
	 */
	virtual bool operator == (const GameState & other) const = 0;

	virtual void setTo(Game * game) const = 0;
	virtual void setFrom(const Game * game) = 0;

	virtual unsigned int hash() const;

	virtual std::string toString() const = 0;

private:
	unsigned int id;
};


std::ostream & operator << (std::ostream & output, const GameState & state);


#endif // GAMESTATE_H_
