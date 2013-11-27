#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
{
	start = GetTickCount();
	oldTime = start;
}

void Timer::reset()
{
	start = GetTickCount();
	oldTime = start;
}

float Timer::getDelta()
{
	float delta = ((GetTickCount() - oldTime) / 1000.0f);
	oldTime = GetTickCount();
	return delta;
}

float Timer::getTime()
{
	return ((GetTickCount() - start) / 1000.0f);
}

bool Timer::hasElapsed(float elapsed)
{
	return getTime() > elapsed;
}