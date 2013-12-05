#include "stdafx.h"
#include "Color.h"
#include "Character.h"
#include "Input.h"
#include "Tween.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "BranchManager.h"
#include "Branch.h"
#include "MainMenu.h"
#include "NoAdventure.h"

NoAdventure::NoAdventure(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	text = new Text(true, "adventure/noadventure.txt", true, 20, 500, 0, 1);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Main Menu", false, 0, 0, 0, 0);

	menu = new Menu(message, cursor, 2, text->getDimension().y + text->getPosition().y + 1, 72, 80);
	menu->addMember(option1);
	menu->setHidden(true);

	myFrames.push_back(text);
	myFrames.push_back(menu);
}

NoAdventure::~NoAdventure()
{
}

void NoAdventure::update(float delta)
{
	Branch::update(delta);
}

void NoAdventure::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void NoAdventure::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		menu->setHidden(false);
	}
}

void NoAdventure::input(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		if (input == 0)
		{
			manager->swap(new MainMenu(manager));
		}
	}
}

void NoAdventure::end(float delta)
{
}