#include "snake.h"

Snake::Snake(Node head, Node prevTail, Node tail, Node food)
{
	this->isGameOver = false;
	this->head = head;
	this->prevTail = prevTail;
	this->tail = tail;
	this->food = food;
	this->nodes.push_back(head);
	this->nodes.push_back(prevTail);
	this->nodes.push_back(tail);
	this->score = 0;
	this->movementCounter = 0;
	this->updateSet();
}

Snake::Snake(const Snake & snake)
{
	this->isGameOver = snake.isGameOver;
	this->head = snake.head;
	this->prevTail = snake.prevTail;
	this->tail = snake.tail;
	this->food = snake.food;

	this->score = snake.score;
	this->movementCounter = snake.movementCounter;

	this->nodes = snake.nodes;
	this->set = snake.set;
}

Snake::Snake()
{
}

Node Snake::getNode(const size_t &index) const
{
	if (index < nodes.size() && index >= 0)
		return nodes.at(index);
	return Node(-1, -1);
}

Direction Snake::getHeadDirection() const
{
	return getDirection(getNode(1), head);
}

Direction Snake::getTailDirection() const
{
	return getDirection(tail, getNode(nodes.size() - 2));
}

Direction Snake::randomMove(const Node & node)
{
	std::vector<Direction> tmp;
	if (canMove(getNeighbor(node, NORTH)))
	{
		tmp.push_back(NORTH);
	}
	if (canMove(getNeighbor(node, SOUTH)))
	{
		tmp.push_back(SOUTH);
	}
	if (canMove(getNeighbor(node, WEST)))
	{
		tmp.push_back(WEST);
	}
	if (canMove(getNeighbor(node, EAST)))
	{
		tmp.push_back(EAST);
	}
	if (tmp.size() > 0)
	{
		return tmp.at(random(0, tmp.size()));
	}
	return ERROR_DIRECTION;
}

Direction Snake::moveAway(const Node & from, const Node & dest)
{
	std::vector<std::pair<Node, int>> tmp;
	Node north = getNeighbor(from, NORTH);
	Node south = getNeighbor(from, SOUTH);
	Node west = getNeighbor(from, WEST);
	Node east = getNeighbor(from, EAST);

	if (canMove(north))
	{
		tmp.push_back(std::make_pair(north, -1));
	}
	if (canMove(south))
	{
		tmp.push_back(std::make_pair(south, -1));
	}
	if (canMove(west))
	{
		tmp.push_back(std::make_pair(west, -1));
	}
	if (canMove(east))
	{
		tmp.push_back(std::make_pair(east, -1));
	}

	for (auto &node : tmp)
	{
		node.second = moveCloser(node.first, dest).second;
	}

	std::vector<Node> nodes;
	int max = -1;
	for (auto it = tmp.begin(); it != tmp.end(); it++)
	{
		if (it->second >= max)
		{
			if (it->second > max)
			{
				max = it->second;
				nodes.clear();
			}
			nodes.push_back(it->first);
		}
	}
	if (nodes.size() > 0)
	{
		Node node = nodes.at(random(0, nodes.size()));
		return getDirection(from, node);
	}
	return ERROR_DIRECTION;
}

std::pair<Direction, int> Snake::moveCloser(const Node &from, const Node &dest)
{
	//set			distance,	node(x,y)
	std::set<std::pair<int, Node>> setds;

	//map of predecessors node(x, y)
	std::map<Node, Node> path;

	//map of distance to node(x, y), distance
	std::map<Node, int> dist;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			dist[Node(i, j)] = INT_MAX;
			path[Node(i, j)] = Node(-1, -1);
		}
	}
	//map of nodes, from node(x,y)	to list his neighbor nodes(x,y) distance
	std::map<Node, std::list<std::pair<Node, int>>> map;
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (canMove(Node(i, j - 1)))
			{
				map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i, j - 1), 1));
			}
			if (canMove(Node(i, j + 1)))
			{
				map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i, j + 1), 1));
			}
			if (canMove(Node(i + 1, j)))
			{
				map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i + 1, j), 1));
			}
			if (canMove(Node(i - 1, j)))
			{
				map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i - 1, j), 1));
			}
		}
	}

	setds.insert(std::make_pair(0, from));
	dist[from] = 0;

	while (!setds.empty())
	{
		std::pair<int, Node> tmp = *(setds.begin());
		setds.erase(setds.begin());

		Node u = tmp.second;

		std::list<std::pair<Node, int>>::iterator i;
		for (i = map[u].begin(); i != map[u].end(); ++i)
		{
			Node v = (*i).first;
			int weight = (*i).second;

			if (dist[v] > dist[u] + weight)
			{
				if (dist[v] != INT_MAX)
				{
					setds.erase(setds.find(std::make_pair(dist[v], v)));
				}
				dist[v] = dist[u] + weight;
				path[v] = u;
				setds.insert(std::make_pair(dist[v], v));
			}
		}
	}

	Node n;
	if (dist[dest] == INT_MAX)
	{	// jeœli cel jest nieosi¹galny
		return std::make_pair(ERROR_DIRECTION, -1);
	}
	else {
		n = dest;
	}

	Node prev;
	std::pair<Direction, int> prevprev;

	while (true)
	{
		prev = Node(path[n]);
		if (prev == Node(-1, -1))
		{
			return prevprev;
		}
		prevprev = std::make_pair(getDirection(prev, n), dist[dest]);
		n = prev;
	}
}

