#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui/snakewindow.h"
#include "ai/randomsolver.h"
#include "ai/hamiltonsolver.h"
#include "ai/greedysolver.h"
#include "ai/astarsolver.h"
#include "util/movethread.h"

#include <QtConcurrent/QtConcurrentRun>
#include <QMainWindow>

class SnakeWindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
	static QString outFileName;

private slots:
	void handleButton();
	void updateGUI(QString name, Move move, Snake snake);
	void reloadLabelsTime();

signals:
	void start();

private:
	QPushButton *btnStart;
	QMap<QString, QPair<MoveThread*, SnakeWindow*>> mapThreads;
	QTimer timer;
	QElapsedTimer stopwatch;

	void closeEvent(QCloseEvent *event);
	void saveData(QString name, Snake snake);
};

#endif // MAINWINDOW_H
