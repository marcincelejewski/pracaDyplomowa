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
	{	//jeœli mo¿emy pod¹¿aæ za jab³uszkiem
		return realTofood;
	}
	else
	{	//jeœli nie mo¿emy pod¹¿aæ za jab³uszkiem
		Direction realToTail = snake.moveAway(snake.head, snake.tail);
		if (realToTail == ERROR_DIRECTION)
		{	//jeœli nie mo¿emy pod¹¿aæ za ogonem
			//dozwolony ruch losowy
			return snake.randomMove(snake.head);
		}
		return realToTail;
	}
}