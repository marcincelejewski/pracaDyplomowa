#ifndef ASTARSOLVER_H
#define ASTARSOLVER_H

#include "ai/basesolver.h"
#include <queue>

class AStarSolver : public BaseSolver
{
public:
	AStarSolver();
	~AStarSolver() {};
	virtual Move nextMove(Snake * snake) override;

	Direction aSearch(Snake snake, const Node &dest);
	Direction bfs(Snake snake, const Node &dest);
	Direction aSearchForwardChecking(Snake snake, const Node &dest);
	int sumPair(const std::pair<int, int> &p);
private:
	size_t counter;
};

#endif // ASTARSOLVER_H