#ifndef PACMAN_H_
#define PACMAN_H_

#include "Action.h"

#include "PacmanSearch.h"

#include "iostream"
#include "list"
#include "string"

/*
 * Variables globales de la aplicación
 */

const unsigned int HEURISTICS = 1000;
const unsigned int GAME_MODE = 1001;
const unsigned int HEURISTIC_EVALUATION = 1002;
const unsigned int SEARCH_DEPTH = 1003;
const unsigned int SOLUTION_FILENAME = 1004;
const unsigned int LAST_SOLUTION_FILENAME = 1005;
const unsigned int EXIT_MODE = 1006;
const unsigned int PATHFINDER = 1007;

/*
 * Modos del juego
 */

const unsigned int MANUAL_MODE = 0;
const unsigned int OFFLINE_SIMULATION_MODE = 1;
const unsigned int ONLINE_SIMULATION_MODE = 2;
const unsigned int SOLUTION_REPLAY_MODE = 3;
const unsigned int LAST_SOLUTION_REPLAY_MODE = 4;

/*
 * Variables globales del juego
 */

const unsigned int DOT_COUNT = 1001;
const unsigned int DESTROYED_DOTS = 1002;
const unsigned int SCATTERED_MODE = 1003;

/*
 * Elementos del juego.
 */

const std::string PACMAN = "Pacman";
const std::string DOT = "Dot";
const std::string BLINKY = "Blinky";
const std::string PINKY = "Pinky";
const std::string INKY = "Inky";
const std::string CLYDE = "Clyde";
// Subtipo utilizado para identificar a los fantasmas.
const std::string GHOST = "Ghost";
// Subtipo utilizado para identificar a las paredes que componen el laberinto.
const std::string WALL = "Wall";

/*
 * Atributos de los personajes del juego.
 */

const unsigned int DIRECTION = 1000;
const unsigned int INSIDE_HOUSE = 1001;

// Posibles direcciones de los personajes del juego.
typedef enum {UP, DOWN, LEFT, RIGHT} Direction;


template <typename Any> std::ostream & operator << (std::ostream & output, const std::list<Any> & l)
{
	output << "{ " ;
	typename std::list<Any>::const_iterator it = l.begin();
	if (it != l.end()) {
		output << *it;
		it++;
	}
	while (it != l.end()) {
		output << ", " << *it;
		it++;

	}
	output << " }" ;
	return output;
}


// Funciones de acceso a los parámetros del juego configurados al inicio y a través de los menús de opciones

unsigned int getMode();
unsigned int getDepth();
HeuristicEvaluation getHeuristEvaluation();
std::string getHeuristEvaluationName();
std::string getSolutionFilename();
std::string getLastSolutionFilename();
const PacmanPathfinder * getPathfinder();

void setLastSolutionFilename(std::string lastSolutionFilename);


template <typename Any> std::ostream & operator << (std::ostream & output, const std::vector<Any> & l)
{
	output << "{ " ;
	typename std::vector<Any>::const_iterator it = l.begin();
	if (it != l.end()) {
		output << *it;
		it++;
	}
	while (it != l.end()) {
		output << ", " << *it;
		it++;

	}
	output << " }" ;
	return output;
}


#endif /* PACMAN_H_ */
