#ifndef MOVETHREAD_H
#define MOVETHREAD_H

#include "ai/basesolver.h"
#include <QThread>
#include <qelapsedtimer.h>

class MoveThread : public QThread
{
	Q_OBJECT

signals:
	void moveDone(QString name, Move move, Snake snake);

public:
	MoveThread(QString name, Snake snake, BaseSolver *solver);
	Snake* getSnake();
	static qint64 sleepTime;

private:
	void run() override;
	int exec();
	BaseSolver *solver;
	QString name;
	Snake snake;
	QElapsedTimer stopwatch;
};

#endif // MOVETHREAD_H