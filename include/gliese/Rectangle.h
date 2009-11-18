#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "Shape.h"

/**
 * La clase Rectangle es la representación de un rectángulo.
 *
 * En el caso del rectángulo las coordenadas (x,y) corresponden a la esquina
 * superior izquierda del mismo.
 *
 */
class Rectangle : public Shape
{
public:
    Rectangle(int x, int y, int width, int height);

    Rectangle(const Rectangle & other);

    virtual ~Rectangle();

    Shape * newInstance() const;

    Rectangle & operator = (const Rectangle & rec);

    bool operator == (const Shape & area) const;

    bool operator != (const Shape & area) const;

    bool contains(int x, int y) const;

    /**
     * Devuelve el ancho del rectángulo.
     * @return ancho.
     */
    int getWidth() const;

    /**
     * Devuelve el alto del rectángulo.
     * @return alto.
     */
    int getHeight() const;

    /**
     * Configura el ancho del rectángulo.
     * @param width ancho.
     */
    void setWidth(int width);

    /**
     * Configura el alto del rectángulo.
     * @param height alto.
     */
    void setHeight(int height);

protected:
    int width, height;
};

#endif /*RECTANGLE_H_*/
