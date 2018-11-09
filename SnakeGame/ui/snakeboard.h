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
	SnakeBoard(BaseSolver *bs, Snake *s, QWidget *parent = nullptr);
	void initScene();
	void drawLines();
	void paintSnakeNormalMove();
	void paintSnakeEatenFoodMove();
	void paintSnakeBody(const Node &n, Direction dirP, Direction dirN);
	void paintSnakeHead(const Node &n, Direction dir);
	void paintSnakeTail(const Node &n, Direction dir);
	void paintFood(const Node &n);
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
	QMap<std::string, QGraphicsPixmapItem*> map;
};

#endif // SNAKEBOARD_H
