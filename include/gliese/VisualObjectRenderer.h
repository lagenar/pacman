#ifndef VISUALOBJECTRENDERER_H_
#define VISUALOBJECTRENDERER_H_

#include "ComponentManager.h"
#include "Rectangle.h"


class Frame;
class Image;
class Rectangle;
class VisualObject;


class VisualObjectRenderer
{
public:
	VisualObjectRenderer(const Rectangle & clipRect);
	virtual ~VisualObjectRenderer();

	const Rectangle & getClipRect() const;

	void setClipRect(const Rectangle & clipRect);

	void add(VisualObject * vObj);

	void update(Frame * frame, unsigned int time);

	void setBackground(Image * background);

private:
	ComponentManager visualObjects;
	Rectangle clipRect;
	Image * background;
};

#endif /*VISUALOBJECTRENDERER_H_*/
