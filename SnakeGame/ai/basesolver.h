#ifndef BASESOLVER_H
#define BASESOLVER_H

#include "util/snake.h"

class BaseSolver
{
public:
	virtual Move nextMove(Snake *snake) = 0;
	std::chrono::high_resolution_clock::time_point clock;
	void runClock();
	double getClock();
};

#endif // BASESOLVER_H
