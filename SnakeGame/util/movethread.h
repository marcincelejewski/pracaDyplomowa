#ifndef MOVETHREAD_H
#define MOVETHREAD_H

#include "ai/basesolver.h"
#include <QThread>

class MoveThread : public QThread
{
	Q_OBJECT

signals:
	void moveDone(QString name, Move move, Snake snake);

public:
	MoveThread(QString name, Snake snake, BaseSolver *solver);
	Snake* getSnake();

private:
	void run() override;
	int exec();
	BaseSolver *solver;
	QString name;
	Snake snake;
};

#endif // MOVETHREAD_H