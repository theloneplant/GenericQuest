#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Color.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "Tween.h"
#include "Input.h"
#include "BranchManager.h"
#include "Branch.h"
#include "Help.h"
#include "PlayerStats.h"
#include "MainMenu.h"

MainMenu::MainMenu(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();

	title = new Frame("genericquest.fram", 1, 9);
	title->setForegroundColor(FG_BLACK);
	sword = new Animation("genericsword.anim", 37, -40, true, false, 7);
	sword->setForegroundColor(FG_YELLOW);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Start", false, 0, 0, 0, 0);
	Text* option2 = new Text(false, "Help", false, 0, 0, 0, 2);
	Text* option3 = new Text(false, "Exit", false, 0, 0, 0, 4);

	menu = new Menu(message, cursor, option1, 20, 16, 72, 80);
	menu->addMember(option2);
	menu->addMember(option3);
	menu->setForegroundColor(FG_BLACK);

	Tween* tween = new Tween(SinIn, sword, 37, 1, .75);
	tween->play();

	myFrames.push_back(title);
	myFrames.push_back(sword);
	myFrames.push_back(menu);

	myTweens.push_back(tween);
}

MainMenu::~MainMenu()
{
	delete title, sword, menu;
}

void MainMenu::update(float delta)
{
	Branch::update(delta);

	for (unsigned int i = 0; i < myTweens.size(); i++)
	{
		myTweens.at(i)->update();
	}

	for(unsigned int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
	}
}

void MainMenu::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void MainMenu::start(float delta)
{
	if (timer.getTime() > 0.6)
	{
		state = Input;
		title->setForegroundColor(FG_WHITE);
		Input::clear();
	}
	else if (timer.getTime() > 0.4)
	{
		title->setForegroundColor(FG_LIGHTGRAY);
	}
	else if (timer.getTime() > 0.2)
		title->setForegroundColor(FG_DARKGRAY);
}

void MainMenu::input(float delta)
{
	if (myTweens.at(0)->isFinished())
	{
		sword->play();
		menu->setForegroundColor(FG_WHITE);
	}

	int temp = menu->input();
	if (temp != -1)
	{
		if (temp == 0)
		{
			MainMenu* mainMenu = new MainMenu(manager);
			manager->swap(mainMenu);
		}
		if (temp == 1)
		{
			Help* help = new Help(manager);
			manager->push(new PlayerStats(manager));
		}
		if (temp == 2)
		{
			state = End;
			timer.reset();
		}
	}
}

void MainMenu::end(float delta)
{
	if (timer.getTime() > .8)
	{
		exit(EXIT_SUCCESS);
	}
	else if (timer.getTime() > .4)
	{
		title->setForegroundColor(FG_BLACK);
		menu->setForegroundColor(FG_BLACK);
		sword->setForegroundColor(FG_BLACK);
	}
	else if (timer.getTime() > .2)
	{
		title->setForegroundColor(FG_DARKGRAY);
		menu->setForegroundColor(FG_DARKGRAY);
	}
	else if (timer.getTime() > 0)
	{
		title->setForegroundColor(FG_LIGHTGRAY);
		menu->setForegroundColor(FG_LIGHTGRAY);
		sword->setForegroundColor(FG_BROWN);
	}
}
