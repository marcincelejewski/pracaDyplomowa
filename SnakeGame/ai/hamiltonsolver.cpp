#include "ai/hamiltonsolver.h"

HamiltonSolver::HamiltonSolver()
{
	list.clear();
	home = Node(0, 0);
}

HamiltonSolver::~HamiltonSolver()
{
	list.clear();
}

Move HamiltonSolver::nextMove(Snake * snake)
{
	if (list.empty())
	{
		if (snake->head == home)
		{
			getSimplyHamiltonCycle(*snake);
		}
		else
		{
			list.push_front(snake->moveCloser(snake->head, home).first);
		}
	}
	if (snake->canMove(list.front()))
	{
		Move move = snake->move(list.front());
		list.pop_front();
		return move;
	}
	else
	{
		return COLLISION;
	}
}

void HamiltonSolver::getSimplyHamiltonCycle(Snake snake)
{
	snake.addDirectionsToList(list, EAST, Snake::BOARD_SIZE - 1);
	snake.addDirectionsToList(list, SOUTH, Snake::BOARD_SIZE - 1);

	size_t col = Snake::BOARD_SIZE - 1;

	while (true)
	{
		list.push_back(WEST);
		snake.addDirectionsToList(list, NORTH, Snake::BOARD_SIZE - 2);
		list.push_back(WEST);
		snake.addDirectionsToList(list, SOUTH, Snake::BOARD_SIZE - 2);

		col = col - 2;

		if (Snake::BOARD_SIZE % 2 == 0 && col == 1)
		{
			list.push_back(WEST);
			snake.addDirectionsToList(list, NORTH, Snake::BOARD_SIZE - 1);
			break;
		}
		if (Snake::BOARD_SIZE % 2 == 1 && col == 2)
		{
			list.push_back(WEST);
			if (snake.food == Node(1, Snake::BOARD_SIZE - 2))
			{
				list.push_back(NORTH);
				list.push_back(WEST);
				list.push_back(NORTH);
			}
			else
			{
				list.push_back(WEST);
				list.push_back(NORTH);
				list.push_back(NORTH);
			}
			for (int i = 0; i < (Snake::BOARD_SIZE - 3) / 2; i++)
			{
				list.push_back(EAST);
				list.push_back(NORTH);
				list.push_back(WEST);
				list.push_back(NORTH);
			}
			break;
		}
	}
}