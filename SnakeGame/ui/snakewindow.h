#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include "ui/snakeboard.h"

class SnakeBoard;

class SnakeWindow : public QFrame
{
	Q_OBJECT

public:
	SnakeWindow(const std::string &aiDesc);
	SnakeBoard *board;
	void setStopwatch(QString time);
	void setScore(QString score);

private:
	QLabel* lblStopwatch;
	QLabel* lblScore;
	QLabel* lblAi;
	QLabel* stopwatchTxt;
	QLabel* scoreTxt;
};

#endif // SNAKEWINDOW_H
