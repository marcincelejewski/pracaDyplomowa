#include "randomsolver.h"

Move RandomSolver::nextMove(Snake *snake)
{
	Direction dir = snake->randomMove(snake->head);
	if (snake->canMove(dir))
	{
		return snake->move(dir);
	}
	else
	{
		return COLLISION;
	}
}