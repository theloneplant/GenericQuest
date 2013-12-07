#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
{
	start = clock();
	oldTime = start;
}

void Timer::reset()
{
	start = clock();
	oldTime = start;
}

float Timer::getDelta()
{
	float delta = ((clock() - oldTime) / 1000.0f);
	oldTime = clock();
	return delta;
}

float Timer::getTime()
{
	return ((clock() - start) / 1000.0f);
}

bool Timer::hasElapsed(float elapsed)
{
	return getTime() > elapsed;
}