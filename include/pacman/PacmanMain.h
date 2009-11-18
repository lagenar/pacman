#ifndef PACMANMAIN_H_
#define PACMANMAIN_H_

#include "PacmanSearch.h"

#include "string"
#include "vector"


// Función de inicialización de la aplicación

void runPacman(PacmanPathfinder * pathfinder,
			   const std::vector<std::pair<HeuristicEvaluation, std::string> > & heuristics,
			   std::string solutionFile = "");


ApplicationState * buildModeMenu(Application * app);

std::ostream & operator << (std::ostream & output, const std::pair<HeuristicEvaluation, std::string> & heuristic);


#endif /* PACMANMAIN_H_ */
