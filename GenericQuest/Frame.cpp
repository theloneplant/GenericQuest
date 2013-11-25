#include "stdafx.h"
#include "FileIO.h"
#include "Canvas.h"
#include "Frame.h"

Frame::Frame()
{
	Actor::Actor();

	setDimension(0, 0);
	frame.resize(0);
	hidden = false;
}

Frame::Frame(int width, int height)
{
	Actor::Actor();
	setDimension(width, height);

	frame.resize(height);
	for (int i = 0; i < height; i++)
	{
		frame.at(i).resize(width);
	}
	hidden = false;
}

Frame::Frame(string file, int x, int y)
{
	Actor::Actor();
	setPosition(x, y);
	FileIO::buildFrame(file, frame, dimension);
	hidden = false;
}

Frame::Frame(vector<vector<Symbol>> newFrame, int x, int y)
{
	Actor::Actor();
	setPosition(x, y);
	frame = newFrame;
	hidden = false;
}

Frame::~Frame()
{
}

void Frame::update(float delta)
{
	Actor::update(delta);
}

void Frame::draw(Canvas* canvas)
{
	if (!hidden)
		canvas->overwrite(this);
}

void Frame::setFrame(vector<vector<Symbol>> newFrame)
{
	frame = newFrame;
}

void Frame::setSymbol(Symbol symbol, int x, int y)
{
	frame.at(y).at(x) = symbol;
}

void Frame::setDimension(int x, int y)
{
	Actor::setDimension(x, y);
	frame.resize(y);
	for (int i = 0; i < frame.size(); i++)
	{
		frame.at(i).resize(x);
	}
}

void Frame::setPosition(int x, int y)
{
	Actor::setPosition(x, y);
}

void Frame::setVelocity(float x, float y)
{
	Actor::setVelocity(x, y);
}

void Frame::setAcceleration(float x, float y)
{
	Actor::setAcceleration(x, y);
}

void Frame::setHidden(bool newHidden)
{
	hidden = newHidden;
}

vector<vector<Symbol>> Frame::getFrame()
{
	return frame;
}

Symbol Frame::getSymbol(int x, int y)
{
	return frame.at(y).at(x);
}

Dimension Frame::getDimension()
{
	return dimension;
}

Vector Frame::getPosition()
{
	return position;
}

Vector Frame::getVelocity()
{
	return velocity;
}

Vector Frame::getAcceleration()
{
	return acceleration;
}

bool Frame::isHidden()
{
	return hidden;
}