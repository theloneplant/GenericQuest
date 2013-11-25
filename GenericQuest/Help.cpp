#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Color.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "Tween.h"
#include "BranchManager.h"
#include "Branch.h"
#include "Help.h"

Help::Help(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();

	frame = new Frame("help.fram", 10, -20);

	Text* message = new Text(false, "", true, 0, 0, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Back", true, 0, 0, 0, 0);

	menu = new Menu(message, cursor, option1, 38, -7, 72, 80);

	Tween* tween = new Tween(SinOut, frame, 10, 5, .5);
	tween->add(menu);

	myFrames.push_back(frame);
	myFrames.push_back(menu);

	myTweens.push_back(tween);
}

Help::~Help()
{

}

void Help::update(float delta)
{
	Branch::update(delta);
}

void Help::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Help::start(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = End;
			myTweens.at(0)->restart(10, -20);
			myTweens.at(0)->setEaseType(SinOut);
		}
	}

	for (int i = 0; i < myTweens.size(); i++)
	{
		myTweens.at(i)->update();
	}
	for (int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
	}
}

void Help::input(float delta)
{
}

void Help::end(float delta)
{
	for (int i = 0; i < myTweens.size(); i++)
	{
		myTweens.at(i)->update();
	}
	for (int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
	}

	if (myTweens.at(0)->isFinished())
	{
		while (_kbhit())
		{
			_getch();
		}

		manager->pop();
	}
}