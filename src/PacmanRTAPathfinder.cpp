#include "PacmanRTAPathfinder.h"

#include "Pacman.h"
#include "PacmanActions.h"

#include "climits"
#include "ctime"
#include "fstream"
#include "sstream"

using namespace std;


const unsigned int MAX_F = UINT_MAX;
const unsigned int LOSE_VALUE = MAX_F - 1;


PacmanRTAPathfinder::PacmanRTAPathfinder()
{
	simulatedGame = 0;
}

PacmanRTAPathfinder::PacmanRTAPathfinder(Game * newGame)
{
	simulatedGame = newGame;
	simulatedGame->gameSetup(&controlSim);
	controlSim.setGame(simulatedGame);

	controlSim.setPlayer(simulatedGame->getObject(PACMAN));

	controlSim.addVisited(controlSim.getCurrentState());
}

PacmanRTAPathfinder::~PacmanRTAPathfinder()
{
	delete simulatedGame;
}

PacmanPathfinder * PacmanRTAPathfinder::newInstance(Game * newGame) const
{
	return new PacmanRTAPathfinder(newGame);
}

bool PacmanRTAPathfinder::isGameOver() const
{
	return controlSim.isGameOver();
}

Action::Type PacmanRTAPathfinder::processCycle()
{
	assert(controlSim.getGame() != 0);

	unsigned int bestF, secondBestF;

	Action::Type bestAction = getAction(maxDepth, bestF, secondBestF);

	if (bestF >= LOSE_VALUE) {
		bestAction = getAction(1, bestF, secondBestF);
	}

	if (secondBestF >= LOSE_VALUE) {
		secondBestF = bestF;
	}

	const GameState * controlState = controlSim.getCurrentState();

	unsigned int visitedId = controlSim.getVisited(controlState);
	if (visitedId == 0) {
		controlSim.addVisited(controlState);
		controlSim.setStateValue(controlState->getId(), secondBestF + 1);
	} else {
		controlSim.setStateValue(visitedId, secondBestF + 1);
	}

    valores_heuristicas.push_back(secondBestF + 1);

	controlSim.getPlayer()->performAction(bestAction);
	controlSim.update();

	solution.push_back(bestAction);

	if (isGameOver()) {
		logSolution();
		saveSolution();
		guardarValoresHeuristicas();
	} else if (getMode() == OFFLINE_SIMULATION_MODE) {
		if (solution.size() % 50  == 0)
			cout << ".\n";
		else
			cout << ".";
		cout.flush();
	}

	return bestAction;
}

Action::Type PacmanRTAPathfinder::getAction(unsigned int depth, unsigned int & bestF, unsigned int & secondBestF)
{
	GameSimulator planSim;
	planSim.setGame(controlSim.getGame());
	planSim.setPlayer(controlSim.getPlayer());
	planSim.setSimulatorController(controlSim.getSimulatorController());

	LogicObject * player = planSim.getPlayer();
	list<Action::Type> playerActions;
	player->getActions(playerActions);

	bestF = MAX_F;
	secondBestF = MAX_F;
	Action::Type bestAction = player->getDefaultActionType();

	list<Action::Type>::iterator action = playerActions.begin();
	while (action != playerActions.end()) {
		if (player->canPerform(*action)) {
			player->performAction(*action);
			planSim.update();

			unsigned int f = MAX_F;

			unsigned int visitedId = controlSim.getVisited(planSim.getCurrentState());
			if (visitedId == 0) {
				f = minimin(planSim, depth, 1);
			} else {
				f = controlSim.getStateValue(visitedId);
			}

			if (f < bestF) {
				secondBestF = bestF;
				bestF = f;
				bestAction = *action;
			} else if (f < secondBestF) {
				secondBestF = f;
			}

			planSim.undoUpdate();
		}
		action++;
	}

	return bestAction;
}

