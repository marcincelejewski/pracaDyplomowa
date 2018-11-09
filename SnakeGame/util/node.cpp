#include "node.h"

Node::Node(int x, int y)
{
	this->x = x;
	this->y = y;
}
Node::Node() {}

bool Node::operator==(const Node& node)
{
	if (this->x == node.x && this->y == node.y)
	{
		return true;
	}
	return false;
}

Direction Node::getDirection(const Node &neighbor)
{
	if (neighbor.x > this->x)
	{
		return EAST;
	}
	else if (neighbor.x < this->x)
	{
		return WEST;
	}
	else if (neighbor.y < this->y)
	{
		return NORTH;
	}
	else if (neighbor.y > this->y)
	{
		return SOUTH;
	}
}

std::string Node::toString() {
	return "(" + std::to_string(x) + "," + std::to_string(y) + ")";
}