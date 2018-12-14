#include "astarsolver.h"

AStarSolver::AStarSolver() {
	counter = 0;
}
Move AStarSolver::nextMove(Snake * snake)
{
	Direction dir = aSearchForwardChecking(*snake, snake->food);

	if (snake->canMove(dir))
	{
		return snake->move(dir);
	}
	else
	{
		return COLLISION;
	}
}

Direction AStarSolver::aSearch(Snake snake, const Node &dest)
{
	std::vector<Node> openList;
	std::vector<Node> closeList;

	//		node			 path			 g	  h
	std::map<Node, std::pair<Node, std::pair<int, int>>> map;

	for (int i = 0; i < Snake::BOARD_SIZE; i++)
	{
		for (int j = 0; j < Snake::BOARD_SIZE; j++)
		{
			map[Node(i, j)] = std::make_pair(Node(-1, -1), std::make_pair(0, 0));
		}
	}

	map[snake.head].second.second = manhattanDistance(snake.head, dest);
	openList.push_back(snake.head);

	while (!openList.empty())
	{
		std::vector<Node> nodes;

		int max = -1;
		for (auto &n : openList)
		{
			if (sumPair(map[n].second) >= max)
			{
				if (sumPair(map[n].second) > max)
				{
					nodes.clear();
					max = sumPair(map[n].second);
				}
				nodes.push_back(n);
			}
		}
		Node now = nodes.at(random(0, nodes.size()));

		openList.erase(std::remove(openList.begin(), openList.end(), now), openList.end());
		closeList.push_back(now);

		Node north = getNeighbor(now, NORTH);
		Node south = getNeighbor(now, SOUTH);
		Node west = getNeighbor(now, WEST);
		Node east = getNeighbor(now, EAST);

		std::vector<Node> tmp;

		if (snake.canMove(north))
		{
			tmp.push_back(north);
		}
		if (snake.canMove(south))
		{
			tmp.push_back(south);
		}
		if (snake.canMove(west))
		{
			tmp.push_back(west);
		}
		if (snake.canMove(east))
		{
			tmp.push_back(east);
		}
		for (auto n : tmp)
		{
			if (std::find(closeList.begin(), closeList.end(), n) != closeList.end()) {
				continue;
			}
			if (std::find(openList.begin(), openList.end(), n) != openList.end()) {
				if (map[n].second.first > (map[now].second.first + 1))
				{
					map[n].first = now;
					map[n].second.first += 1;
				}
			}
			else
			{
				map[n] = std::make_pair(now, std::make_pair(map[now].second.first + 1, manhattanDistance(n, dest)));
				openList.push_back(n);
				if (n == dest)
				{
					Node node = openList.back();
					Node bufor;

					while (node != Node(-1, -1) && node != snake.head)
					{
						bufor = node;
						node = map[node].first;
					}
					return getDirection(snake.head, bufor);
				}
			}
		}
	}

	return ERROR_DIRECTION;
}

Direction AStarSolver::bfs(Snake snake, const Node &dest)
{
	std::queue<Node> queue;
	std::unordered_set<std::pair<size_t, size_t>, pair_hash> visited;
	std::map<Node, Node> path;

	for (int i = 0; i < Snake::BOARD_SIZE; i++)
	{
		for (int j = 0; j < Snake::BOARD_SIZE; j++)
		{
			path[Node(i, j)] = Node(-1, -1);
		}
	}

	queue.push(snake.head);

	while (!queue.empty())
	{
		Node n = queue.front();
		queue.pop();
		if (n == dest)
		{
			Node node = dest;
			Node bufor;
			while (node != Node(-1, -1) && node != snake.head)
			{
				bufor = node;
				node = path[node];
			}

			return getDirection(snake.head, bufor);
		}

		Node north = getNeighbor(n, NORTH);
		Node south = getNeighbor(n, SOUTH);
		Node west = getNeighbor(n, WEST);
		Node east = getNeighbor(n, EAST);

		std::vector<Node> tmp;

		if (snake.canMove(north))
		{
			tmp.push_back(north);
		}
		if (snake.canMove(south))
		{
			tmp.push_back(south);
		}
		if (snake.canMove(west))
		{
			tmp.push_back(west);
		}
		if (snake.canMove(east))
		{
			tmp.push_back(east);
		}
		std::random_shuffle(tmp.begin(), tmp.end());
		for (auto node : tmp)
		{
			auto search = visited.find(node);
			if (search == visited.end())
			{
				queue.push(node);
				visited.insert(node);
				path[node] = n;
			}
		}
	}
	return ERROR_DIRECTION;
}

Direction AStarSolver::aSearchForwardChecking(Snake snake, const Node &dest)
{
	Snake virSnake = Snake(snake);

	Direction realTofood = bfs(snake, dest);

	if (realTofood != ERROR_DIRECTION)
	{	//jeœli mo¿emy pod¹¿aæ za jab³uszkiem
		while (virSnake.head != dest)
		{
			virSnake.move(bfs(virSnake, dest));
		}
		Direction virtualToTail = aSearch(virSnake, virSnake.tail);

		if (virtualToTail != ERROR_DIRECTION)
		{	//jeœli zjemy jab³uszko i bêdziemy mogli pod¹¿aæ za ogonem
			return realTofood;
		}
		else
		{	//jeœli zjemy jab³uszko i nie bêdziemy mogli pod¹¿aæ za ogonem
			if (snake.nodes.size() + 1 >= pow(Snake::BOARD_SIZE, 2))
			{
				return realTofood;
			}
			//pod¹¿aj za ogonem najd³u¿sz¹ œcie¿k¹
			return snake.moveAway(snake.head, snake.tail);
		}
	}
	else
	{	//jeœli nie mo¿emy pod¹¿aæ za jab³uszkiem
		Direction realToTail = aSearch(snake, snake.tail);

		if (realToTail == ERROR_DIRECTION)
		{	//jeœli nie mo¿emy pod¹¿aæ za ogonem
			//dozwolony ruch losowy
			return snake.randomMove(snake.head);
		}

		Direction awayToTail = snake.moveAway(snake.head, snake.tail);
		if (realToTail == awayToTail)
		{
			return realToTail;
		}
		else
		{
			if (counter < 3)
			{
				counter = 0;
				return awayToTail;
			}
			else
			{
				counter++;
			}
		}

		return realToTail;
	}
	return ERROR_DIRECTION;
}

int AStarSolver::sumPair(const std::pair<int, int> &p)
{
	return p.first + p.second;
}