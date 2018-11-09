#include "randomsolver.h"

Move RandomSolver::nextMove(Snake *snake)
{
	std::vector<Direction> directions;

	if (snake->canMove(NORTH))
	{
		directions.push_back(NORTH);
	}
	if (snake->canMove(SOUTH))
	{
		directions.push_back(SOUTH);
	}
	if (snake->canMove(EAST))
	{
		directions.push_back(EAST);
	}
	if (snake->canMove(WEST))
	{
		directions.push_back(WEST);
	}

	if (directions.size() > 0)
	{
		Direction dir = directions.at(random(0, directions.size()));
		return snake->move(dir);
	}
	else
	{
		return COLLISION;
	}
}

RandomSolver::RandomSolver()
{
}