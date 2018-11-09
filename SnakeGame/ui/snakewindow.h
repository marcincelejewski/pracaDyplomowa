#ifndef SNAKEWINDOW_H
#define SNAKEWINDOW_H

#include <QFrame>
#include <QMainWindow>
#include <QtWidgets>

class SnakeBoard;

class SnakeWindow : public QMainWindow
{
	Q_OBJECT

public:
	SnakeWindow();

private slots:
	void handleButton();

private:
	SnakeBoard *board;
	QPushButton *btnStart;
};

#endif // SNAKEWINDOW_H
