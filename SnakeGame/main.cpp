#include "ui/mainwindow.h"
#include "ui/snakeboard.h"

#include <QApplication>
#include <sstream>

size_t Snake::BOARD_SIZE;
size_t SnakeBoard::boardPixelSize;
size_t SnakeBoard::cellPixelSize;
qint64 MoveThread::sleepTime;
double SnakeBoard::scaleRatio;

QString MainWindow::outFileName;

static const QString boardSizeName = "boardSize";
static const QString boardPixelSizeName = "boardPixelSize";
static const QString imagesSizeName = "imagesSize";
static const QString sleepTimeName = "sleepTime";
static const QString outFileName = "outFileName";

void readConfig()
{
	QFile file("../SnakeGame/config.properties");

	if (file.open(QFile::ReadOnly | QFile::Text))
	{
		QTextStream in(&file);
		size_t imagesSize;

		while (!in.atEnd()) {
			QString line = in.readLine();
			line = line.simplified();
			line.replace(" ", "");
			if (line.at(0) != '#')
			{
				QStringList list = line.split("=");

				if (list.size() > 1)
				{
					if (list[0] == boardSizeName)
					{
						size_t bufor = list[1].toInt();
						if (bufor > 5 && bufor <= 25)
						{
							Snake::BOARD_SIZE = bufor;
						}
						else
						{
							Snake::BOARD_SIZE = 10;
						}
						qInfo() << (boardSizeName + " = " + QString::number(Snake::BOARD_SIZE));
					}

					else if (list[0] == boardPixelSizeName)
					{
						size_t bufor = list[1].toInt();
						if (bufor > 250 && bufor <= 750)
						{
							SnakeBoard::boardPixelSize = bufor;
						}
						else
						{
							SnakeBoard::boardPixelSize = 450;
						}
						qInfo() << (boardPixelSizeName + " = " + QString::number(SnakeBoard::boardPixelSize));
					}

					else if (list[0] == imagesSizeName)
					{
						size_t bufor = list[1].toInt();
						if (bufor > 10 && bufor <= 100)
						{
							imagesSize = bufor;
						}
						else
						{
							imagesSize = 450;
						}
						qInfo() << (imagesSizeName + " = " + QString::number(imagesSize));
					}

					else if (list[0] == sleepTimeName)
					{
						qint64 bufor = list[1].toInt();
						if (bufor > 50 && bufor <= 1000)
						{
							MoveThread::sleepTime = bufor;
						}
						else
						{
							MoveThread::sleepTime = 125;
						}
						qInfo() << (sleepTimeName + " = " + QString::number(MoveThread::sleepTime));
					}
					else if (list[0] == outFileName)
					{
						MainWindow::outFileName = list[1];
						qInfo() << (outFileName + " = " + MainWindow::outFileName);
					}
				}
			}
		}
		file.close();

		SnakeBoard::cellPixelSize = SnakeBoard::boardPixelSize / Snake::BOARD_SIZE;
		qInfo() << ("cellPixelSize = " + QString::number(SnakeBoard::cellPixelSize));

		SnakeBoard::scaleRatio = double(SnakeBoard::cellPixelSize) / double(imagesSize);
		qInfo() << ("scaleRatio = " + QString::number(SnakeBoard::scaleRatio));
	}
}

int main(int argc, char *argv[])
{
	qRegisterMetaType<Move>("Move");
	qRegisterMetaType<Snake>("Snake");
	readConfig();
	QApplication a(argc, argv);
	MainWindow window;
	window.show();

	return a.exec();
}