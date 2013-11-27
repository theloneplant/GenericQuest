#include "stdafx.h"
#include "Random.h"

void Random::init()
{
	srand(static_cast<unsigned int>(time(0)));
}

int Random::random(int low, int high)
{
	return rand() % high + low;
}