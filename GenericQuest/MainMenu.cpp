#include "stdafx.h"
#include "Canvas.h"
#include "Symbol.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "Tween.h"
#include "BranchManager.h"
#include "Branch.h"
#include "MainMenu.h"

MainMenu::MainMenu(BranchManager* bm)
{
	Branch::Branch(bm);
	/*
	Animation* chest = new Animation("pointer.anim", 15, 10, true, true, 15);
	chest->play();

	text->setVelocity(0, 0);
	title->setAcceleration(0, 0);
	title->setVelocity(0, 0);
	chest->setAcceleration(0, 0);
	chest->setVelocity(0, 0);
	*/

	Text* text = new Text(true, "Test.txt", true, 15, 500, 1, 1);
	Frame* title = new Frame("genericquest.fram", 1, 9);
	Animation* sword = new Animation("genericsword.anim", 37, 1, true, false, 7);
	sword->play();

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Frame* option1 = new Frame("option1.fram", 0, 0);
	Frame* option2 = new Frame("option2.fram", 0, 2);
	Frame* option3 = new Frame("option3.fram", 0, 4);

	menu = new Menu(message, cursor, option1, 20, 16, 72, 80);
	menu->addMember(option2);
	menu->addMember(option3);

	Tween* tween = new Tween(SinInOut, menu, 50, 16, 1);
	myTweens.push_back(tween);

	myFrames.push_back(text);
	myFrames.push_back(title);
	myFrames.push_back(sword);
	myFrames.push_back(menu);
}

MainMenu::~MainMenu()
{
}

void MainMenu::update(float delta)
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

void MainMenu::draw(Canvas* canvas)
{
	for(int i = 0; i < myFrames.size(); i++)
	{
		myFrames.at(i)->draw(canvas);
	}
}

void MainMenu::start(float delta)
{
	int temp = menu->input();
	if (temp != -1)
	{
		if (temp == 0)
		{
			cout << "NOPE";
		}
		if (temp == 1)
		{
		}
		if (temp == 2)
		{
			exit(EXIT_SUCCESS);
		}
	}

	for (int i = 0; i < myTweens.size(); i++)
	{
		if (myTweens.at(0)->isFinished())
			myTweens.at(0)->restart();

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
}

void MainMenu::end(float delta)
{
}
