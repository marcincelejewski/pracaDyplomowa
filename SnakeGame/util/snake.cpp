#include "snake.h"

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
	updateSet();
}

Node Snake::getNode(size_t index)
{
	if (index < nodes.size() && index >= 0)
		return nodes.at(index);
	return getNullNode();
}

Direction Snake::getHeadDirection()
{
	return getNode(1).getDirection(head);
}

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
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
			{
				dist[std::make_pair(i, j)] = INT_MAX;
				pred[std::make_pair(i, j)] = std::make_pair(-1, -1);
			}
		}

		//map of nodes, from node(x,y)	to lis his neighbor nodes(x,y) distance
		std::map<std::pair<int, int>, std::list<std::pair<std::pair<int, int>, int>>> map;
		for (int i = 0; i < boardSize; i++)
		{
			for (int j = 0; j < boardSize; j++)
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
			list.push_back(prev.getDirection(n));
			n = prev;
		}
	}
}

Move Snake::addNode(Node n)
{
	nodes.insert(nodes.begin(), n);

	head = nodes.front();

	if (!(n == food))
	{
		tail = prevTail;
		nodes.pop_back();
		prevTail = getNode(nodes.size() - 2);
		return NORMAL;
	}
	else
	{
		food = randomFood();
		score++;
		return EATEN_FOOD;
	}
}

Node Snake::randomFood() {
	std::vector<Node> v;
	for (size_t i = 0; i < Snake::boardSize; i++)
	{
		for (size_t j = 0; j < Snake::boardSize; j++)
		{
			auto search = set.find(std::make_pair(i, j));
			if (search == set.end())
			{
				v.push_back(Node(i, j));
			}
		}
	}
	return v.at(random(0, v.size()));
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
	updateSet();
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
		if (search != set.end() || head.x + 1 >= Snake::boardSize)
		{
			return false;
		}
		return true;
	}
	else if (dir == SOUTH)
	{
		auto search = set.find(std::make_pair(head.x, head.y + 1));
		if (search != set.end() || head.y + 1 >= Snake::boardSize)
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
	if (node.first < 0 || node.first >= boardSize || node.second < 0 || node.second >= boardSize)
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
		if (search != set.end() || node.first + 1 >= Snake::boardSize)
		{
			return false;
		}
		return true;
	}
	else if (dir == SOUTH)
	{
		auto search = set.find(std::make_pair(node.first, node.second + 1));
		if (search != set.end() || node.second + 1 >= Snake::boardSize)
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

const Node& Snake::getNullNode()
{
	static Node node(INT_MAX, INT_MAX);
	return node;
}