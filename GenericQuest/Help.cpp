#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Color.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "Tween.h"
#include "Input.h"
#include "BranchManager.h"
#include "Branch.h"
#include "Help.h"

Help::Help(BranchManager* bm) : Branch(bm)
{
	timer.reset();
	manager->setInMenu(true);

	frame = new Frame("help.fram", 12, -16);

	Text* message = new Text(false, "", true, 0, 0, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 0, 0, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Back", true, 0, 0, 0, 0);

	menu = new Menu(message, cursor, 38, 1, 72, 80);
	menu->addMember(option1);

	tween = new Tween(SinOut, frame, 12, 3, 0.3f);
	tween->add(menu);
	tween->play();

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
			myTweens.at(0)->restart(12, -18);
			myTweens.at(0)->setDuration(0.3f);
		}
	}
}

void Help::input(float delta)
{
}

void Help::end(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = Start;
			myTweens.at(0)->restart(12, 3);
		}
	}
	if (myTweens.at(0)->isFinished())
	{
		Input::clear();
		manager->setInMenu(false);
		manager->pop();
	}
}