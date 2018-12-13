#ifndef NODE_H
#define NODE_H

#include <utility>

enum Direction {
	NORTH,
	SOUTH,
	EAST,
	WEST,
	ERROR_DIRECTION
};

using Node = std::pair<int, int>;

Direction getDirection(const Node & node, const Node &neighbor);
int manhattanDistance(const Node &a, const Node &b);
Node getNeighbor(const Node &node, const Direction &dir);

#endif // NODE_H