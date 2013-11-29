#include "stdafx.h"
#include "Canvas.h"
#include "Actor.h"
#include "Input.h"
#include "Menu.h"
#include "MultiMenu.h"

MultiMenu::MultiMenu(Frame* newMessage, Frame* newCursor, Menu* menu, float x, float y, char newUp, char newDown)
{
	Actor::Actor();
	setPosition(x, y);

	message = newMessage;
	cursor = newCursor;
	menus.push_back(menu);
	focusedMember = 0;
	up = newUp;
	down = newDown;
	hidden = false;
}

MultiMenu::~MultiMenu()
{
}

void MultiMenu::update(float delta)
{
	Actor::update(delta);

	message->update(delta);
	cursor->update(delta);
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		menus.at(i)->update(delta);
	}

	//Update cursor position
	cursor->setPosition(menus.at(focusedMember)->getFocused()->getPosition().x - cursor->getDimension().x, 
		menus.at(focusedMember)->getFocused()->getPosition().y 
		+ menus.at(focusedMember)->getFocused()->getDimension().y / 2 - cursor->getDimension().y / 2);
}

int MultiMenu::input()
{
	if (Input::keyHit())
	{
		char input = Input::get();

		if (input == up)
		{
			focusedMember--;
			if (focusedMember < 0)
				focusedMember = menus.size() - 1;
		}
		else if (input == down)
		{
			focusedMember++;
			if (focusedMember > menus.size() - 1)
				focusedMember = 0;
		}
		else if (input == 13)
			return focusedMember;
	}

	return menus.at(focusedMember)->input();
}

void MultiMenu::draw(Canvas* canvas)
{
	if (!hidden)
	{
		for (unsigned int i = 0; i < menus.size(); i++)
		{
			for (unsigned int j = 0; j < menus.at(i)->getSize(); j++)
				canvas->overwrite(menus.at(i)->getMember(j), position.x, position.y);
		}
		canvas->overwrite(message, position.x, position.y);
		canvas->overwrite(cursor, position.x, position.y);
	}
}

void MultiMenu::addMenu(Menu* newMenu)
{
	menus.push_back(newMenu);
}

void MultiMenu::setForegroundColor(int color)
{
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		menus.at(i)->setForegroundColor(color);
	}
}

void MultiMenu::setBackgroundColor(int color)
{
	for (unsigned int i = 0; i < menus.size(); i++)
	{
		menus.at(i)->setBackgroundColor(color);
	}
}