#ifndef GAMESPACE_H_
#define GAMESPACE_H_

#include "LogicObject.h"
#include "Rectangle.h"

#include "cassert"
#include "list"
#include "string"

#include "iostream"


/**
 * La clase GameSpace representa la estructura de datos que permite acceder a
 * los objetos lógicos a través de sus coordenadas en el espacio bidimensional
 * que constituye el area de juego.
 */
class GameSpace
{
public:
	GameSpace(int width, int height, int sectorWidth, int sectorHeight);

    virtual ~GameSpace();

    /**
     * Devuelve el ancho del espacio de juego, en unidades lógicas.
     * @return ancho del espacio de juego.
     */
    int getWidth() const;

    /**
     * Devuelve el alto del espacio de juego, en unidades lógicas.
     * @return alto del espacio de juego.
     */
    int getHeight() const;

    /**
     * Agrega un objeto lógico al área de juego.
     * @param obj objeto lógico.
     */
    void add(LogicObject * obj);

    /**
     * Elimina un objeto lógico al área de juego.
     * @param obj objeto lógico.
     */
    void remove(LogicObject * obj);

    /**
     * Devuelve los objetos que ocupan en forma total o parcial el area
     * rectangular indicada.
     * @param area area sobre el cual se buscarán los objetos.
     * @param objects objetos constantes cuya posición se encuentra dentro del area indicada.
     */
    void getObjects(const Rectangle & area, std::list<const LogicObject *> & objects) const;

    /**
     * Devuelve los objetos que ocupan en forma total o parcial el area
     * rectangular indicada.
     * @param area area sobre el cual se buscarán los objetos.
     * @param objects objetos cuya posición se encuentra dentro del area indicada.
     */
    void getObjects(const Rectangle & area, std::list<LogicObject *> & objects);

    /**
     * Devuelve los objetos que ocupan en forma total o parcial el area
     * rectangular indicada y que cumplan con el filtro por tipo.
     * @param area area sobre el cual se buscarán los objetos.
     * @param type tipo de los objetos
     * @param objects objetos constantes cuya posición se encuentra dentro del area indicada.
     */
    void getObjects(const Rectangle & area, const LogicObject::Type & type, std::list<const LogicObject *> & objects) const;

    /**
     * Devuelve los objetos que ocupan en forma total o parcial el area
     * rectangular indicada y que cumplan con el filtro por tipo.
     * @param area area sobre el cual se buscarán los objetos.
     * @param type tipo de los objetos
     * @param objects objetos cuya posición se encuentra dentro del area indicada.
     */
    void getObjects(const Rectangle & area, const LogicObject::Type & type, std::list<LogicObject *> & objects);

    virtual GameSpace * newInstance() const;

private:
	class SpaceSector;

private:
    const SpaceSector & getSector(int x, int y) const;
    SpaceSector & getSector(int x, int y);

private:
	SpaceSector * * sectors;
    int width, height;
    int sectorWidth, sectorHeight;
};


#endif /*GAMESPACE_H_*/
