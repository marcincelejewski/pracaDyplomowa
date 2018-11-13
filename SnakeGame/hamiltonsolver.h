#ifndef HAMILTONSOLVER_H
#define HAMILTONSOLVER_H

#include "ai/basesolver.h"

class HamiltonSolver : public BaseSolver
{
public:
	virtual Move nextMove(Snake *snake) override;
	HamiltonSolver();
	std::list<Direction> list;
	Node home;
};

#endif // HAMILTONSOLVER_H