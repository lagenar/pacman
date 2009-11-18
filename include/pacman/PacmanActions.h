#ifndef PACMANACTIONS_H_
#define PACMANACTIONS_H_

#include "MoveAction.h"


class PacmanCharacterMove: public MoveAction
{
public:
	PacmanCharacterMove(const Type & type, unsigned int cycles, unsigned int distance);
	PacmanCharacterMove(const PacmanCharacterMove & other);

	virtual ~PacmanCharacterMove();

	virtual Action & operator = (const Action & other);

	virtual Action * newInstance() const;

	virtual bool canPerform() const;

protected:
	virtual void processCycle();
};


class PacmanMove: public PacmanCharacterMove
{
public:
	PacmanMove(const Type & type, unsigned int cycles, unsigned int distance);
	PacmanMove(const PacmanMove & other);

	virtual ~PacmanMove();

	Action & operator = (const Action & other);

	Action * newInstance() const;

protected:
	void processCycle();
};


class GhostMove: public PacmanCharacterMove
{
public:
	GhostMove(const Type & type, unsigned int cycles, unsigned int distance);
	GhostMove(const PacmanMove & other);

	virtual ~GhostMove();

	Action & operator = (const Action & other);

	Action * newInstance() const;

protected:
	virtual void processCycle();
};


class PacmanNoAction: public NoAction
{
public:
	static const Action::Type NOACTION;

public:
	PacmanNoAction(const Type & type, unsigned int cycles);

	PacmanNoAction(const PacmanNoAction & other);

	virtual ~PacmanNoAction();

	Action * newInstance() const;

	Action & operator = (const Action & other);

	bool canPerform() const;

protected:
    void processCycle();
};


#endif /* PACMANACTIONS_H_ */
