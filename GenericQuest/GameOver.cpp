#include "stdafx.h"
#include "Color.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "BranchManager.h"
#include "Branch.h"
#include "MainMenu.h"
#include "GameOver.h"

GameOver::GameOver(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	gameOver = new Frame("gameover.fram", 0, 0);
	gameOver->setPosition(CONSOLE_WIDTH / 2 - gameOver->getDimension().x / 2, 7);
	gameOver->setForegroundColor(FG_BLACK);
	death = new Frame("death.fram", 0, 0);
	death->setPosition(CONSOLE_WIDTH / 2 - death->getDimension().x / 2, 11);
	death->setForegroundColor(FG_BLACK);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Main Menu", false, 0, 0, 0, 0);
	Text* option2 = new Text(false, "Exit", false, 0, 0, 2, 2);

	menu = new Menu(message, cursor, 36, 16, 72, 80);
	menu->addMember(option1);
	menu->addMember(option2);
	menu->setHidden(true);

	myFrames.push_back(gameOver);
	myFrames.push_back(death);
	myFrames.push_back(menu);
}

GameOver::~GameOver()
{
}

void GameOver::update(float delta)
{
	Branch::update(delta);
}

void GameOver::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void GameOver::start(float delta)
{
	if (timer.getTime() > 2.5f)
	{
		state = Input;
		menu->setHidden(false);
	}
	else if (timer.getTime() > 2.1f)
	{
		death->setForegroundColor(FG_WHITE);
	}
	else if (timer.getTime() > 1.8f)
	{
		death->setForegroundColor(FG_LIGHTGRAY);
	}
	else if (timer.getTime() > 1.5f)
	{
		death->setForegroundColor(FG_DARKGRAY);
	}
	else if (timer.getTime() > 1)
	{
		gameOver->setForegroundColor(FG_WHITE);
	}
	else if (timer.getTime() > 0.6f)
	{
		gameOver->setForegroundColor(FG_LIGHTGRAY);
	}
	else if (timer.getTime() > 0.3f)
	{
		gameOver->setForegroundColor(FG_DARKGRAY);
	}
}

void GameOver::input(float delta)
{
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

void GameOver::end(float delta)
{
}