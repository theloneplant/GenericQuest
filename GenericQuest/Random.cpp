#include "stdafx.h"
#include "Random.h"

void Random::init()
{
	srand(time(0));
}

int Random::random(int low, int high)
{
	return rand() % high + low;
}