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
#include "MainMenu.h"

MainMenu::MainMenu(BranchManager* bm)
{
	Branch::Branch(bm);
	manager = bm;
	timer.reset();

	//Text* text = new Text(true, "Test.txt", true, 15, 500, 1, 1);
	title = new Frame("genericquest.fram", 1, 9);
	sword = new Animation("genericsword.anim", 37, -40, true, false, 7);
	sword->setForegroundColor(Color::FG_LIGHTMAGENTA);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Frame* option1 = new Frame("option1.fram", 0, 0);
	Frame* option2 = new Frame("option2.fram", 0, 2);
	Frame* option3 = new Frame("option3.fram", 0, 4);

	menu = new Menu(message, cursor, option1, 20, 16, 72, 80);
	menu->addMember(option2);
	menu->addMember(option3);
	menu->setHidden(true);

	Tween* tween = new Tween(SinIn, sword, 37, 1, .75);
	myTweens.push_back(tween);

	myFrames.push_back(title);
	myFrames.push_back(sword);
	myFrames.push_back(menu);
}

MainMenu::~MainMenu()
{
	delete title, sword, menu;
}

void MainMenu::update(float delta)
{
	Branch::update(delta);
}

void MainMenu::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void MainMenu::start(float delta)
{
	if (sword->isFinished())
	{
		state = Input;
		menu->setHidden(false);

		Input::clear();
	}

	for (int i = 0; i < myTweens.size(); i++)
	{
		if (myTweens.at(0)->isFinished())
			sword->play();

		myTweens.at(i)->update();
	}

	for(int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
		//myFrames.at(i)->setPosition(30 + 5 * (i + 2) * sin(static_cast<double>(GetTickCount()) / 300 + ((i + 1) * 90)), (i) * 3 + 1);
	}
}

void MainMenu::input(float delta)
{
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
			manager->push(new Help(manager));
		}
		if (temp == 2)
		{
			exit(EXIT_SUCCESS);
		}
	}

	for(int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->update(delta);
		//myFrames.at(i)->setPosition(30 + 5 * (i + 2) * sin(static_cast<double>(GetTickCount()) / 300 + ((i + 1) * 90)), (i) * 3 + 1);
	}
}

void MainMenu::end(float delta)
{
}
