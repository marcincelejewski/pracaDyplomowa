#include "snakewindow.h"
#include "ui/snakeboard.h"
#include "ai/randomsolver.h"

SnakeWindow::SnakeWindow()
{
	setWindowTitle(tr("Snake"));
	btnStart = new QPushButton("Start");

	Snake *snake = new Snake(Node(Snake::boardSize / 2, Snake::boardSize - 4), Node(Snake::boardSize / 2, Snake::boardSize - 3), Node(Snake::boardSize / 2, Snake::boardSize - 2), Node(Snake::boardSize / 2, 1));

	BaseSolver * solver = new RandomSolver;
	board = new SnakeBoard(solver, snake, "Algorytm Losowy");

	QWidget *wdg = new QWidget(this);
	QGridLayout *layout = new QGridLayout(wdg);

	layout->addWidget(btnStart);
	layout->addWidget(board);

	wdg->setLayout(layout);
	setCentralWidget(wdg);

	connect(btnStart, SIGNAL(released()), this, SLOT(handleButton()));
}

void SnakeWindow::handleButton()
{
	btnStart->setVisible(false);
	board->play();
}