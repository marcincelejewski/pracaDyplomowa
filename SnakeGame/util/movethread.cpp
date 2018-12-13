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
	//board->timer->start(SnakeBoard::sleepTime / 10);
	Move move;
	while (true)
	{
		//moveTime = std::chrono::high_resolution_clock::now();

		move = solver->nextMove(&snake);
		if (move == COLLISION)
		{
			snake.isGameOver = true;
		}
		emit(moveDone(name, move, snake));
		msleep(100);

		//msleep(sleepTime - board->getMoveTime());
	}
	return 0;
}