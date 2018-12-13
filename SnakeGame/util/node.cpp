#include "node.h"

Direction getDirection(const Node & node, const Node &neighbor)
{
	if (neighbor.first > node.first)
	{
		return EAST;
	}
	else if (neighbor.first < node.first)
	{
		return WEST;
	}
	else if (neighbor.second < node.second)
	{
		return NORTH;
	}
	else if (neighbor.second > node.second)
	{
		return SOUTH;
	}
	return ERROR_DIRECTION;
}

int manhattanDistance(const Node &a, const Node &b)
{
	return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

Node getNeighbor(const Node &node, const Direction &dir)
{
	Node n;
	if (dir == NORTH)
	{
		n = Node(node.first, node.second - 1);
	}
	else if (dir == SOUTH)
	{
		n = Node(node.first, node.second + 1);
	}
	else if (dir == WEST)
	{
		n = Node(node.first - 1, node.second);
	}
	else if (dir == EAST)
	{
		n = Node(node.first + 1, node.second);
	}
	return n;
}