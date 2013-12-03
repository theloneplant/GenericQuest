#include "stdafx.h"
#include "Color.h"
#include "Input.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "BranchManager.h"
#include "Branch.h"
#include "MainMenu.h"
#include "ClassChoice.h"

ClassChoice::ClassChoice(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	title = new Frame("gameover.fram", 0, 0);
	title->setPosition(CONSOLE_WIDTH / 2 - title->getDimension().x / 2, 7);
	title->setForegroundColor(FG_BLACK);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	knight = new Text(false, "Knight", false, 0, 0, 0, 0);
	ranger = new Text(false, "Ranger", false, 0, 0, 10, 0);
	wizard = new Text(false, "Wizard", false, 0, 0, 20, 0);
	knight->setForegroundColor(FG_LIGHTRED);
	ranger->setForegroundColor(FG_GREEN);
	wizard->setForegroundColor(FG_BLUE);

	menu = new Menu(message, cursor, 20, 10, 75, 77);
	menu->addMember(knight);
	menu->addMember(ranger);
	menu->addMember(wizard);

	myFrames.push_back(title);
	myFrames.push_back(menu);
}

ClassChoice::~ClassChoice()
{
}

void ClassChoice::update(float delta)
{
	Branch::update(delta);
}

void ClassChoice::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void ClassChoice::start(float delta)
{
	state = Input;
}

void ClassChoice::input(float delta)
{
	if (menu->getFocusedIndex() == 0)
	{
		knight->setForegroundColor(FG_LIGHTRED);
		ranger->setForegroundColor(FG_GREEN);
		wizard->setForegroundColor(FG_BLUE);
	}
	else if (menu->getFocusedIndex() == 1)
	{
		knight->setForegroundColor(FG_RED);
		ranger->setForegroundColor(FG_LIGHTGREEN);
		wizard->setForegroundColor(FG_BLUE);
	}
	else if (menu->getFocusedIndex() == 2)
	{
		knight->setForegroundColor(FG_RED);
		ranger->setForegroundColor(FG_GREEN);
		wizard->setForegroundColor(FG_LIGHTBLUE);
	}
	
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			manager->swap(new MainMenu(manager));
		}
		else if (input == 1)
		{
			exit(EXIT_SUCCESS);
		}
	}
}

void ClassChoice::end(float delta)
{
}