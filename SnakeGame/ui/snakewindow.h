#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include "ui/snakeboard.h"

#include <QtWidgets>
#include <sstream>
#include <iomanip>

class SnakeBoard;

class SnakeWindow : public QFrame
{
	Q_OBJECT

public:
	SnakeWindow(BaseSolver *solver, Snake *snake, const std::string &aiDesc);
	void startTimer();
	void play();

public slots:
	void reload();

private:
	SnakeBoard *board;
	QLabel* lblTimer;
	QLabel* lblScore;
	QLabel* lblAi;

	QLabel* timerTxt;
	QLabel* scoreTxt;

	QTimer *timer;
};

#endif // SNAKEWINDOW_H
