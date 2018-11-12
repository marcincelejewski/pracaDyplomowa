#ifndef SNAKEBOARD_H
#define SNAKEBOARD_H

#include "graphics.h"
#include "util/snake.h"
#include "ai/basesolver.h"

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsView>
#include <QtWidgets>

class SnakeBoard : public QGraphicsView
{
	Q_OBJECT

public:
	SnakeBoard(BaseSolver *bs, Snake *s, std::string aiDesc, QWidget *parent = nullptr);
	void initScene();
	void initLabels(std::string aiDesc);
	void drawLines();
	void paintSnakeBody(const Node &n, Direction dirP, Direction dirN);
	void paintSnakeHead();
	void paintSnakeTail();
	void paintFood();
	void paintSnake();
	void paintGameOver();
	void sleep();
	void play();
	static size_t sleepTime;
	static size_t boardPixelSize;
	static size_t cellPixelSize;
	static double scaleRatio;

private:
	QGraphicsScene *scene;
	Graphics *graphics;
	BaseSolver *solver;
	Snake *snake;
	QList<QGraphicsPixmapItem*> list;
	QGraphicsPixmapItem *food = nullptr;
	QLabel* lblTimer;
	QLabel* lblScore;
	QLabel* lblAi;
};

#endif // SNAKEBOARD_H
