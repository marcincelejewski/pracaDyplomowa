#include "ai/basesolver.h"

void BaseSolver::runClock()
{
	clock = std::chrono::high_resolution_clock::now();
}

double BaseSolver::getClock()
{
	std::chrono::duration<double> elapsed = std::chrono::high_resolution_clock::now() - clock;
	return elapsed.count();
}