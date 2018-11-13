#include "hamiltonsolver.h"

Move HamiltonSolver::nextMove(Snake * snake)
{
	std::list<Direction> list;
	if (list.empty())
	{
		if (snake->head == home)
		{
			//podazaj sciezka hamiltona
		}
		else
		{
			snake->shortestPathToNode(list, home);
		}
	}
	if (snake->canMove(list.back()))
	{
		Move move = snake->move(list.back());
		list.pop_back();
		return move;
	}
	else
	{
		return COLLISION;
	}
}

HamiltonSolver::HamiltonSolver()
{
	list.clear();
	home = Node(0, 0);
}