#include "graphics.h"
#include "snakeboard.h"

Graphics::Graphics()
{
	readGraphics();
}
const std::string& Graphics::getPath()
{
	static std::string path("../SnakeGame/images/");
	return path;
}
void Graphics::readGraphics() {
	//food
	food = new QPixmap(QPixmap((getPath() + "food.png").c_str()));

	//head
	headN = new QPixmap((getPath() + "headN.png").c_str());
	headE = new QPixmap((getPath() + "headE.png").c_str());
	headS = new QPixmap((getPath() + "headS.png").c_str());
	headW = new QPixmap((getPath() + "headW.png").c_str());

	//tail
	tailN = new QPixmap((getPath() + "tailN.png").c_str());
	tailE = new QPixmap((getPath() + "tailE.png").c_str());
	tailS = new QPixmap((getPath() + "tailS.png").c_str());
	tailW = new QPixmap((getPath() + "tailW.png").c_str());

	//body
	bodyNS = new QPixmap((getPath() + "bodyNS.png").c_str());
	bodyEW = new QPixmap((getPath() + "bodyEW.png").c_str());
	bodyNE = new QPixmap((getPath() + "bodyNE.png").c_str());
	bodyES = new QPixmap((getPath() + "bodyES.png").c_str());
	bodySW = new QPixmap((getPath() + "bodySW.png").c_str());
	bodyNW = new QPixmap((getPath() + "bodyNW.png").c_str());
}