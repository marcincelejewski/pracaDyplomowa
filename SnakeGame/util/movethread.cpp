#include "movethread.h"

MoveThread::MoveThread(QString name, Snake snake, BaseSolver *solver)
{
	this->name = name;
	this->snake = snake;
	this->solver = solver;
}

Snake* MoveThread::getSnake()
{
	return &snake;
}

void MoveThread::run()
{
	exec();
}

int MoveThread::exec()
{
	stopwatch.start();
	Move move;
	while (true)
	{
		stopwatch.restart();
		move = solver->nextMove(&snake);
		if (move == COLLISION)
		{
			snake.isGameOver = true;
		}
		emit(moveDone(name, move, snake));
		msleep(sleepTime - stopwatch.elapsed());

		//msleep(sleepTime - board->getMoveTime());
	}
	return 0;
}