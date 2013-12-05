#include "stdafx.h"
#include "Color.h"
#include "Character.h"
#include "Enemy.h"
#include "Input.h"
#include "Tween.h"
#include "Frame.h"
#include "Text.h"
#include "Animation.h"
#include "Menu.h"
#include "BranchManager.h"
#include "Branch.h"
#include "Combat.h"
#include "Ch1Box.h"
#include "Ch1Combat1.h"

Ch1Combat1::Ch1Combat1(BranchManager* bm, int input) : Branch(bm)
{
	timer.reset();

	if (input == 0)
		text = new Text(true, "adventure/ch1inn.txt", true, 20, 500, 0, 1);
	else if (input == 1)
		text = new Text(true, "adventure/ch1blacksmith.txt", true, 20, 500, 0, 1);
	else if (input == 2)
		text = new Text(true, "adventure/ch1chapel.txt", true, 20, 500, 0, 1);
	else if (input == 3)
		text = new Text(true, "adventure/ch1graveyard.txt", true, 20, 500, 0, 1);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "I'm ready!", false, 0, 0, 0, 0);

	menu = new Menu(message, cursor, 2, text->getDimension().y + text->getPosition().y + 1, 72, 80);
	menu->addMember(option1);
	menu->setHidden(true);

	myFrames.push_back(text);
	myFrames.push_back(menu);
}

Ch1Combat1::~Ch1Combat1()
{
}

void Ch1Combat1::update(float delta)
{
	Branch::update(delta);
}

void Ch1Combat1::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Ch1Combat1::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		menu->setHidden(false);
		timer.reset();
	}
}

void Ch1Combat1::input(float delta)
{
	if (menu->input() == 0)
		manager->swap(new Combat (manager, new Ch1Box(manager), Ghoul));
}

void Ch1Combat1::end(float delta)
{
}