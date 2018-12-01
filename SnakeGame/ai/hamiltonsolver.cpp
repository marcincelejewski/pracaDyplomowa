#include "ai/hamiltonsolver.h"

Move HamiltonSolver::nextMove(Snake * snake)
{
	if (list.empty())
	{
		if (snake->head == home)
		{
			snake->getSimplyHamiltonCycle(list);
		}
		else
		{
			snake->shortestPathToNode(list, home);
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

HamiltonSolver::HamiltonSolver()
{
	list.clear();
	home = Node(0, 0);
}