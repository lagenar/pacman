#include "PacmanHeuristics.h"

#include "Pacman.h"

#include "iostream"

using namespace std;


unsigned int h1(const Game * game)
{
    // Reemplazar
    const int margin = 4;
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
    return game->getVariables().getInteger(DOT_COUNT) + cantidad;
}

int distancia_manhattan(int x1, int x2, int y1, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

unsigned int h2(const Game * game)
{
    const LogicObject * pacman = game->getObject(PACMAN);
    const Shape * shape = pacman->getShape();
    int x = shape->getX();
    int y = shape->getY();
    const GameSpace & gs = game->getGameSpace();
    const int w = gs.getWidth();
    const int h = gs.getHeight();

    Direction dir;
    pacman->getAttribute(DIRECTION, dir);
    int wi, hi, rw, rh;
    if (dir == DOWN) {
        wi = 1;
        hi = y + 1;
        rw = w;
        rh = h-hi;
    } else if (dir == UP) {
        wi = 1;
        hi = 1;
        rw = w;
        rh = y-1;
    } else if (dir == LEFT) {
        wi = 1;
        hi = 1;
        rw = x - 1;
        rh = h;
    } else if (dir == RIGHT) {
        wi = x + 1;
        hi = 1;
        rw = w - wi;
        rh = h;
    } else {
        wi = 1;
        hi = 1;
        rw = w;
        rh = h;
    }
    set<string> dotSubtype;
    dotSubtype.insert(DOT);
    list<const LogicObject *> dots;
    cout << wi << "," << hi << "," << rw << "," << rh << endl;
    game->getGameSpace().getObjects(Rectangle(wi, hi, rw, rh),
                                    LogicObject::Type(dotSubtype), dots);

    int d = 1000;
    for (list<const LogicObject *>::const_iterator it = dots.begin(); it != dots.end(); it++) {
        const Shape * s = (*it)->getShape();

        d = min(d, distancia_manhattan(x, s->getX(), y, s->getY()));
    }

	return game->getVariables().getInteger(DOT_COUNT) + d;
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
        int d = abs(posx-x) + abs(posy-y);
        double f = (1.0/float(d)) * 100;
        costo+=f;
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

