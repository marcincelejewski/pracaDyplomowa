#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui/snakewindow.h"

#include <QFrame>
#include <QMainWindow>
#include <QtWidgets>

class SnakeWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();

private slots:
	void handleButton();

private:
	SnakeWindow *snakeWindow;
	QPushButton *btnStart;
protected:
	void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
