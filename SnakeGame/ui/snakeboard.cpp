#include "snakeboard.h"

SnakeBoard::SnakeBoard(BaseSolver *bs, Snake *s, QWidget *parent) :
	QGraphicsView(parent)
{
	graphics = new Graphics();
	solver = bs;
	snake = s;
	setFixedSize(static_cast<int>(SnakeBoard::boardPixelSize), static_cast<int>(SnakeBoard::boardPixelSize));
	setFrameStyle(QFrame::Panel | QFrame::Plain);
	setFocusPolicy(Qt::StrongFocus);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	initScene();
}

void SnakeBoard::initScene()
{
	scene = new QGraphicsScene();
	scene->setSceneRect(0, 0, SnakeBoard::boardPixelSize, SnakeBoard::boardPixelSize);
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
	item->setPixmap(QPixmap((graphics->getPath() + "bg.jpg").c_str()).scaled(static_cast<int>(SnakeBoard::boardPixelSize), static_cast<int>(SnakeBoard::boardPixelSize)));
	scene->addItem(item);
	setScene(scene);

	drawLines();
}

void SnakeBoard::paintSnakeNormalMove()
{
	if (map.contains("tail") && map.contains("pre_tail") && map.contains("head"))
	{
		scene->removeItem(map["tail"]);
		scene->removeItem(map["pre_tail"]);
		scene->removeItem(map["head"]);
	}

	Direction tailDir = snake->getTailDirection();
	paintSnakeHead(snake->head, snake->getHeadDirection());
	paintSnakeTail(snake->tail, tailDir);

	Node prev2tail = snake->getNode(snake->nodes.size() - 3);

	paintSnakeBody(snake->prevTail, snake->prevTail.getDirection(prev2tail), snake->getNode(snake->nodes.size() - 2).getDirection(snake->tail));

	//drukowanie szyi
}

void SnakeBoard::paintSnakeEatenFoodMove()
{
	if (map.contains("head"))
	{
		scene->removeItem(map["head"]);
	}

	Direction headDir = snake->getHeadDirection();
	paintSnakeHead(snake->head, headDir);

	Node nextHead = snake->getNode(1);
	paintSnakeBody(nextHead, headDir, snake->getNode(2).getDirection(nextHead));
}

void SnakeBoard::paintSnakeHead(const Node &n, Direction dir)
{
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
	tmp->setPos(n.x * SnakeBoard::cellPixelSize, n.y * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	map["head"] = tmp;
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
	map["pre_tail"] = tmp;
}

void SnakeBoard::paintSnakeTail(const Node &n, Direction dir)
{
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
	tmp->setPos(n.x * SnakeBoard::cellPixelSize, n.y * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	map["tail"] = tmp;
}

void SnakeBoard::paintFood(const Node & n)
{
	QGraphicsPixmapItem *tmp = new QGraphicsPixmapItem(*(graphics->food));
	tmp->setPos(n.x * SnakeBoard::cellPixelSize, n.y * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
}

void SnakeBoard::sleep()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(SnakeBoard::sleepTime));
}

void SnakeBoard::play()
{
	paintSnakeNormalMove();
	paintFood(snake->food);

	Move move;
	while (true)
	{
		QCoreApplication::processEvents();
		scene->update();
		sleep();

		move = solver->nextMove(snake);

		try
		{
			if (move == COLLISION)
			{
				break;
			}
			else if (move == NORMAL)
			{
				paintSnakeNormalMove();
			}
			else if (move == EATEN_FOOD)
			{
				paintSnakeEatenFoodMove();
			}
		}
		catch (const char *e) {
			qDebug(e);
			break;
		}
	}
}

void SnakeBoard::drawLines()
{
	for (size_t i = 0; i < Snake::boardSize; i++)
	{
		scene->addLine(0, i * SnakeBoard::cellPixelSize, width(), i * SnakeBoard::cellPixelSize, Qt::DashLine);
		scene->addLine(i * SnakeBoard::cellPixelSize, 0, i * SnakeBoard::cellPixelSize, height(), Qt::DashLine);
	}
}