#include "snakeboard.h"

SnakeBoard::SnakeBoard(BaseSolver *solver, Snake *snake, QWidget *parent) :
	QGraphicsView(parent)
{
	graphics = new Graphics();
	this->solver = solver;
	this->snake = snake;
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(reload()));
	gameOver = false;

	setFixedSize(static_cast<int>(SnakeBoard::boardPixelSize), static_cast<int>(SnakeBoard::boardPixelSize));
	setFrameStyle(QFrame::Panel | QFrame::Plain);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	initScene();
}

void SnakeBoard::initScene()
{
	scene = new QGraphicsScene(this);
	scene->setSceneRect(0, 0, SnakeBoard::boardPixelSize, SnakeBoard::boardPixelSize);
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
	item->setPixmap(QPixmap((graphics->getPath() + "bg.jpg").c_str()).scaled(static_cast<int>(SnakeBoard::boardPixelSize), static_cast<int>(SnakeBoard::boardPixelSize)));
	scene->addItem(item);
	setScene(scene);

	drawLines();

	paintSnake();
	paintFood();
}

void SnakeBoard::paintSnakeHead()
{
	Direction dir = snake->getHeadDirection();
	QGraphicsPixmapItem *tmp;
	if (dir == NORTH)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->headN));
	}
	else if (dir == EAST)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->headE));
	}
	else if (dir == SOUTH)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->headS));
	}
	else if (dir == WEST)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->headW));
	}
	else
	{
		throw "Niedozwolony kierunek HEAD";
	}
	tmp->setPos(snake->head.x * SnakeBoard::cellPixelSize, snake->head.y * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	list.append(tmp);
}

void SnakeBoard::paintSnakeBody(const Node &n, Direction dirP, Direction dirN)
{
	QGraphicsPixmapItem *tmp;
	if ((dirP == NORTH && dirN == SOUTH) || (dirN == NORTH && dirP == SOUTH))
	{
		tmp = new QGraphicsPixmapItem(*(graphics->bodyNS));
	}
	else if ((dirP == NORTH && dirN == EAST) || (dirN == NORTH && dirP == EAST))
	{
		tmp = new QGraphicsPixmapItem(*(graphics->bodyNE));
	}
	else if ((dirP == NORTH && dirN == WEST) || (dirN == NORTH && dirP == WEST))
	{
		tmp = new QGraphicsPixmapItem(*(graphics->bodyNW));
	}
	else if ((dirP == SOUTH && dirN == EAST) || (dirN == SOUTH && dirP == EAST))
	{
		tmp = new QGraphicsPixmapItem(*(graphics->bodyES));
	}
	else if ((dirP == SOUTH && dirN == WEST) || (dirN == SOUTH && dirP == WEST))
	{
		tmp = new QGraphicsPixmapItem(*(graphics->bodySW));
	}
	else if ((dirP == EAST && dirN == WEST) || (dirN == EAST && dirP == WEST))
	{
		tmp = new QGraphicsPixmapItem(*(graphics->bodyEW));
	}
	else
	{
		throw "Niedozwolony kierunek BODY";
	}
	tmp->setPos(n.x * SnakeBoard::cellPixelSize, n.y * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	list.append(tmp);
}

void SnakeBoard::paintSnakeTail()
{
	Direction dir = snake->getTailDirection();
	QGraphicsPixmapItem *tmp;
	if (dir == NORTH)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->tailN));
	}
	else if (dir == EAST)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->tailE));
	}
	else if (dir == SOUTH)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->tailS));
	}
	else if (dir == WEST)
	{
		tmp = new QGraphicsPixmapItem(*(graphics->tailW));
	}
	else
	{
		throw "Niedozwolony kierunek TAIL";
	}
	tmp->setPos(snake->tail.x * SnakeBoard::cellPixelSize, snake->tail.y * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	list.append(tmp);
}

void SnakeBoard::paintFood()
{
	if (food)
	{
		scene->removeItem(food);
	}
	food = new QGraphicsPixmapItem(*(graphics->food));
	food->setPos(snake->food.x * SnakeBoard::cellPixelSize, snake->food.y * SnakeBoard::cellPixelSize);
	food->setScale(scaleRatio);
	scene->addItem(food);
}

void SnakeBoard::paintSnake()
{
	for (auto l : list)
	{
		scene->removeItem(l);
	}

	size_t counter = 0;
	for (auto node : snake->nodes)
	{
		if (node == snake->head)
		{
			paintSnakeHead();
		}
		else if (node == snake->tail)
		{
			paintSnakeTail();
		}
		else
		{
			paintSnakeBody(node, node.getDirection(snake->getNode(counter - 1)), node.getDirection(snake->getNode(counter + 1)));
		}
		counter++;
	}
}

void SnakeBoard::paintGameOver()
{
	QPixmap pm = QPixmap((graphics->getPath() + "gameover.png").c_str());
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
	item->setPixmap(pm);

	item->setPos((scene->width() - pm.width()) / 2, (scene->height() - pm.height()) / 2);
	scene->addItem(item);
}

void SnakeBoard::sleep(size_t value)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(value));
}

void SnakeBoard::play()
{
	timer->start(SnakeBoard::sleepTime / 10);
	startGameTime();
	Move move;
	while (true)
	{
		moveTime = std::chrono::high_resolution_clock::now();

		move = solver->nextMove(snake);

		try
		{
			if (move == COLLISION)
			{
				gameOver = true;
				paintGameOver();
				break;
			}
			else if (move == NORMAL)
			{
				paintSnake();
			}
			else if (move == EATEN_FOOD)
			{
				paintSnake();
				paintFood();
			}
		}
		catch (const char *e) {
			qDebug(e);
			break;
		}

		QCoreApplication::processEvents();
		scene->update();

		sleep(sleepTime - getMoveTime());
	}
}

size_t SnakeBoard::getScore()
{
	return snake->score;
}

double SnakeBoard::getGameTime()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - gameTime;
	return elapsed.count();
}

double SnakeBoard::getMoveTime()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - moveTime;
	return elapsed.count() * 1000;
}

bool SnakeBoard::isGameOver()
{
	return gameOver;
}

void SnakeBoard::drawLines()
{
	for (size_t i = 0; i < Snake::boardSize; i++)
	{
		scene->addLine(0, i * SnakeBoard::cellPixelSize, width(), i * SnakeBoard::cellPixelSize, Qt::DashLine);
		scene->addLine(i * SnakeBoard::cellPixelSize, 0, i * SnakeBoard::cellPixelSize, height(), Qt::DashLine);
	}
}

void SnakeBoard::reload()
{
	if (!gameOver)
	{
		if (getMoveTime() > sleepTime + 25)
		{
			exit(222);
		}
	}
	else
	{
		timer->stop();
	}
}

void SnakeBoard::startGameTime()
{
	gameTime = std::chrono::high_resolution_clock::now();
}