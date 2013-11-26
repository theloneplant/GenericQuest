#include "stdafx.h"
#include "Input.h"
#include "Canvas.h"
#include "Actor.h"
#include "Menu.h"

Menu::Menu(Frame* newMessage, Frame* newCursor, Frame* member, int x, int y, char newUp, char newDown)
{
	Actor::Actor();
	setPosition(x, y);

	message = newMessage;
	cursor = newCursor;
	members.push_back(member);
	focusedMember = 0;
	up = newUp;
	down = newDown;
	hidden = false;
}

Menu::~Menu()
{
	delete message;
	delete cursor;
	for (int i = 0; i < members.size(); i++)
	{
		delete members.at(i);
	}
}

void Menu::update(float delta)
{
	Actor::update(delta);

	message->update(delta);
	cursor->update(delta);
	for (int i = 0; i < members.size(); i++)
	{
		members.at(i)->update(delta);
	}

	//Update cursor position
	cursor->setPosition(members.at(focusedMember)->getPosition().x - cursor->getDimension().x, 
		members.at(focusedMember)->getPosition().y + members.at(focusedMember)->getDimension().y / 2 - cursor->getDimension().y / 2);
}

int Menu::input()
{
	if (Input::keyHit())
	{
		char input = '`';
		input = Input::get();

		if (input == up && focusedMember >= 0)
		{
			focusedMember--;
			if (focusedMember < 0)
				focusedMember = members.size() - 1;
		}
		else if (input == down)
		{
			focusedMember++;
			if (focusedMember > members.size() - 1)
				focusedMember = 0;
		}
		else if (input == 13)
			return focusedMember;
	}

	return -1;
}

void Menu::draw(Canvas* canvas)
{
	if (!hidden)
	{
		for (int i = 0; i < members.size(); i++)
		{
			canvas->overwrite(members.at(i), position.x, position.y);
		}
		canvas->overwrite(message, position.x, position.y);
		canvas->overwrite(cursor, position.x, position.y);
	}
}

void Menu::addMember(Frame* newFrame)
{
	members.push_back(newFrame);
}

void Menu::setForegroundColor(int color)
{
	for (int i = 0; i < members.size(); i++)
	{
		members.at(i)->setForegroundColor(color);
	}
	message->setForegroundColor(color);
	cursor->setForegroundColor(color);
}
void Menu::setBackgroundColor(int color)
{
	for (int i = 0; i < members.size(); i++)
	{
		members.at(i)->setBackgroundColor(color);
	}
	message->setBackgroundColor(color);
	cursor->setBackgroundColor(color);
}

void Menu::setDimension(int x, int y)
{
	Actor::setDimension(x, y);
}

void Menu::setPosition(int x, int y)
{
	Actor::setPosition(x, y);
}

void Menu::setVelocity(float x, float y)
{
	Actor::setVelocity(x ,y);
}

void Menu::setAcceleration(float x, float y)
{
	Actor::setAcceleration(x, y);
}

Dimension Menu::getDimension()
{
	return dimension;
}

Vector Menu::getPosition()
{
	return position;
}

Vector Menu::getVelocity()
{
	return velocity;
}

Vector Menu::getAcceleration()
{
	return acceleration;
}