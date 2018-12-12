#ifndef GREEDYSOLVER_H
#define GREEDYSOLVER_H

#include "basesolver.h"
class GreedySolver : public BaseSolver
{
public:
	GreedySolver() {};
	~GreedySolver() {};
	virtual Move nextMove(Snake *snake) override;

	Direction greedy(Snake snake, const Node &dest);
};

#endif // GREEDYSOLVER_H
