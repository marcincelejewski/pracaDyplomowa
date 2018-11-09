#ifndef SNAKE_H
#define SNAKE_H
#include "node.h"

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <QtDebug>

struct pair_hash {
	inline std::size_t operator()(const std::pair<std::size_t, std::size_t> & v) const {
		return v.first * 31 + v.second;
	}
};

inline std::size_t random(const std::size_t min, const std::size_t max)
{
	std::random_device r;
	std::default_random_engine e1(r());
	const std::uniform_int_distribution<std::size_t> uniform_dist(min, max - 1);
	return uniform_dist(e1);
}

enum Move {
	COLLISION,
	EATEN_FOOD,
	NORMAL
};

class Snake
{
public:
	Snake(Node first, Node last, Node tail, Node food);
	Node randomFood();
	Node getNode(size_t index);
	Direction getHeadDirection();
	Direction getTailDirection();
	const Node& getNullNode();

	Move move(Direction dir);
	Move addNode(Node n);

	void updateSet();
	bool canMove(Direction dir);

	Node head;
	Node tail;
	Node prevTail;
	Node food;
	static size_t boardSize;
	size_t score;
	std::vector <Node> nodes;
	std::unordered_set<std::pair<size_t, size_t>, pair_hash> set;
};

#endif // SNAKE_H
