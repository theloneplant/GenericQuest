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
#include "Chapter1.h"
#include "NameChoice.h"

NameChoice::NameChoice(BranchManager* bm, Role role) : Branch(bm)
{
	timer.reset();
	Character::player->init(role);

	title = new Frame("name.fram", 0, 0);
	title->setPosition(CONSOLE_WIDTH / 2 - title->getDimension().x / 2, 7);
	title->setForegroundColor(FG_YELLOW);
	title->setHidden(true);

	welcome = new Text(false, "Get ready for <YELLOW>Adventure<LIGHTGRAY>!", true, 50, 0, 0, 0);
	welcome->setPosition(CONSOLE_WIDTH / 2 - welcome->getDimension().x / 2, 13);
	welcome->setPaused(true);

	cursor = new Animation("textcursor.anim", 0, 0, true, false, 5);
	cursor->play();

	namePrint = new Text(false, "", false, 0, 0, 0, 13);
	namePrint->setPosition(CONSOLE_WIDTH / 2 - namePrint->getDimension().x / 2, namePrint->getPosition().y);
	cursor->setPosition(namePrint->getPosition().x + namePrint->getDimension().x, namePrint->getPosition().y);
	error = new Text(false, "Enter a name less than 35 characters!", false, 0, 0, 0, 0);
	error->setPosition(CONSOLE_WIDTH / 2 - error->getDimension().x / 2, 15);
	error->setHidden(true);
	name = "";
	valid = false;

	tween = new Tween(SinOut, namePrint, 0, 0, .5);

	myFrames.push_back(title);
	myFrames.push_back(welcome);
	myFrames.push_back(cursor);
	myFrames.push_back(error);
	myFrames.push_back(namePrint);

	myTweens.push_back(tween);
}

NameChoice::~NameChoice()
{
}

void NameChoice::update(float delta)
{
	Branch::update(delta);
}

void NameChoice::draw(Canvas* canvas)
{
	Branch::draw(canvas);
}

void NameChoice::start(float delta)
{
	title->setHidden(false);
	welcome->setHidden(true);
	state = Input;
}

void NameChoice::input(float delta)
{
	if (Input::keyHit())
	{
		error->setHidden(true);
		char in = Input::get();
		if (in == 8)
		{
			if (name.length() > 0)
			{
				valid = true;
				name.pop_back();
			}
			else
				valid = false;
		}
		else if (in == 13)
		{
			if (valid)
			{
				title->setHidden(true);
				welcome->setHidden(false);
				welcome->setTypewriter(true);
				welcome->reset();
				state = End;
				timer.reset();
				tween->restart(namePrint->getPosition().x, 10);
				tween->setDuration(1);
				tween->play();
				cursor->setHidden(true);
			}
		}
		else if (name.length() >= 35)
		{
			error->setHidden(false);
			valid = false;
		}
		else if (name.length() < 35)
		{
			valid = true;
			name.push_back(in);
		}
		namePrint->setText(false, name);
		namePrint->setPosition(CONSOLE_WIDTH / 2 - namePrint->getDimension().x / 2, namePrint->getPosition().y);
		cursor->setPosition(namePrint->getPosition().x + namePrint->getDimension().x, namePrint->getPosition().y);

		if (valid)
			namePrint->setForegroundColor(FG_LIGHTGRAY);
		else
		{
			namePrint->setForegroundColor(FG_LIGHTRED);
		}
	}
}

void NameChoice::end(float delta)
{
	if (tween->isFinished())
	{
		welcome->setPaused(false);
		if (welcome->isFinished() && timer.getTime() > 4)
		{
			Character::player->setName(name);
			manager->setGameStart(true);
			manager->swap(new Chapter1(manager));
		}
	}
}