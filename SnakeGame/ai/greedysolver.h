#ifndef GREEDYSOLVER_H
#define GREEDYSOLVER_H

#include "ai/basesolver.h"
class GreedySolver : public BaseSolver
{
public:
	GreedySolver() {};
	~GreedySolver() {};

	virtual Move nextMove(Snake * snake) override;

	Direction greedy(Snake snake, const Node &dest);
};

#endif // GREEDYSOLVER_H
