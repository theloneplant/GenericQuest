#include "stdafx.h"
#include "FileIO.h"
#include "Symbol.h"
#include "Canvas.h"
#include "Frame.h"
#include "Text.h"

Text::Text(bool useFile, string file, bool type, int newSpeed, int newPause, int x, int y)
{
	Actor::Actor();
	FileIO::buildText(useFile, file, text, dimension);
	setDimension(text.at(0).size(), text.size());
	frame.resize(text.size());
	for (int i = 0; i < text.size(); i++)
	{
		frame.at(i).resize(text.at(0).size());
	}

	setPosition(x, y);
	typewriter = type;
	paused = false; //Doesnt start out pausing for punctuation
	cursorX = 0;
	cursorY = 0;
	typeSpeed = newSpeed; //Used for slowly typing out characters
	pause = newPause; //Used for pausing at punctuation and new lines
}

Text::~Text()
{
}

void Text::update(float delta)
{
	Actor::update(delta);

	if (typewriter) //If it's animated
	{
		if (timer.getTime() >= typeSpeed / 1000.0) //Check the delay
		{
			if (cursorY < text.size())
			{
				if (cursorX < text.at(cursorY).size()) //Bounds checking
				{
					char ch;
					if (cursorX > 0)
						ch = text.at(cursorY).at(cursorX - 1).getChar();
					else
						ch = text.at(cursorY).at(cursorX).getChar();

					if (ch != '`')
					{
						if (ch == '.' || ch == '!' || ch == '?')
						{
							if (timer.getTime() >= pause / 1000.0)
							{
								Frame::setSymbol(text.at(cursorY).at(cursorX), cursorX, cursorY);
								cursorX++;
								timer.reset();
							}
						}
						else if (ch == ',' || ch == ';' || ch == '\'' || ch == '\"')
						{
							if (timer.getTime() >= pause / 1000.0 / 6)
							{
								Frame::setSymbol(text.at(cursorY).at(cursorX), cursorX, cursorY);
								cursorX++;
								timer.reset();
							}
						}
						else
						{
							Frame::setSymbol(text.at(cursorY).at(cursorX), cursorX, cursorY);
							cursorX++;
							timer.reset();
						}
					}
					else //It's the end of the line
					{
						if (timer.getTime() >= pause / 1000.0)
						{
							cursorX = 0;
							cursorY++;
							timer.reset();
						}
					}
				}
				else //CursorX is out of bounds, wrap around
				{
					if (timer.getTime() >= pause / 1000.0)
					{
						cursorX = 0;
						cursorY++;
						timer.reset();
					}
				}
			}
		}
	}
}

void Text::draw(Canvas* canvas)
{
	Frame::draw(canvas);
}

void Text::setSymbol(Symbol symbol, int x, int y)
{
	Frame::setSymbol(symbol, x, y);
}

void Text::setDimension(int x, int y)
{
	Frame::setDimension(x, y);
}

void Text::setPosition(int x, int y)
{
	Actor::setPosition(x, y);
}

void Text::setVelocity(float x, float y)
{
	Actor::setVelocity(x, y);
}

void Text::setAcceleration(float x, float y)
{
	Actor::setAcceleration(x, y);
}

Symbol Text::getSymbol(int x, int y)
{
	return Frame::getSymbol(x, y);
}

Dimension Text::getDimension()
{
	return dimension;
}

Vector Text::getPosition()
{
	return position;
}

Vector Text::getVelocity()
{
	return velocity;
}

Vector Text::getAcceleration()
{
	return acceleration;
}