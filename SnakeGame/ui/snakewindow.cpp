#include "snakewindow.h"

SnakeWindow::SnakeWindow(const std::string &aiDesc)
{
	setFrameStyle(QFrame::Panel | QFrame::Plain);

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

	lblStopwatch = new QLabel(this);
	lblStopwatch->setText("Czas:");
	lblStopwatch->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	lblStopwatch->setFont(font);
	layout->addWidget(lblStopwatch, 0, 4, 1, 1);

	stopwatchTxt = new QLabel(this);
	stopwatchTxt->setFrameStyle(QFrame::Panel | QFrame::Sunken);
	stopwatchTxt->setText("0");
	stopwatchTxt->setAlignment(Qt::AlignCenter | Qt::AlignCenter);
	stopwatchTxt->setFont(font);
	stopwatchTxt->setMinimumWidth(70);
	layout->addWidget(stopwatchTxt, 0, 5, 1, 1);

	board = new SnakeBoard(this);
	layout->addWidget(board, 1, 0, 1, 6);

	setLayout(layout);
}

void SnakeWindow::setStopwatch(QString time)
{
	stopwatchTxt->setText(time);
}

void SnakeWindow::setScore(QString score)
{
	scoreTxt->setText(score);
}