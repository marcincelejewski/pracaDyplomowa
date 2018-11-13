#include "mainwindow.h"
#include "ui/snakewindow.h"
#include "ai/randomsolver.h"

MainWindow::MainWindow()
{
	setWindowTitle(tr("Snake"));
	btnStart = new QPushButton("Start");
	btnStart->setFont(QFont("Comic Sans MS", 16));

	Snake *snake = new Snake(Node(Snake::boardSize / 2, Snake::boardSize - 4), Node(Snake::boardSize / 2, Snake::boardSize - 3),
		Node(Snake::boardSize / 2, Snake::boardSize - 2), Node(Snake::boardSize / 2, 1));

	BaseSolver * solver = new RandomSolver;
	snakeWindow = new SnakeWindow(solver, snake, "Losowy");

	QWidget *wdg = new QWidget(this);
	QGridLayout *layout = new QGridLayout(wdg);

	layout->addWidget(btnStart);
	layout->addWidget(snakeWindow);
	wdg->setLayout(layout);
	setCentralWidget(wdg);

	connect(btnStart, SIGNAL(released()), this, SLOT(handleButton()));
}

void MainWindow::handleButton()
{
	btnStart->setEnabled(false);
	snakeWindow->play();
}

void MainWindow::closeEvent(QCloseEvent * event)
{
	exit(0);
}