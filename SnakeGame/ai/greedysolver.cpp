#include "greedysolver.h"

Move GreedySolver::nextMove(Snake * snake)
{
	Direction dir = greedy(*snake, snake->food);

	if (snake->canMove(dir))
	{
		return snake->move(dir);
	}
	else
	{
		return COLLISION;
	}
}

Direction GreedySolver::greedy(Snake snake, const Node & dest)
{
	Direction realTofood = snake.moveCloser(snake.head, dest).first;

	if (realTofood != ERROR_DIRECTION)
	{	//je�li mo�emy pod��a� za jab�uszkiem
		return realTofood;
	}
	else
	{	//je�li nie mo�emy pod��a� za jab�uszkiem
		Direction realToTail = snake.moveAway(snake.head, snake.tail);
		if (realToTail == ERROR_DIRECTION)
		{	//je�li nie mo�emy pod��a� za ogonem
			//dozwolony ruch losowy
			return snake.randomMove(snake.head);
		}
		return realToTail;
	}
}