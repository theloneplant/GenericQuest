#include "stdafx.h"
#include "FileIO.h"
#include "Symbol.h"
#include "Color.h"
#include "Input.h"
#include "Canvas.h"
#include "Frame.h"
#include "Text.h"

Text::Text(bool useFile, string file, bool type, int newSpeed, int newPause, float x, float y)
{
	FileIO::buildText(useFile, file, text, dimension);
	frame.resize(text.size());
	for (unsigned int i = 0; i < text.size(); i++)
	{
		frame.at(i).resize(text.at(0).size());
	}

	setPosition(x, y);
	typewriter = type;
	paused = false; //Doesnt start out pausing for punctuation
	finished = false;
	cursorX = 0;
	cursorY = 0;
	typeSpeed = newSpeed; //Used for slowly typing out characters
	pause = newPause; //Used for pausing at punctuation and new lines

	if (!type)
	{
		frame = text;
		finished = true;
	}
}

Text::~Text()
{
}

void Text::update(float delta)
{
	Actor::update(delta);

	if (Input::keyHit())
	{
		if (Input::get() != 27) // Ignore Esc
		{
			typewriter = false;
		}
	}

	if (typewriter && !paused) //If it's animated
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
						//if (timer.getTime() >= pause / 1000.0)
						{
							cursorX = 0;
							cursorY++;
							timer.reset();
						}
					}
				}
				else //CursorX is out of bounds, wrap around
				{
					//if (timer.getTime() >= pause / 1000.0)
					{
						cursorX = 0;
						cursorY++;
						timer.reset();
					}
				}
			}
			else
			{
				if (!finished)
					finished = true;
			}
		}
	}
	else if (!typewriter)
	{
		frame = text;
		if (!finished)
			finished = true;
	}
}

void Text::draw(Canvas* canvas)
{
	if (!hidden)
		Frame::draw(canvas);
}

void Text::reset()
{
	Symbol replace;
	replace.setChar(' ');
	replace.setBackgroundColor(Color::BG_BLACK);
	replace.setForegroundColor(Color::FG_LIGHTGRAY);
	cursorX = cursorY = 0;
	for (int y = 0; y < text.size(); y++)
	{
		for (int x = 0; x < text.at(y).size(); x++)
		{
			// Reset all symbols
			setSymbol(replace, x, y);
		}
	}
	finished = false;
}

void Text::setText(bool useFile, string file)
{
	FileIO::buildText(useFile, file, text, dimension);
	cursorX = 0;
	cursorY = 0;
	if (typewriter)
		frame.resize(0);
	frame.resize(text.size());
	for (unsigned int i = 0; i < text.size(); i++)
	{
		frame.at(i).resize(text.at(0).size());
	}
	finished = false;
}

void Text::setPaused( bool newPaused)
{
	paused = newPaused;
}

void Text::setTypewriter(bool type)
{
	typewriter = type;
}

void Text::setFinished(bool newFinished)
{
	finished = newFinished;
}

void Text::setForegroundColor(int color)
{
	Frame::setForegroundColor(color);
	for (unsigned int y = 0; y < text.size(); y++)
	{
		for (unsigned int x = 0; x < text.at(y).size(); x++)
		{
			text.at(y).at(x).setForegroundColor(color);
		}
	}
}

void Text::setBackgroundColor(int color)
{
	Frame::setBackgroundColor(color);
	for (unsigned int y = 0; y < text.size(); y++)
	{
		for (unsigned int x = 0; x < text.at(y).size(); x++)
		{
			text.at(y).at(x).setBackgroundColor(color);
		}
	}
}

void Text::setSymbol(Symbol symbol, int x, int y)
{
	Frame::setSymbol(symbol, x, y);
}

void Text::setDimension(int x, int y)
{
	Frame::setDimension(x, y);
}

void Text::setPosition(float x, float y)
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

bool Text::isFinished()
{
	return finished;
}