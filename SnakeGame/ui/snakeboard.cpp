#include "snakeboard.h"

SnakeBoard::SnakeBoard(QWidget *parent) :
	QGraphicsView(parent)
{
	graphics = new Graphics();

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
	item->setPixmap(QPixmap((QString(Graphics::path) + "bg.jpg")).scaled(static_cast<int>(SnakeBoard::boardPixelSize), static_cast<int>(SnakeBoard::boardPixelSize)));
	scene->addItem(item);
	setScene(scene);

	drawLines();
}

void SnakeBoard::paintSnakeHead(const Snake& snake)
{
	Direction dir = snake.getHeadDirection();
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
	tmp->setPos(snake.head.first * SnakeBoard::cellPixelSize, snake.head.second * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	list.append(tmp);
}

void SnakeBoard::paintSnakeBody(const Node &n, const Direction &dirP, const Direction &dirN)
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
	tmp->setPos(n.first * SnakeBoard::cellPixelSize, n.second * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	list.append(tmp);
}

void SnakeBoard::paintSnakeTail(const Snake& snake)
{
	Direction dir = snake.getTailDirection();
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
	tmp->setPos(snake.tail.first * SnakeBoard::cellPixelSize, snake.tail.second * SnakeBoard::cellPixelSize);
	tmp->setScale(scaleRatio);
	scene->addItem(tmp);
	list.append(tmp);
}

void SnakeBoard::paintFood(const Snake& snake)
{
	if (food)
	{
		scene->removeItem(food);
	}
	food = new QGraphicsPixmapItem(*(graphics->food));
	food->setPos(snake.food.first * SnakeBoard::cellPixelSize, snake.food.second * SnakeBoard::cellPixelSize);
	food->setScale(scaleRatio);
	scene->addItem(food);
}

void SnakeBoard::paintSnake(const Snake& snake)
{
	for (auto l : list)
	{
		scene->removeItem(l);
	}
	list.clear();

	size_t counter = 0;
	for (auto node : snake.nodes)
	{
		if (node == snake.head)
		{
			paintSnakeHead(snake);
		}
		else if (node == snake.tail)
		{
			paintSnakeTail(snake);
		}
		else
		{
			paintSnakeBody(node, getDirection(node, snake.getNode(counter - 1)), getDirection(node, snake.getNode(counter + 1)));
		}
		counter++;
	}
}

void SnakeBoard::paintGameOver()
{
	QPixmap pm = QPixmap((QString(Graphics::path) + "gameover.png")).scaled(static_cast<int>(SnakeBoard::boardPixelSize), static_cast<int>(SnakeBoard::boardPixelSize));
	QGraphicsPixmapItem *item = new QGraphicsPixmapItem();
	item->setPixmap(pm);

	item->setPos((scene->width() - pm.width()) / 2, (scene->height() - pm.height()) / 2);
	item->scale();
	scene->addItem(item);
}

void SnakeBoard::drawLines()
{
	for (size_t i = 0; i < Snake::BOARD_SIZE; i++)
	{
		scene->addLine(0, i * SnakeBoard::cellPixelSize, width(), i * SnakeBoard::cellPixelSize, Qt::DashLine);
		scene->addLine(i * SnakeBoard::cellPixelSize, 0, i * SnakeBoard::cellPixelSize, height(), Qt::DashLine);
	}
}