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
#include "NameChoice.h"
#include "ClassChoice.h"

ClassChoice::ClassChoice(BranchManager* bm) : Branch(bm)
{
	timer.reset();

	title = new Frame("classchoose.fram", 1, 1);
	title->setForegroundColor(FG_YELLOW);
	title->setHidden(true);

	Text* message = new Text(false, "", true, 15, 500, 0, 0);
	Animation* cursor = new Animation("cursor.anim", 15, 10, true, false, 3);
	cursor->setForegroundColor(FG_BLACK);
	cursor->play();
	knight = new Text(true, "knight.fram", false, 0, 0, 12, -4);
	ranger = new Text(true, "ranger.fram", false, 0, 0, 32, -5);
	wizard = new Text(true, "wizard.fram", false, 0, 0, 54, -4);
	knight->setForegroundColor(FG_BLACK);
	ranger->setForegroundColor(FG_BLACK);
	wizard->setForegroundColor(FG_BLACK);

	menu = new Menu(message, cursor, 0, 0, 75, 77);
	menu->addMember(knight);
	menu->addMember(ranger);
	menu->addMember(wizard);

	kAnim = new Animation("knight.anim", 11, -16, true, false, 5);
	rAnim = new Animation("ranger.anim", 32, -15, true, false, 5);
	wAnim = new Animation("wizard.anim", 51, -18, true, false, 6);

	knight->setHidden(true);
	ranger->setHidden(true);
	wizard->setHidden(true);
	kAnim->setHidden(true);
	rAnim->setHidden(true);
	wAnim->setHidden(true);

	kTween = new Tween(SinOut, kAnim, 11, 6, .5);
	kTween->add(knight);
	rTween = new Tween(SinOut, rAnim, 32, 7, .5);
	rTween->add(ranger);
	wTween = new Tween(SinOut, wAnim, 51, 4, .5);
	wTween->add(wizard);
	kPlayed = rPlayed = wPlayed = false;

	myFrames.push_back(menu);
	myFrames.push_back(kAnim);
	myFrames.push_back(rAnim);
	myFrames.push_back(wAnim);
	myFrames.push_back(title);

	myTweens.push_back(kTween);
	myTweens.push_back(rTween);
	myTweens.push_back(wTween);
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

	updateColors();

	if (timer.getTime() > 1.5f)
	{
		state = Input;
	}
	else if (timer.getTime() > 0.5f && !wPlayed)
	{
		wizard->setHidden(false);
		wAnim->setHidden(false);
		wTween->play();
		wPlayed = true;
	}
	else if (timer.getTime() > 0.25f && !rPlayed)
	{
		ranger->setHidden(false);
		rAnim->setHidden(false);
		rTween->play();
		rPlayed = true;
	}
	else if (timer.getTime() > 0 && !kPlayed)
	{
		knight->setHidden(false);
		kAnim->setHidden(false);
		kTween->play();
		kPlayed = true;
	}
}

void ClassChoice::input(float delta)
{
	updateColors();

	if (wTween->isFinished())
		title->setHidden(false);
	
	int input = menu->input();
	if (input != -1)
	{
		if (input == 0 || input == 1 || input == 2)
		{
			selected = input;
			state = End;
			kPlayed = rPlayed = wPlayed = false;
		}
	}
}

void ClassChoice::end(float delta)
{
	if (selected == 0 && !kPlayed)
	{
		timer.reset();
		kPlayed = true;
		rAnim->setHidden(true);
		ranger->setHidden(true); //This was bugged for some reason
		ranger->setPosition(ranger->getPosition().x, -20); //Avoids the bug i didnt figure out
		wAnim->setHidden(true);
		wizard->setHidden(true);
		wizard->setPosition(wizard->getPosition().x, -20);
		kTween->restart(CONSOLE_WIDTH / 2 - kAnim->getDimension().x / 2, kAnim->getPosition().y);
	}
	else if (selected == 1 && !rPlayed)
	{
		timer.reset();
		rPlayed = true;
		kAnim->setHidden(true);
		knight->setHidden(true);
		knight->setPosition(knight->getPosition().x, -20);
		wAnim->setHidden(true);
		wizard->setHidden(true);
		wizard->setPosition(wizard->getPosition().x, -20);
		rTween->restart(CONSOLE_WIDTH / 2 - rAnim->getDimension().x / 2, rAnim->getPosition().y);
	}
	else if (selected == 2 && !wPlayed)
	{
		timer.reset();
		wPlayed = true;
		kAnim->setHidden(true);
		knight->setHidden(true);
		knight->setPosition(knight->getPosition().x, -20);
		rAnim->setHidden(true);
		ranger->setHidden(true);
		ranger->setPosition(ranger->getPosition().x, -20);
		wTween->restart(CONSOLE_WIDTH / 2 - wAnim->getDimension().x / 2, wAnim->getPosition().y);
	}
	if (kPlayed && kTween->isFinished() && timer.getTime() > 1)
	{
		manager->swap(new NameChoice(manager, Knight));
	}
	else if (rPlayed && rTween->isFinished() && timer.getTime() > 1)
	{
		manager->swap(new NameChoice(manager, Ranger));
	}
	else if (wPlayed && wTween->isFinished() && timer.getTime() > 1)
	{
		manager->swap(new NameChoice(manager, Wizard));
	}
}

void ClassChoice::updateColors()
{
	if (menu->getFocusedIndex() == 0)
	{
		knight->setForegroundColor(FG_LIGHTRED);
		kAnim->setForegroundColor(FG_LIGHTRED);
		kAnim->play();
		ranger->setForegroundColor(FG_GREEN);
		rAnim->setForegroundColor(FG_GREEN);
		rAnim->restart();
		rAnim->pause();
		wizard->setForegroundColor(FG_BLUE);
		wAnim->setForegroundColor(FG_BLUE);
		wAnim->restart();
		wAnim->pause();
	}
	else if (menu->getFocusedIndex() == 1)
	{
		knight->setForegroundColor(FG_RED);
		kAnim->setForegroundColor(FG_RED);
		kAnim->restart();
		kAnim->pause();
		ranger->setForegroundColor(FG_LIGHTGREEN);
		rAnim->setForegroundColor(FG_LIGHTGREEN);
		rAnim->play();
		wizard->setForegroundColor(FG_BLUE);
		wAnim->setForegroundColor(FG_BLUE);
		wAnim->restart();
		wAnim->pause();
	}
	else if (menu->getFocusedIndex() == 2)
	{
		knight->setForegroundColor(FG_RED);
		kAnim->setForegroundColor(FG_RED);
		kAnim->restart();
		kAnim->pause();
		ranger->setForegroundColor(FG_GREEN);
		rAnim->setForegroundColor(FG_GREEN);
		rAnim->restart();
		rAnim->pause();
		wizard->setForegroundColor(FG_LIGHTBLUE);
		wAnim->setForegroundColor(FG_LIGHTBLUE);
		wAnim->play();
	}
}