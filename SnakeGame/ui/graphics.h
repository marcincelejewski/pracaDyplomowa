#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <QGraphicsPixmapItem>

class Graphics
{
public:
	Graphics();

	QPixmap *food;

	QPixmap *tailN;
	QPixmap *tailE;
	QPixmap *tailS;
	QPixmap *tailW;

	QPixmap *headN;
	QPixmap *headE;
	QPixmap *headS;
	QPixmap *headW;

	QPixmap *bodyEW;
	QPixmap *bodyNS;
	QPixmap *bodyNE;
	QPixmap *bodyES;
	QPixmap *bodySW;
	QPixmap *bodyNW;

	static constexpr const char* path = "../SnakeGame/images/";

private:
	void readGraphics();
};

#endif // GRAPHICS_H
