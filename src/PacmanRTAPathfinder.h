#ifndef PACMANRTAPATHFINDER_H_
#define PACMANRTAPATHFINDER_H_

#include "PacmanSearch.h"

#include "GameSimulator.h"

#include "list"


class PacmanRTAPathfinder : public PacmanPathfinder
{
public:
	PacmanRTAPathfinder();
	PacmanRTAPathfinder(Game * newGame);

	virtual ~PacmanRTAPathfinder();

	PacmanPathfinder * newInstance(Game * newGame) const;

	bool isGameOver() const;

	Action::Type processCycle();

private:
	Action::Type getAction(unsigned int depth, unsigned int & min, unsigned int & secondMin);

	unsigned int minimin(GameSimulator & planSim, unsigned int depth, unsigned int g);

	void pruneActions(const LogicObject * player, std::list<Action::Type> & playerActions);

	void logSolution();
	void saveSolution() const;
	void guardarValoresHeuristicas() const;

private:
	GameSimulator controlSim;
	std::list<Action::Type> solution;
	Game * simulatedGame;

	//Variables agregadas para obtener informacion
	std::list<unsigned> valores_heuristicas;
	unsigned estados_evaluados;
};


#endif /* PACMANRTAPATHFINDER_H_ */

