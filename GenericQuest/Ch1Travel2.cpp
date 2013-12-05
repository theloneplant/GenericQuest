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
#include "Ch1Combat1.h"
#include "Ch1Travel2.h"

Ch1Travel2::Ch1Travel2(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	text = new Text(true, "adventure/ch1travel2.txt", true, 20, 500, 0, 1);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Inn", false, 0, 0, 0, 0);
	Text* option2 = new Text(false, "Blacksmith", false, 0, 0, 0, 1);
	Text* option3 = new Text(false, "Chapel", false, 0, 0, 0, 2);
	Text* option4 = new Text(false, "Graveyard", false, 0, 0, 0, 3);

	menu = new Menu(message, cursor, 2, text->getDimension().y + text->getPosition().y + 1, 72, 80);
	menu->addMember(option1);
	menu->addMember(option2);
	menu->addMember(option3);
	menu->addMember(option4);
	menu->setHidden(true);

	myFrames.push_back(text);
	myFrames.push_back(menu);
}

Ch1Travel2::~Ch1Travel2()
{
}

void Ch1Travel2::update(float delta)
{
	Branch::update(delta);
}

void Ch1Travel2::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Ch1Travel2::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		menu->setHidden(false);
		timer.reset();
	}
}

void Ch1Travel2::input(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		manager->swap(new Ch1Combat1 (manager, input));
	}
}

void Ch1Travel2::end(float delta)
{
}