unsigned int PacmanRTAPathfinder::minimin(GameSimulator & planSim, unsigned int depth, unsigned int g)
{
	assert(h != 0);

	if (planSim.isGameOver()) {
		if (planSim.getGameOverResult() == GameSimulator::WIN) {
			return g;
		} else {
			return LOSE_VALUE;
		}
	} else if (g >= depth) {
		return (*h)(planSim.getGame()) + g;
	} else {
		const GameState * currentState = planSim.getCurrentState();

		if (planSim.isInPath(currentState)) {
			return MAX_F;
		} else {
			unsigned int visitedId = planSim.getVisited(currentState);

			if (visitedId != 0) {
				return planSim.getStateValue(visitedId) + g;
			} else {
				LogicObject * player = planSim.getPlayer();
				list<Action::Type> playerActions;
				player->getActions(playerActions);

				pruneActions(player, playerActions);

				unsigned int minF = MAX_F;

				list<Action::Type>::iterator action = playerActions.begin();
				while (action != playerActions.end()) {
					if (player->canPerform(*action)) {
						player->performAction(*action);
						planSim.update();

						unsigned int f = minimin(planSim, depth, g + 1);

						if (f < minF) {
							minF = f;
						}

						planSim.undoUpdate();
					}
					action++;
				}

				planSim.addVisited(currentState);
				planSim.setStateValue(currentState->getId(), minF - g);

				return minF;
			}
		}
	}
}

void PacmanRTAPathfinder::pruneActions(const LogicObject * player, list<Action::Type> & playerActions)
{
	// Se elimina la posibilidad de retroceder
	Direction direction;
	player->getAttribute(DIRECTION, direction);
	if (direction == DOWN)
		playerActions.remove(MoveAction::MoveUp);
	else if (direction == UP)
		playerActions.remove(MoveAction::MoveDown);
	else if (direction == RIGHT)
		playerActions.remove(MoveAction::MoveLeft);
	else
		playerActions.remove(MoveAction::MoveRight);
	// También se quita la posibilidad de detenerse en las intersecciones
	playerActions.remove(PacmanNoAction::NOACTION);
}

void PacmanRTAPathfinder::logSolution() const
{
	cout << "\n\nDetalle de las acciones de la solucion obtenida:\n";

	list<Action::Type>::const_iterator action = solution.begin();
	while (action != solution.end()) {
		cout << *action << endl;
		action++;
	}

	cout << "\nTotal de acciones ejecutadas: " << solution.size() << "\n";

	if (controlSim.getGameOverResult() == GameSimulator::WIN) {
		cout << "\nResultado: Gano\n";
	} else {
		cout << "\nResultado: Perdio\n";
	}
}

string format(int n)
{
	stringstream result;
	if (n < 10)
		result << '0' << n;
	else
		result << n;
	return result.str();
}

void PacmanRTAPathfinder::saveSolution() const
{
	// Generar el nombre del archivo de solución

	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	stringstream filename, date;

	date << timeinfo->tm_year + 1900 << format(timeinfo->tm_mon) << format(timeinfo->tm_mday);
	date << '-';
	date << format(timeinfo->tm_hour) << format(timeinfo->tm_min) << format(timeinfo->tm_sec);

	filename << getHeuristEvaluationName() << '-' << getDepth() << '-' << date.str() << ".txt";

	// Crear el archivo

	ofstream file(filename.str().c_str(), ios::trunc);

	file << "# Las lineas que comienzan con # se ignoraran al leer el archivo de acciones\n";
	file << "# Resultado de la solucion: ";
	if (controlSim.getGameOverResult() == GameSimulator::WIN) {
		file << "Gano\n";
	} else {
		file << "Perdio\n";
	}

	list<Action::Type>::const_iterator action = solution.begin();
	while (action != solution.end()) {
		file << *action << endl;
		action++;
	}
	file.close();

	cout << "\nSe guardo la solucion en el archivo: " << filename.str() << "\n\n";

	// Configurar el nombre del archivo a reproducir como una variable global
	setLastSolutionFilename(filename.str());
}

void PacmanRTAPathfinder::guardarValoresHeuristicas() const
{

	time_t rawtime;
	struct tm * timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	stringstream filename, date;

	date << timeinfo->tm_year + 1900 << format(timeinfo->tm_mon) << format(timeinfo->tm_mday);
	date << '-';
	date << format(timeinfo->tm_hour) << format(timeinfo->tm_min) << format(timeinfo->tm_sec);

	filename << getHeuristEvaluationName() << '-' << getDepth() << '-' << date.str() << ".dat";

	// Crear el archivo
    ofstream file(filename.str().c_str(), ios::trunc);
    int i =  1;
    int s = valores_heuristicas.size();
    for (std::list<unsigned>::const_iterator it = valores_heuristicas.begin(); it != valores_heuristicas.end(); it++, i++) {
        file << i << '\t' << (s-i) + 1 << '\t' << (*it) << endl;
    }
    file.close();
}
