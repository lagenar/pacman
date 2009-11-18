#ifndef SHAPE_H_
#define SHAPE_H_

/**
 * La clase Shape representa una figura bidimensional, con una posición dada
 * en la forma de coordenadas (x,y), la cual dependiendo de la instancia
 * particular puede constituir el centro de la misma o alguna de sus
 * esquinas.
 *
 */
class Shape
{
public:
	enum {
		RECTANGLE
	};

	typedef int Type;

public:
    Shape(const Type & type);

    virtual ~Shape();

    virtual Shape * newInstance() const = 0;

    virtual bool operator == (const Shape & area) const = 0;

    bool operator != (const Shape & area) const;

    Type getType() const;

    bool intersects(const Shape & area) const;

    virtual bool contains(int x, int y) const = 0;

    /**
     * Devuelve la coordenada X de la posición de la figura.
     * @return coordenada X.
     */
    int getX() const;

    /**
     * Devuelve la coordenada Y de la posición de la figura.
     * @return coordenada Y.
     */
    int getY() const;

	/**
     * Configura la coordenada X de la ubicación de la figura.
	 * @param x coordenada X.
	 */
    void setX(int x);

    /**
     * Configura la coordenada X de la ubicación de la figura.
     * @param y coordenada Y.
     */
    void setY(int y);

protected:
	Type type;
    int x, y;
};

#endif /*SHAPE_H_*/
