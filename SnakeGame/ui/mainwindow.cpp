#include "mainwindow.h"
#include "ui/snakewindow.h"
#include "ai/randomsolver.h"
#include "ai/hamiltonsolver.h"

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

	BaseSolver * solverRandom = new RandomSolver;
	snakeWindowRandom = new SnakeWindow(solverRandom, snake, "Losowy");
	layout->addWidget(snakeWindowRandom, 1, 0, 1, 1);

	BaseSolver * solverHamilton = new HamiltonSolver();
	snakeWindowHamilton = new SnakeWindow(solverHamilton, snake, "Hamilton");
	layout->addWidget(snakeWindowHamilton, 1, 1, 1, 1);

	wdg->setLayout(layout);
	setCentralWidget(wdg);

	connect(btnStart, SIGNAL(released()), this, SLOT(handleButton()));
}

void t(SnakeWindow* snakeWindowRandom)
{
}

void MainWindow::handleButton()
{
	btnStart->setEnabled(false);

	//snakeWindowRandom->play();
	snakeWindowHamilton->play();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	exit(0);
}