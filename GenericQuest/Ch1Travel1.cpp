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
#include "Combat.h"
#include "Ch1Travel2.h"
#include "Ch1Travel1.h"

Ch1Travel1::Ch1Travel1(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	text = new Text(true, "adventure/ch1travel1.txt", true, 20, 500, 0, 1);

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

Ch1Travel1::~Ch1Travel1()
{
}

void Ch1Travel1::update(float delta)
{
	Branch::update(delta);
}

void Ch1Travel1::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void Ch1Travel1::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		menu->setHidden(false);
		timer.reset();
	}
}

void Ch1Travel1::input(float delta)
{
	if (menu->input() == 0)
		manager->swap(new Combat (manager, new Ch1Travel2(manager)));
}

void Ch1Travel1::end(float delta)
{
}