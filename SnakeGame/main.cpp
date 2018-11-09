#include "ui/snakewindow.h"
#include "ui/snakeboard.h"

#include <QApplication>
#include <fstream>
#include <sstream>

size_t Snake::boardSize;
size_t SnakeBoard::boardPixelSize;
size_t SnakeBoard::cellPixelSize;
size_t SnakeBoard::sleepTime = 50;
double SnakeBoard::scaleRatio;

static const std::string boardSizeName = "boardSize";
static const std::string boardPixelSizeName = "boardPixelSize";
static const std::string imagesSizeName = "imagesSize";
static const std::string sleepTimeName = "sleepTime";

void readConfig()
{
	std::ifstream file("../SnakeGame/config.properties");
	if (file.is_open()) {
		size_t imagesSize = 0;
		std::string line;
		while (getline(file, line)) {
			std::remove_if(line.begin(), line.end(), isspace);
			if (line.at(0) != '#')
			{
				std::size_t index = line.find_first_of('=');
				size_t value = 0;
				if (line.substr(0, index) == boardSizeName)
				{
					std::stringstream buf(line.substr(index + 1, line.length()));
					buf >> value;
					if (value > 5 && value < 25)
					{
						Snake::boardSize = value;
					}
					else
					{
						Snake::boardSize = 10;
					}
					qInfo() << (boardSizeName + " = " + std::to_string(Snake::boardSize)).c_str();
				}
				else if (line.substr(0, index) == boardPixelSizeName)
				{
					std::stringstream buf(line.substr(index + 1, line.length()));
					buf >> value;
					if (value > 200 && value < 800)
					{
						SnakeBoard::boardPixelSize = value;
					}
					else
					{
						SnakeBoard::boardPixelSize = 600;
					}
					qInfo() << (boardPixelSizeName + " = " + std::to_string(SnakeBoard::boardPixelSize)).c_str();
				}
				else if (line.substr(0, index) == imagesSizeName)
				{
					std::stringstream buf(line.substr(index + 1, line.length()));
					buf >> value;
					if (value > 10 && value < 100)
					{
						imagesSize = value;
					}
					else
					{
						imagesSize = 50.0;
					}
					qInfo() << (imagesSizeName + " = " + std::to_string(imagesSize)).c_str();
				}
				else if (line.substr(0, index) == sleepTimeName)
				{
					std::stringstream buf(line.substr(index + 1, line.length()));
					buf >> value;
					if (value > 50 && value < 1000)
					{
						SnakeBoard::sleepTime = value;
					}
					else
					{
						SnakeBoard::sleepTime = 500;
					}
					qInfo() << (sleepTimeName + " = " + std::to_string(SnakeBoard::sleepTime)).c_str();
				}
			}
		}
		file.close();
		SnakeBoard::cellPixelSize = SnakeBoard::boardPixelSize / Snake::boardSize;
		qInfo() << ("cellPixelSize = " + std::to_string(SnakeBoard::cellPixelSize)).c_str();

		SnakeBoard::scaleRatio = double(SnakeBoard::cellPixelSize) / double(imagesSize);
		qInfo() << ("scaleRatio = " + std::to_string(SnakeBoard::scaleRatio)).c_str();
	}
}

int main(int argc, char *argv[])
{
	readConfig();
	QApplication a(argc, argv);
	SnakeWindow window;
	window.show();
	return a.exec();
}