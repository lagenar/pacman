#include "PacmanHeuristics.h"

#include "Pacman.h"

#include "iostream"

using namespace std;


unsigned int h1(const Game * game)
{
    // Reemplazar
    const GameSpace & gs = game->getGameSpace();
    int w = gs.getWidth();
    int h = gs.getHeight();
    const LogicObject * pacman = game->getObject(PACMAN);
    const Shape * shape = pacman->getShape();
    int x = shape->getX();
    int y = shape->getY();
    return abs(w/2-x)+abs(h/2-y)+10*game->getVariables().getInteger(DOT_COUNT);
}

unsigned int h2(const Game * game)
{
    // Reemplazar
	return game->getVariables().getInteger(DOT_COUNT)*game->getVariables().getInteger(DOT_COUNT);
}

unsigned int h3(const Game * game)
{
    // Reemplazar
	return game->getVariables().getInteger(DOT_COUNT);
}

unsigned int h4(const Game * game)
{
    // Reemplazar
	return game->getVariables().getInteger(DOT_COUNT);
}

unsigned int h5(const Game * game)
{
    // Reemplazar
	return game->getVariables().getInteger(DOT_COUNT);
}

unsigned int h6(const Game * game)
{
    // Reemplazar
	return game->getVariables().getInteger(DOT_COUNT);
}

