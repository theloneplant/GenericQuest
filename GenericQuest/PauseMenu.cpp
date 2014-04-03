#include "stdafx.h"
#include "Canvas.h"
#include "Character.h"
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
#include "MainMenu.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	frame = new Frame("pause.fram", 26, -16);

	Text* message = new Text(false, "", true, 0, 0, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 0, 0, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Resume", true, 0, 0, 1, 0);
	Text* option2 = new Text(false, "Main Menu", true, 0, 0, 0, 2);
	Text* option3 = new Text(false, "Exit", true, 0, 0, 2, 4);

	menu = new Menu(message, cursor, frame->getPosition().x + frame->getDimension().x / 2 
		- option2->getDimension().x / 2, frame->getPosition().y + 6, 72, 80);
	menu->addMember(option1);
	menu->addMember(option2);
	menu->addMember(option3);

	tween = new Tween(SinOut, frame, 26, 6, 0.3f);
	tween->add(menu);
	tween->play();

	myFrames.push_back(frame);
	myFrames.push_back(menu);

	myTweens.push_back(tween);
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::update(float delta)
{
	Branch::update(delta);
}

void PauseMenu::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void PauseMenu::start(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = End;
			myTweens.at(0)->restart(26, -18);
			myTweens.at(0)->setDuration(0.3f);
		}
		else if (input == 1)
		{
			state = End;
			manager->setMenuEnabled(false);
			manager->setGameStart(false);
			Character::player->setInit(false);
			manager->cleanSwap(new MainMenu(manager));
		}
		else if (input == 2)
		{
			_CrtDumpMemoryLeaks();
			exit(EXIT_SUCCESS);
		}
	}
}

void PauseMenu::input(float delta)
{
}

void PauseMenu::end(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			state = Start;
			myTweens.at(0)->restart(26, 6);
		}
	}

	if (myTweens.at(0)->isFinished())
	{
		Input::clear();
		manager->setInMenu(false);
		manager->pop();
	}
}