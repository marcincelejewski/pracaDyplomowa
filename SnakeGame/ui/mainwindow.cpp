#include "mainwindow.h"
#include "ui/snakewindow.h"
#include "ai/randomsolver.h"
#include "ai/hamiltonsolver.h"
#include "ai/greedysolver.h"
#include "ai/astarsolver.h"

MainWindow::MainWindow()
{
	setWindowTitle(tr("Snake"));
	btnStart = new QPushButton("Start");
	btnStart->setFont(QFont("Comic Sans MS", 16));

	QWidget *wdg = new QWidget(this);
	QGridLayout *layout = new QGridLayout(wdg);
	layout->addWidget(btnStart, 0, 0, 1, 3);

	Snake *snake = new Snake(Node(Snake::BOARD_SIZE / 2, Snake::BOARD_SIZE - 4), Node(Snake::BOARD_SIZE / 2, Snake::BOARD_SIZE - 3),
		Node(Snake::BOARD_SIZE / 2, Snake::BOARD_SIZE - 2), Node(Snake::BOARD_SIZE / 2, 1));

	BaseSolver *solver;

	solver = new RandomSolver();
	snakeWindowHamilton = new SnakeWindow(solver, snake, "Losowy");
	layout->addWidget(snakeWindowHamilton, 1, 0, 1, 1);

	solver = new HamiltonSolver();
	snakeWindowHamilton = new SnakeWindow(solver, snake, "Hamilton");
	layout->addWidget(snakeWindowHamilton, 1, 1, 1, 1);

	solver = new GreedySolver;
	snakeWindowGreedy = new SnakeWindow(solver, snake, "Zachlanny");
	layout->addWidget(snakeWindowGreedy, 2, 0, 1, 1);

	solver = new AStarSolver();
	snakeWindowAstar = new SnakeWindow(solver, snake, "A*");
	layout->addWidget(snakeWindowAstar, 2, 1, 1, 1);

	wdg->setLayout(layout);
	setCentralWidget(wdg);

	connect(btnStart, SIGNAL(released()), this, SLOT(handleButton()));
}

void MainWindow::handleButton()
{
	btnStart->setEnabled(false);

	snakeWindowRandom->play();
	//snakeWindowHamilton->play();
	//snakeWindowGreedy->play();
	//snakeWindowAstar->play();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	exit(0);
}