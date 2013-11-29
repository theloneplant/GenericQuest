#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "BranchManager.h"
#include "Branch.h"

Branch::Branch()
{
	state = Start;
}

Branch::Branch(BranchManager* bm)
{
	Branch::Branch();
	manager = bm;
}

Branch::~Branch()
{
}

void Branch::update(float delta)
{
	switch(state)
	{
		case Start:
			start(delta);
			break;
		case Input:
			input(delta);
			break;
		case End:
			end(delta);
			break;
	}
}

void Branch::draw(Canvas* canvas)
{
	for(unsigned int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->draw(canvas);
	}
}

void Branch::start(float delta)
{
}

void Branch::input(float delta)
{
}

void Branch::end(float delta)
{
}

void Branch::setState(State newState)
{
	state = newState;
}