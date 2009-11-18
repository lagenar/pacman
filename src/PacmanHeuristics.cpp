#include "PacmanHeuristics.h"

#include "Pacman.h"

#include "iostream"

using namespace std;


unsigned int h1(const Game * game)
{
    // Reemplazar
    const int margin = 8;
    const GameSpace & gs = game->getGameSpace();
    const int w = gs.getWidth();
    const int h = gs.getHeight();
    const LogicObject * pacman = game->getObject(PACMAN);
    const Shape * shape = pacman->getShape();
    const int x = shape->getX();
    const int y = shape->getY();
    int hi, hf, wi, wf; //Extremos del rectangulo.
    hi = max(0, y - margin); //Revisar el rango de la matriz.
    hf = min(h - 1, y + margin);
    wi = max(0, x - margin);
    wf = min(w - 1, x + margin);
    set<string> ghostSubtype;
    ghostSubtype.insert(GHOST);
    list<const LogicObject *> ghosts;
    gs.getObjects(Rectangle(wi,hi,wf-wi,hf-hi), LogicObject::Type(ghostSubtype), ghosts);
    int cantidad = ghosts.size();
    cout << "dimensiones: " << wi << "," << hi << "," << wf << "," << hf << endl;
    return game->getVariables().getInteger(DOT_COUNT)+cantidad*10;
}

unsigned int h2(const Game * game)
{
    // Reemplazar
	return game->getVariables().getInteger(DOT_COUNT);
}

unsigned int h3(const Game * game)
{
    // Reemplazar
    const LogicObject * pacman = game->getObject(PACMAN);
    const Shape * shape = pacman->getShape();
    const int x = shape->getX();
    const int y = shape->getY();
    const GameSpace & gs = game->getGameSpace();
    const int w = gs.getWidth();
    const int h = gs.getHeight();
    list<const LogicObject *> ghosts;
    ghosts.push_back(game->getObject(INKY));
    ghosts.push_back(game->getObject(PINKY));
    ghosts.push_back(game->getObject(BLINKY));
    ghosts.push_back(game->getObject(CLYDE));
    int costo = game->getVariables().getInteger(DOT_COUNT);
    list<const LogicObject *>::const_iterator it;
    for(it = ghosts.begin(); it != ghosts.end(); it++)
    {
        const Shape * shape = (*it)->getShape();
        int posx = shape->getX();
        int posy = shape->getY();
        int d = abs(posx-x)+abs(posy-y);
        costo-=d;
    }
    return costo;
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

