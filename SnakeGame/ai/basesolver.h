#ifndef BASESOLVER_H
#define BASESOLVER_H

#include "util/snake.h"

class BaseSolver
{
public:
	virtual Move nextMove(Snake *snake) = 0;
	BaseSolver() {};
};

#endif // BASESOLVER_H
