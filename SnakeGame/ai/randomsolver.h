#ifndef RANDOMSOLVER_H
#define RANDOMSOLVER_H

#include "ai/basesolver.h"

class RandomSolver : public BaseSolver
{
public:
	RandomSolver() {};
	~RandomSolver() {};

	virtual Move nextMove(Snake * snake) override;
};

#endif // RANDOMSOLVER_H
