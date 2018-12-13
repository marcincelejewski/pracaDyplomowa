#include "graphics.h"

Graphics::Graphics()
{
	readGraphics();
}

void Graphics::readGraphics() {
	//food
	food = new QPixmap(QString(path) + "food.png");

	//head
	headN = new QPixmap(QString(path) + "headN.png");
	headE = new QPixmap(QString(path) + "headE.png");
	headS = new QPixmap(QString(path) + "headS.png");
	headW = new QPixmap(QString(path) + "headW.png");

	//tail
	tailN = new QPixmap(QString(path) + "tailN.png");
	tailE = new QPixmap(QString(path) + "tailE.png");
	tailS = new QPixmap(QString(path) + "tailS.png");
	tailW = new QPixmap(QString(path) + "tailW.png");

	//body
	bodyNS = new QPixmap(QString(path) + "bodyNS.png");
	bodyEW = new QPixmap(QString(path) + "bodyEW.png");
	bodyNE = new QPixmap(QString(path) + "bodyNE.png");
	bodyES = new QPixmap(QString(path) + "bodyES.png");
	bodySW = new QPixmap(QString(path) + "bodySW.png");
	bodyNW = new QPixmap(QString(path) + "bodyNW.png");
}