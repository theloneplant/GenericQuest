#include "stdafx.h"
#include "Random.h"

int Random::random(int low, int high)
{
	int random = rand();
	int final = random % (high - low + 1) + low;
	return final;
}