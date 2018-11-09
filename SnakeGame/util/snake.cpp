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
	static Node node(1000, 1000);
	return node;
}