#include "snake.h"

std::string timeToString(std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point finish)
{
	return std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(finish - start).count());
}

Snake::Snake(Node first, Node last, Node tail, Node food)
{
	this->head = first;
	this->prevTail = last;
	this->tail = tail;
	this->food = food;
	nodes.push_back(first);
	nodes.push_back(last);
	nodes.push_back(tail);
	score = 0;
	movementCounter = 0;
	updateSet();
}

Node Snake::getNode(size_t index)
{
	if (index < nodes.size() && index >= 0)
		return nodes.at(index);
	return getNullNode();
}

//nieu¿ywane
Direction Snake::getHeadDirection()
{
	return getNode(1).getDirection(head);
}
//nieu¿ywane
Direction Snake::getTailDirection()
{
	return tail.getDirection(getNode(nodes.size() - 2));
}

void Snake::shortestPathToNode(std::list<Direction>& list, Node dest)
{
	if (!(head == dest))
	{
		//set			distance,	node(x,y)
		std::set<std::pair<int, std::pair<int, int>>> setds;

		//map of predecessors node(x, y)
		std::map<std::pair<int, int>, std::pair<int, int>> pred;

		//map of distance to node(x, y), distance
		std::map<std::pair<int, int>, int> dist;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				dist[std::make_pair(i, j)] = INT_MAX;
				pred[std::make_pair(i, j)] = std::make_pair(-1, -1);
			}
		}
		//map of nodes, from node(x,y)	to list his neighbor nodes(x,y) distance
		std::map<std::pair<int, int>, std::list<std::pair<std::pair<int, int>, int>>> map;
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (canMove(std::make_pair(i, j), NORTH))
				{
					map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i, j - 1), 1));
				}
				if (canMove(std::make_pair(i, j), SOUTH))
				{
					map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i, j + 1), 1));
				}
				if (canMove(std::make_pair(i, j), EAST))
				{
					map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i + 1, j), 1));
				}
				if (canMove(std::make_pair(i, j), WEST))
				{
					map[std::make_pair(i, j)].push_back(std::make_pair(std::make_pair(i - 1, j), 1));
				}
			}
		}

		setds.insert(std::make_pair(0, std::make_pair(head.x, head.y)));
		dist[std::make_pair(head.x, head.y)] = 0;

		while (!setds.empty())
		{
			std::pair<int, std::pair<int, int>> tmp = *(setds.begin());
			setds.erase(setds.begin());

			std::pair<int, int> u = tmp.second;

			std::list< std::pair<std::pair<int, int>, int>>::iterator i;
			for (i = map[u].begin(); i != map[u].end(); ++i)
			{
				std::pair<int, int> v = (*i).first;
				int weight = (*i).second;

				if (dist[v] > dist[u] + weight)
				{
					if (dist[v] != INT_MAX)
					{
						setds.erase(setds.find(std::make_pair(dist[v], v)));
					}
					dist[v] = dist[u] + weight;
					pred[v] = u;
					setds.insert(std::make_pair(dist[v], v));
				}
			}
		}

		Node n = dest;
		Node prev;
		while (true)
		{
			prev = Node(pred[std::make_pair(n.x, n.y)].first, pred[std::make_pair(n.x, n.y)].second);
			if (prev.x == -1 || prev.y == -1)
			{
				break;
			}
			list.push_front(prev.getDirection(n));
			n = prev;
		}
	}
}

void Snake::getSimplyHamiltonCycle(std::list<Direction>& list)
{
	addDirectionsToList(list, EAST, BOARD_SIZE - 1);
	addDirectionsToList(list, SOUTH, BOARD_SIZE - 1);

	size_t col = BOARD_SIZE - 1;

	while (true)
	{
		list.push_back(WEST);
		addDirectionsToList(list, NORTH, BOARD_SIZE - 2);
		list.push_back(WEST);
		addDirectionsToList(list, SOUTH, BOARD_SIZE - 2);

		col = col - 2;

		if (BOARD_SIZE % 2 == 0 && col == 1)
		{
			list.push_back(WEST);
			addDirectionsToList(list, NORTH, BOARD_SIZE - 1);
			break;
		}
		if (BOARD_SIZE % 2 == 1 && col == 2)
		{
			list.push_back(WEST);
			if (food == Node(1, 1))
			{
				list.push_back(NORTH);
				list.push_back(WEST);
				list.push_back(NORTH);

				for (int i = 0; i < (BOARD_SIZE - 3) / 2; i++)
				{
					list.push_back(EAST);
					list.push_back(NORTH);
					list.push_back(WEST);
					list.push_back(NORTH);
				}
			}
			else
			{
				for (int i = 0; i < (BOARD_SIZE - 3) / 2; i++)
				{
					list.push_back(EAST);
					list.push_back(NORTH);
					list.push_back(WEST);
					list.push_back(NORTH);
				}

				list.push_back(WEST);
				list.push_back(NORTH);
				list.push_back(NORTH);
			}
			break;
		}
	}
}

