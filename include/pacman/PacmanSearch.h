#ifndef PACMANSEARCH_H_
#define PACMANSEARCH_H_

#include "Action.h"
#include "Game.h"


// Tipo que define la interfaz general de las funciones de evaluación heurísticas

typedef unsigned int (*HeuristicEvaluation)(const Game * game);

// Interfaz general de la clase que implementa los algoritmos de búsqueda parcial

class PacmanPathfinder
{
public:
	PacmanPathfinder()
	{
		h = 0;
		maxDepth = 0;
	}

	virtual ~PacmanPathfinder()
	{
	}

	void setHeuristicEvaluation(HeuristicEvaluation h)
	{
		this->h = h;
	}

	void setMaxDepth(unsigned int maxDepth)
	{
		this->maxDepth = maxDepth;
	}

	virtual PacmanPathfinder * newInstance(Game * newGame) const = 0;

	virtual bool isGameOver() const = 0;

	virtual Action::Type processCycle() = 0;

protected:
	HeuristicEvaluation h;
	unsigned int maxDepth;
};


#endif /* PACMANSEARCH_H_ */
