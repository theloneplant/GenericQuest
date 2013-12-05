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
#include "AdventureStart.h"

AdventureStart::AdventureStart(BranchManager* bm)
{
	timer.reset();

	text = new Text(true, "adventure/start.txt", true, 20, 500, 0, 1);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Approach the caravan", false, 0, 0, 0, 0);

	menu = new Menu(message, cursor, 1, text->getDimension().y + text->getPosition().y + 1, 72, 80);
	menu->addMember(option1);
	menu->setHidden(true);

	myFrames.push_back(text);
	myFrames.push_back(menu);
}

AdventureStart::~AdventureStart()
{
}

void AdventureStart::update(float delta)
{
	Branch::update(delta);
}

void AdventureStart::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void AdventureStart::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		menu->setHidden(false);
	}
}

void AdventureStart::input(float delta)
{
}

void AdventureStart::end(float delta)
{
}