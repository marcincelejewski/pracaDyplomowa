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
	SnakeWindow(BaseSolver *solver, Snake *snake, std::string aiDesc);
	void play();
	void startTimer();

public slots:
	void reload();

private:
	SnakeBoard *board;
	QLabel* lblTimer;
	QLabel* lblScore;
	QLabel* lblAi;

	QLabel* timerTxt;
	QLabel* scoreTxt;
	QLabel* aiTxt;

	QTimer *timer;
};

#endif // SNAKEWINDOW_H
