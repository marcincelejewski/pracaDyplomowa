#ifndef SNAKEBOARD_H
#define SNAKEBOARD_H

#include "ui/graphics.h"
#include "ai/basesolver.h"

#include <QGraphicsScene>
#include <QPixmap>
#include <QGraphicsView>
#include <QtWidgets>

class SnakeBoard : public QGraphicsView
{
	Q_OBJECT

public:
	SnakeBoard(QWidget *parent = nullptr);
	void initScene();
	void drawLines();
	void paintSnakeBody(const Node &n, const Direction &dirP, const Direction &dirN);
	void paintSnakeHead(const Snake& snake);
	void paintSnakeTail(const Snake& snake);
	void paintFood(const Snake& snake);
	void paintSnake(const Snake& snake);
	void paintGameOver();

	static size_t sleepTime;
	static size_t boardPixelSize;
	static size_t cellPixelSize;
	static double scaleRatio;

private:
	QGraphicsScene *scene;
	Graphics *graphics;
	QList<QGraphicsPixmapItem*> list;
	QGraphicsPixmapItem *food = nullptr;
};

#endif // SNAKEBOARD_H
