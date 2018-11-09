#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <QGraphicsPixmapItem>

class Graphics
{
public:
	Graphics();
	void readGraphics();
	const std::string& getPath();

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
};

#endif // GRAPHICS_H
