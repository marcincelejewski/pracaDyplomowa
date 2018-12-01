#ifndef SNAKE_H
#define SNAKE_H
#include "node.h"

#include <vector>
#include <algorithm>
#include <unordered_set>
#include <random>
#include <QtDebug>
#include <limits.h>
#include <set>
#include <map>
#include <chrono>
#include <fstream>

struct pair_hash {
	inline std::size_t operator()(const std::pair<std::size_t, std::size_t> &v) const {
		return v.first * 6661 + v.second;
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

	void randomFood();
	Node getNode(size_t index);
	const Node& getNullNode();

	Direction getHeadDirection();
	Direction getTailDirection();

	void shortestPathToNode(std::list<Direction> & list, Node dest);
	void getSimplyHamiltonCycle(std::list<Direction> & list);
	void addDirectionsToList(std::list<Direction> & list, Direction dir, size_t count);
	void updateSet();
	void startTime();

	void saveData();

	Move move(Direction dir);
	Move addNode(Node n);

	bool canMove(Direction dir);
	bool canMove(std::pair<int, int> node, Direction dir);

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

#endif // SNAKE_H
