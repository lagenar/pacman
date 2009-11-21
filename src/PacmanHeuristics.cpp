#include "PacmanHeuristics.h"

#include "Pacman.h"

#include "iostream"

using namespace std;

int distancia_manhattan(int x1, int x2, int y1, int y2)
{
    return abs(x1-x2) + abs(y1-y2);
}

int distancia_punto_mas_cercano(const LogicObject * pacman, const GameSpace & gs)
{
    int x = pacman->getShape()->getX();
    int y = pacman->getShape()->getY();
    int w = gs.getWidth();
    int h = gs.getHeight();

    list<const LogicObject *> puntos;
    int min_dist = 1000;
    int frontera = 2;
    bool cubrio_espacio_total = false;
    bool hay_puntos = false;
    do {
        int wi = max(0, x - frontera);
        int hi = max(0, y - frontera);
        int wf = min(w, x + frontera);
        int hf = min(h, y + frontera);

        gs.getObjects(Rectangle(wi, hi, wf - wi, hf - hi), DOT, puntos);
        for (list<const LogicObject *>::const_iterator it = puntos.begin(); it != puntos.end(); it++) {
            const Shape * s = (*it)->getShape();
            min_dist = min(min_dist, distancia_manhattan(x, s->getX(), y, s->getY()));
        }

        hay_puntos = puntos.size() > 0;
        cubrio_espacio_total = (x - frontera) <= 0 && (y - frontera) <= 0 &&
                               (x + frontera) >= w && (y + frontera) >= h;
        frontera *= 2;
    } while (!hay_puntos && !cubrio_espacio_total);

    return min_dist;
}


unsigned int h1(const Game * game)
{
    int frontera = 5;
    const GameSpace & gs = game->getGameSpace();
    int w = gs.getWidth();
    int h = gs.getHeight();
    const LogicObject * pacman = game->getObject(PACMAN);
    const Shape * shape = pacman->getShape();
    int x = shape->getX();
    int y = shape->getY();
    int hi, hf, wi, wf; //Extremos del rectangulo.
    hi = max(0, y - frontera);
    hf = min(h - 1, y + frontera);
    wi = max(0, x - frontera);
    wf = min(w - 1, x + frontera);

    set<string> ghostSubtype;
    ghostSubtype.insert(GHOST);
    list<const LogicObject *> ghosts;
    gs.getObjects(Rectangle(wi,hi,wf-wi,hf-hi), LogicObject::Type(ghostSubtype), ghosts);
    int cant_ghosts = ghosts.size();
    int cant_puntos = game->getVariables().getInteger(DOT_COUNT);

    return cant_puntos + cant_ghosts;
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
    }

    list<const LogicObject *> dots;
    game->getGameSpace().getObjects(Rectangle(wi, hi, rw, rh),
                                    DOT, dots);

    int d = 1000;
    for (list<const LogicObject *>::const_iterator it = dots.begin(); it != dots.end(); it++) {
        const Shape * s = (*it)->getShape();

        d = min(d, distancia_manhattan(x, s->getX(), y, s->getY()));
    }

    int en_dir = dots.size();
	return game->getVariables().getInteger(DOT_COUNT) + 2*d;
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