void Snake::addDirectionsToList(std::list<Direction>& list, Direction dir, size_t count)
{
	for (size_t i = 0; i < count; i++)
	{
		list.push_back(dir);
	}
}

Move Snake::addNode(Node n)
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
		saveData();
		return EATEN_FOOD;
	}
}

void Snake::randomFood() {
	std::vector<Node> v;
	for (size_t i = 0; i < Snake::BOARD_SIZE; i++)
	{
		for (size_t j = 0; j < Snake::BOARD_SIZE; j++)
		{
			auto search = set.find(std::make_pair(i, j));
			if (search == set.end())
			{
				v.push_back(Node(i, j));
			}
		}
	}
	if (v.size() > 0)
	{
		food = v.at(random(0, v.size()));
	}
}

Move Snake::move(Direction dir)
{
	Move move;
	if (dir == NORTH) {
		Node n = Node(head.x, head.y - 1);
		move = addNode(n);
	}
	else if (dir == EAST)
	{
		Node n = Node(head.x + 1, head.y);
		move = addNode(n);
	}
	else if (dir == SOUTH)
	{
		Node n = Node(head.x, head.y + 1);
		move = addNode(n);
	}
	else if (dir == WEST)
	{
		Node n = Node(head.x - 1, head.y);
		move = addNode(n);
	}
	else
	{
		throw "Niedozwolony kierunek";
	}
	return move;
}

bool Snake::canMove(Direction dir)
{
	if (dir == NORTH)
	{
		auto search = set.find(std::make_pair(head.x, head.y - 1));
		if (search != set.end() || head.y - 1 < 0)
		{
			return false;
		}
		return true;
	}
	else if (dir == EAST)
	{
		auto search = set.find(std::make_pair(head.x + 1, head.y));
		if (search != set.end() || head.x + 1 >= Snake::BOARD_SIZE)
		{
			return false;
		}
		return true;
	}
	else if (dir == SOUTH)
	{
		auto search = set.find(std::make_pair(head.x, head.y + 1));
		if (search != set.end() || head.y + 1 >= Snake::BOARD_SIZE)
		{
			return false;
		}
		return true;
	}
	else if (dir == WEST)
	{
		auto search = set.find(std::make_pair(head.x - 1, head.y));
		if (search != set.end() || head.x - 1 < 0)
		{
			return false;
		}
		return true;
	}
	return false;
}

//							Node(x,y)
bool Snake::canMove(std::pair<int, int> node, Direction dir)
{
	if (node.first < 0 || node.first >= BOARD_SIZE || node.second < 0 || node.second >= BOARD_SIZE)
	{
		return false;
	}
	if (dir == NORTH)
	{
		auto search = set.find(std::make_pair(node.first, node.second - 1));
		if (search != set.end() || node.second - 1 < 0)
		{
			return false;
		}
		return true;
	}
	else if (dir == EAST)
	{
		auto search = set.find(std::make_pair(node.first + 1, node.second));
		if (search != set.end() || node.first + 1 >= Snake::BOARD_SIZE)
		{
			return false;
		}
		return true;
	}
	else if (dir == SOUTH)
	{
		auto search = set.find(std::make_pair(node.first, node.second + 1));
		if (search != set.end() || node.second + 1 >= Snake::BOARD_SIZE)
		{
			return false;
		}
		return true;
	}
	else if (dir == WEST)
	{
		auto search = set.find(std::make_pair(node.first - 1, node.second));
		if (search != set.end() || node.first - 1 < 0)
		{
			return false;
		}
		return true;
	}
	return false;
}

void Snake::updateSet()
{
	set.clear();
	for (auto &node : this->nodes)
	{
		set.insert(std::make_pair(node.x, node.y));
	}
}

void Snake::startTime()
{
	time = std::chrono::high_resolution_clock::now();
}

void Snake::saveData()
{
	std::ofstream outfile(Snake::outFileName, std::ios_base::app);

	if (outfile.is_open())
	{
		outfile << "\n" << score << ";" << timeToString(time, std::chrono::high_resolution_clock::now()) << ";" << movementCounter;
		outfile.close();
	}
}

const Node& Snake::getNullNode()
{
	static Node node(INT_MAX, INT_MAX);
	return node;
}