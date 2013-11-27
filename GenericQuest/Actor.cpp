#include "stdafx.h"
#include "Canvas.h"
#include "Actor.h"

Actor::Actor()
{
	setDimension(0, 0);
	setPosition(0, 0);
	setVelocity(0, 0);
	setAcceleration(0, 0);
}

Actor::~Actor()
{
	//Do nothing
}

void Actor::update(float delta)
{
	velocity.x += acceleration.x * delta;
	velocity.y += acceleration.y * delta * 2 / 3;
	position.x += velocity.x * delta;
	position.y += velocity.y * delta * 2 / 3;
}

void Actor::draw(Canvas* canvas)
{
	//Do nothing
}

void Actor::setDimension(int x, int y)
{
	dimension.x = x;
	dimension.y = y;
}

void Actor::setPosition(float x, float y)
{
	position.x = x;
	position.y = y;
}

void Actor::setVelocity(float x, float y)
{
	velocity.x = x;
	velocity.y = y;
}

void Actor::setAcceleration(float x, float y)
{
	acceleration.x = x;
	acceleration.y = y;
}

void Actor::setHidden(bool newHidden)
{
	hidden = newHidden;
}

Dimension Actor::getDimension()
{
	return dimension;
}

Vector Actor::getPosition()
{
	return position;
}

Vector Actor::getVelocity()
{
	return velocity;
}

Vector Actor::getAcceleration()
{
	return acceleration;
}

bool Actor::isHidden()
{
	return hidden;
}