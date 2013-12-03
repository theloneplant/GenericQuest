#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Tween.h"
#include "BranchManager.h"
#include "Branch.h"

Branch::Branch(BranchManager* bm)
{
	state = Start;
	manager = bm;
}

Branch::~Branch()
{
	for (unsigned int i = 0; i < myFrames.size(); i++)
		delete myFrames.at(i);
	for (unsigned int i = 0; i < myTweens.size(); i++)
		delete myTweens.at(i);
}

void Branch::update(float delta)
{
	for (unsigned int i = 0; i < myTweens.size(); i++)
	{
		myTweens.at(i)->update();
	}
	for (unsigned int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
	}

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

void Branch::resetTimer()
{
	timer.reset();
}