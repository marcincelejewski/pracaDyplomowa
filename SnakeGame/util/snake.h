#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <limits.h>
#include <set>
#include <map>
#include <chrono>
#include <fstream>
#include <string>
#include "node.h"

struct pair_hash {
	inline std::size_t operator()(const std::pair<std::size_t, std::size_t> &v) const {
		return v.first * 6661 + v.second;
	}
};

enum Move {
	COLLISION,
	EATEN_FOOD,
	NORMAL
};

class Snake
{
public:
	Snake(Node first, Node prevTail, Node tail, Node food);
	Snake(const Snake &snake);

	Node getNode(const size_t &index);

	Direction getHeadDirection();
	Direction getTailDirection();
	Direction randomMove(const Node &node);
	Direction moveAway(const Node &from, const Node &dest);

	std::pair<Direction, int> moveCloser(const Node &from, const Node &dest);

	void addDirectionsToList(std::list<Direction> & list, const Direction &dir, const size_t &count);
	void updateSet();
	void startTime();
	void saveData();
	void randomFood();

	Move move(const Direction &dir);
	Move addNode(const Node &n);

	bool canMove(const Direction &dir);
	bool canMove(const Node &node);

	Node head;
	Node tail;
	Node prevTail;
	Node food;
	static size_t BOARD_SIZE;
	static std::string outFileName;
	size_t score;

	size_t movementCounter;
	std::chrono::high_resolution_clock::time_point time;

	std::vector <Node> nodes;
	std::unordered_set<std::pair<size_t, size_t>, pair_hash> set;
};

inline std::size_t random(const std::size_t min, const std::size_t max)
{
	std::random_device r;
	std::default_random_engine e1(r());
	const std::uniform_int_distribution<std::size_t> uniform_dist(min, max - 1);
	return uniform_dist(e1);
}

#endif // SNAKE_H
