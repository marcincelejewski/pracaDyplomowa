#ifndef ASTARSOLVER_H
#define ASTARSOLVER_H

#include "ai/basesolver.h"
#include "util/snake.h"
#include <stack>
#include <queue>
class AStarSolver : public BaseSolver
{
public:
	AStarSolver() {};
	~AStarSolver() {};
	virtual Move nextMove(Snake *snake) override;

	Direction aSearch(Snake snake, const Node &dest);
	Direction bfs(Snake snake, const Node &dest);
	Direction aSearchForwardChecking(Snake snake, const Node &dest);
	int sumPair(const std::pair<int, int> &p);
};

#endif // ASTARSOLVER_H