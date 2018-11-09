#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_snakegame.h"

class SnakeGame : public QMainWindow
{
	Q_OBJECT

public:
	SnakeGame(QWidget *parent = Q_NULLPTR);

private:
	Ui::SnakeGameClass ui;
};
