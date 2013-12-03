#include "stdafx.h"
#include "Color.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "Branch.h"
#include "GameOver.h"

GameOver::GameOver(BranchManager* bm, Branch* newLink,  int cr)
{
	frame = new Frame("gameover.fram", 1, 9);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Start", false, 0, 0, 0, 0);
	Text* option2 = new Text(false, "Help", false, 0, 0, 0, 2);
	Text* option3 = new Text(false, "Exit", false, 0, 0, 0, 4);

	menu = new Menu(message, cursor, 20, 16, 72, 80);
	menu->addMember(option1);
	menu->addMember(option2);
	menu->addMember(option3);
	menu->setForegroundColor(FG_BLACK);
}

GameOver::~GameOver()
{
}

void GameOver::update(float delta)
{
}

void GameOver::draw(Canvas* canvas)
{
}

void GameOver::start(float delta)
{
}

void GameOver::input(float delta)
{
}

void GameOver::end(float delta)
{
}