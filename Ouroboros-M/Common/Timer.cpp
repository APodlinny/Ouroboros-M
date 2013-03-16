#include "Timer.h"

using namespace Ouroboros::Common;

Timer::Timer()
{
	Init();
}

void Timer::Init()
{
	startTime = clock();
}

double Timer::GetTime()
{
	endTime = clock();

	return (endTime-startTime)/(double)CLOCKS_PER_SEC;
}