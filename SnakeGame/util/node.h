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
	int x, y;

	Node();
	Node(int x, int y);
	bool operator==(const Node& n);
	Direction getDirection(const Node &neighbor);
};

#endif // NODE_H
