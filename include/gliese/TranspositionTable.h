#ifndef TRANSPOSITIONTABLE_H_
#define TRANSPOSITIONTABLE_H_

#include "GameState.h"

#include "hash_map"
#include "list"


class TranspositionTable
{
	static unsigned int fails;

public:
	TranspositionTable();

	virtual ~TranspositionTable();

	void add(const GameState * state);

	const GameState * find(const GameState * state) const;

	unsigned int size() const;

private:
	typedef std::hash_map<unsigned int, std::list<const GameState *> > StateTable;
	StateTable states;
	unsigned int stateCount;
};


#endif /* TRANSPOSITIONTABLE_H_ */
