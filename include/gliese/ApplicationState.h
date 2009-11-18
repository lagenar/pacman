#ifndef APPLICATIONSTATE_H_
#define APPLICATIONSTATE_H_

#include "VisualObjectRenderer.h"


class Application;


/**
 * La clase ApplicationState representa un estado de la aplicación.
 * Cada estado de la aplicación tendrá asignada una parte de la ventana
 * principal donde se podrá dibujar sus objetos visuales.
 */
class ApplicationState
{
	friend class Application;

public:
	ApplicationState(Application * application);

	virtual ~ApplicationState();

	VisualObjectRenderer & getVisualObjectRenderer();

protected:
	virtual void setup() = 0;

	virtual void clean() = 0;

	virtual void update(unsigned int time) = 0;

protected:
	Application * application;
	VisualObjectRenderer visualObjects;
};

#endif /*APPLICATIONSTATE_H_*/