void Snake::addDirectionsToList(std::list<Direction>& list, const Direction &dir, const size_t &count)
{
	for (size_t i = 0; i < count; i++)
	{
		list.push_back(dir);
	}
}

Move Snake::addNode(const Node &n)
{
	nodes.insert(nodes.begin(), n);
	head = nodes.front();
	movementCounter++;
	if (!(n == food))
	{
		tail = prevTail;
		nodes.pop_back();
		prevTail = getNode(nodes.size() - 2);
		updateSet();
		return NORMAL;
	}
	else
	{
		score++;
		updateSet();
		randomFood();
		return EATEN_FOOD;
	}
}

void Snake::randomFood() {
	std::vector<Node> v;
	for (size_t i = 0; i < Snake::BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < Snake::BOARD_SIZE; j++)
		{
			Node node = std::make_pair(i, j);
			if (node != tail)
			{
				auto search = set.find(node);
				if (search == set.end())
				{
					v.push_back(Node(i, j));
				}
			}
		}
	}
	if (v.size() > 0)
	{
		food = v.at(random(0, v.size()));
	}
	else
	{
		food = Node(-1, -1);
	}
}

Move Snake::move(const Direction &dir)
{
	if (food == Node(-1, -1))
	{
		return COLLISION;
	}
	Move move;
	if (dir == NORTH) {
		Node n = Node(head.first, head.second - 1);
		move = addNode(n);
	}
	else if (dir == EAST)
	{
		Node n = Node(head.first + 1, head.second);
		move = addNode(n);
	}
	else if (dir == SOUTH)
	{
		Node n = Node(head.first, head.second + 1);
		move = addNode(n);
	}
	else if (dir == WEST)
	{
		Node n = Node(head.first - 1, head.second);
		move = addNode(n);
	}
	else
	{
		throw "Niedozwolony kierunek";
	}
	return move;
}

bool Snake::canMove(const Direction &dir)
{
	Node n;
	if (dir == NORTH)
	{
		n = getNeighbor(head, NORTH);
		auto search = set.find(n);
		if (search != set.end() || n.second < 0)
		{
			return false;
		}
		return true;
	}
	else if (dir == EAST)
	{
		n = getNeighbor(head, EAST);
		auto search = set.find(n);
		if (search != set.end() || n.first >= Snake::BOARD_SIZE)
		{
			return false;
		}
		return true;
	}
	else if (dir == SOUTH)
	{
		n = getNeighbor(head, SOUTH);
		auto search = set.find(n);
		if (search != set.end() || n.second >= Snake::BOARD_SIZE)
		{
			return false;
		}
		return true;
	}
	else if (dir == WEST)
	{
		n = getNeighbor(head, WEST);
		auto search = set.find(n);
		if (search != set.end() || n.first < 0)
		{
			return false;
		}
		return true;
	}
	return false;
}

bool Snake::canMove(const Node & node)
{
	if (node.first < 0 || node.first >= BOARD_SIZE || node.second < 0 || node.second >= BOARD_SIZE)
	{
		return false;
	}
	auto search = set.find(node);
	if (search != set.end())
	{
		return false;
	}
	return true;
}

void Snake::updateSet()
{
	set.clear();
	for (auto &node : this->nodes)
	{
		if (node != tail)
		{
			set.insert(node);
		}
	}
}

//void Snake::saveData()
//{
//	std::ofstream outfile(Snake::outFileName, std::ios_base::app);
//
//	if (outfile.is_open())
//	{
//		outfile << "\n" << score << ";" << timeToString(time, std::chrono::high_resolution_clock::now()) << ";" << movementCounter;
//		outfile.close();
//	}
//}