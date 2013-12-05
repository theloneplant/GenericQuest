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
#include "MainMenu.h"
#include "Ch1Box.h"

Ch1Box::Ch1Box(BranchManager* bm) : Branch(bm)
{
	timer.reset();
	waiting = false;

	text = new Text(true, "adventure/ch1box.txt", true, 20, 500, 0, 1);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->play();
	Text* option1 = new Text(false, "Open the box", false, 0, 0, 0, 0);

	menu = new Menu(message, cursor, 2, text->getDimension().y + text->getPosition().y + 1, 72, 80);
	menu->addMember(option1);
	menu->setHidden(true);

	glitch = new Animation("glitch.anim", 0, 0, true, true, 10);
	glitch->pause();
	glitch->setHidden(true);

	myFrames.push_back(text);
	myFrames.push_back(menu);
	myFrames.push_back(glitch);
}

Ch1Box::~Ch1Box()
{
}

void Ch1Box::update(float delta)
{
	Branch::update(delta);
}

void Ch1Box::draw(Canvas* canvas)
{
	if (!waiting)
		Branch::draw(canvas);
}

void Ch1Box::start(float delta)
{
	if (text->isFinished())
	{
		state = Input;
		menu->setHidden(false);
		timer.reset();
	}
}

void Ch1Box::input(float delta)
{
	int input = menu->input();

	if (input != -1)
	{
		state = End;
		timer.reset();
		glitch->play();
		glitch->setHidden(false);
	}
}

void Ch1Box::end(float delta)
{
	if (glitch->isFinished() && timer.getTime() > 1.5f)
	{
		if (!waiting)
		{
			cout << '\a';
			waiting = true;
		}
		else if (waiting && timer.getTime() > 4)
		{
			manager->swap(new MainMenu(manager));
		}
	}
}