#include "mainwindow.h"

MainWindow::MainWindow()
{
	setWindowTitle(tr("Snake"));
	connect(&timer, SIGNAL(timeout()), this, SLOT(reloadStopwatch()));

	btnStart = new QPushButton("Start");
	btnStart->setFont(QFont("Comic Sans MS", 16));
	connect(btnStart, SIGNAL(released()), this, SLOT(handleButton()));

	Snake snake = Snake(Node(Snake::BOARD_SIZE / 2, Snake::BOARD_SIZE - 4), Node(Snake::BOARD_SIZE / 2, Snake::BOARD_SIZE - 3),
		Node(Snake::BOARD_SIZE / 2, Snake::BOARD_SIZE - 2), Node(Snake::BOARD_SIZE / 2, 1));

	mapThreads["random"] = qMakePair(new MoveThread("random", snake, new RandomSolver()), new SnakeWindow("Losowy"));
	mapThreads["hamilton"] = qMakePair(new MoveThread("hamilton", snake, new HamiltonSolver()), new SnakeWindow("Hamilton"));
	mapThreads["greedy"] = qMakePair(new MoveThread("greedy", snake, new GreedySolver()), new SnakeWindow("Zachlanny"));
	mapThreads["a*"] = qMakePair(new MoveThread("a*", snake, new AStarSolver()), new SnakeWindow("A*"));

	QWidget *wdg = new QWidget(this);
	QGridLayout *layout = new QGridLayout(wdg);
	layout->addWidget(btnStart, 0, 0, 1, 3);

	QMapIterator<QString, QPair<MoveThread*, SnakeWindow*>> it(mapThreads);
	int w = 1, k = 0;
	while (it.hasNext())
	{
		it.next();
		connect(it.value().first, SIGNAL(moveDone(QString, Move, Snake)), this, SLOT(updateGUI(QString, Move, Snake)));

		layout->addWidget(it.value().second, w, k, 1, 1);
		k++;
		if (k > 1)
		{
			w++;
			k = 0;
		}

		it.value().second->board->paintSnake(snake);
		it.value().second->board->paintFood(snake);
	}

	wdg->setLayout(layout);
	setCentralWidget(wdg);
}

void MainWindow::handleButton()
{
	btnStart->setEnabled(false);
	timer.start();

	QMapIterator<QString, QPair<MoveThread*, SnakeWindow*>> it(mapThreads);
	while (it.hasNext())
	{
		it.next();
		it.value().first->start();
	}
	stopwatch.start();
}

void MainWindow::updateGUI(QString name, Move move, Snake snake)
{
	if (move == COLLISION)
	{
		mapThreads[name].second->board->paintGameOver();
		mapThreads[name].first->terminate();
	}
	else if (move == NORMAL)
	{
		mapThreads[name].second->board->paintSnake(snake);
	}
	else if (move == EATEN_FOOD)
	{
		mapThreads[name].second->board->paintSnake(snake);
		mapThreads[name].second->board->paintFood(snake);
		mapThreads[name].second->setScore(QString::number(snake.score));
	}
	mapThreads[name].second->update();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	exit(0);
}

void MainWindow::reloadStopwatch()
{
	QMapIterator<QString, QPair<MoveThread*, SnakeWindow*>> it(mapThreads);
	while (it.hasNext())
	{
		it.next();
		if (!it.value().first->getSnake()->isGameOver)
		{
			it.value().second->setStopwatch(QString::number((double)stopwatch.elapsed() / 1000, 'f', 1));
		}
	}
}