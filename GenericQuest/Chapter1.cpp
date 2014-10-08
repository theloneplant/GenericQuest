#include "stdafx.h"
#include "Input.h"
#include "Tween.h"
#include "Frame.h"
#include "Text.h"
#include "BranchManager.h"
#include "Branch.h"
#include "AdventureStart.h"
#include "Chapter1.h"

Chapter1::Chapter1(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	text1 = new Text(false, "Chapter 1", true, 50, 500, 0, 1);
	text1->setPosition(CONSOLE_WIDTH / 2 - text1->getDimension().x / 2, 10);
	text2 = new Text(false, "Welcome to <AREA>", true, 50, 500, 0, 1);
	text2->setPosition(CONSOLE_WIDTH / 2 - text2->getDimension().x / 2, 12);
	text2->setPaused(true);

	myFrames.push_back(text1);
	myFrames.push_back(text2);
}

Chapter1::~Chapter1()
{
}

void Chapter1::update(float delta)
{
	Branch::update(delta);
}

void Chapter1::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Chapter1::start(float delta)
{
	if (timer.getTime() > 1.5)
	{
		state = Input;
		text2->setPaused(false);
	}
}

void Chapter1::input(float delta)
{
	if (text2->isFinished())
	{
		timer.reset();
		state = End;
	}
}

void Chapter1::end(float delta)
{
	if (timer.getTime() > 1)
		manager->swap(new AdventureStart(manager));
}