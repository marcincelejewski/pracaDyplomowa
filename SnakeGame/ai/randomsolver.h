#ifndef RANDOMSOLVER_H
#define RANDOMSOLVER_H

#include "basesolver.h"

class RandomSolver : public BaseSolver
{
public:
	virtual Move nextMove(Snake *snake) override;
};

#endif // RANDOMSOLVER_H
