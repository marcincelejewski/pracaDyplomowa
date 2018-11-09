#ifndef NODE_H
#define NODE_H

#include <string>

enum Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST
};

class Node
{
public:
	Node();
	Node(int x, int y);
	int x, y;
	bool operator==(const Node& n);
	Direction getDirection(const Node &neighbor);
	std::string toString();
};

#endif // NODE_H
