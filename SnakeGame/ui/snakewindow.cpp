#include "snakewindow.h"

SnakeWindow::SnakeWindow(BaseSolver *solver, Snake *snake, const std::string &aiDesc)
{
	setFrameStyle(QFrame::Panel | QFrame::Plain);

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(reload()));

	QFont font("Comic Sans MS", 14);
	QGridLayout *layout = new QGridLayout;

	lblAi = new QLabel(this);
	lblAi->setText(aiDesc.c_str());
	lblAi->setAlignment(Qt::AlignLeft | Qt::AlignLeft);
	lblAi->setFont(font);
	lblAi->setMinimumWidth(70);
	layout->addWidget(lblAi, 0, 0, 1, 1);

	lblScore = new QLabel(this);
	lblScore->setText("Wynik:");
	lblScore->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	lblScore->setFont(font);
	layout->addWidget(lblScore, 0, 2, 1, 1);

	scoreTxt = new QLabel(this);
	scoreTxt->setText("0");
	scoreTxt->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	scoreTxt->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
	scoreTxt->setFont(font);
	scoreTxt->setMinimumWidth(70);
	layout->addWidget(scoreTxt, 0, 3, 1, 1);

	lblTimer = new QLabel(this);
	lblTimer->setText("Czas:");
	lblTimer->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	lblTimer->setFont(font);
	layout->addWidget(lblTimer, 0, 4, 1, 1);

	timerTxt = new QLabel(this);
	timerTxt->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	timerTxt->setText("0");
	timerTxt->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
	timerTxt->setFont(font);
	timerTxt->setMinimumWidth(70);
	layout->addWidget(timerTxt, 0, 5, 1, 1);

	board = new SnakeBoard(solver, snake, this);
	layout->addWidget(board, 1, 0, 1, 6);

	setLayout(layout);
}

void SnakeWindow::play()
{
	startTimer();
	board->play();
}

void SnakeWindow::startTimer()
{
	timer->start(SnakeBoard::sleepTime / 4);
}

void SnakeWindow::reload()
{
	if (board->isGameOver())
	{
		timer->stop();
	}
	else {
		scoreTxt->setText(std::to_string(board->getScore()).c_str());
		std::stringstream stream;
		stream << std::fixed << std::setprecision(1) << board->getGameTime();
		timerTxt->setText(stream.str().c_str());
	}
}