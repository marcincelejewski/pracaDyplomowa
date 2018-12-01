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
	SnakeBoard(BaseSolver *solver, Snake *snake, QWidget *parent = nullptr);
	void initScene();
	void drawLines();
	void paintSnakeBody(const Node &n, Direction dirP, Direction dirN);
	void paintSnakeHead();
	void paintSnakeTail();
	void paintFood();
	void paintSnake();
	void paintGameOver();
	void sleep(size_t value);
	size_t getScore();
	double getGameTime();
	double getMoveTime();
	bool isGameOver();
	void play();
	static size_t sleepTime;
	static size_t boardPixelSize;
	static size_t cellPixelSize;
	static double scaleRatio;

	std::chrono::high_resolution_clock::time_point moveTime;

public slots:
	void checkTime();

private:
	QGraphicsScene *scene;
	Graphics *graphics;
	BaseSolver *solver;
	Snake *snake;
	QList<QGraphicsPixmapItem*> list;
	QGraphicsPixmapItem *food = nullptr;
	QTimer *timer;
	bool gameOver;
};

#endif // SNAKEBOARD_H
