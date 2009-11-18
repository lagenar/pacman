#ifndef RULE_H_
#define RULE_H_

#include "Component.h"


class Game;


// TODO: Renombrar a "Process"
// TODO: Subir la prioridad a nivel del componente y ajustar el PriorityComponentManager acordemente

class Rule : public Component
{
public:
	/*static const unsigned int HIGHEST_PRIORITY = 0;
	static const unsigned int HIGH_PRIORITY = 50;*/
	static const unsigned int DEFAULT_PRIORITY = 1;



public:
	Rule(const Type & type = "", bool skip = false, unsigned int priority = DEFAULT_PRIORITY);
	Rule(const Type & type, unsigned int priority);
	Rule(bool skip, unsigned int priority = DEFAULT_PRIORITY);
	Rule(unsigned int priority);
	Rule(const Rule & other);

	virtual ~Rule();

	unsigned int getPriority() const;

	bool getSkipUpdate() const;

	void setPriority(unsigned int priority);

	void setSkipUpdate(bool skip);

    void setGame(Game * game);

    //Rule & operator = (const Rule & other);
	virtual Component & operator = (const Component & other);

protected:
	virtual void update(unsigned int time);

	virtual void onUpdate(unsigned int time) = 0;

protected:
	unsigned int priority;
	bool skipUpdate;

	Game * game;
};

#endif /*RULE_H_*/
