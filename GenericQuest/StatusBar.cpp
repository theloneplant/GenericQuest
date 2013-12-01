#include "stdafx.h"
#include "Frame.h"
#include "StatusBar.h"

StatusBar::StatusBar(unsigned int newWidth, Color fg, Color fill, Color empt, float x, float y)
{
	Actor::setPosition(x, y);
	Actor::setDimension(newWidth, 1);
	bar = new Frame(newWidth, 1);
	width = newWidth;
	textColor = fg;
	filled = fill;
	empty = empt;
}

StatusBar::~StatusBar()
{
	delete bar;
}

void StatusBar::update(float delta)
{
	Actor::update(delta);
	bar->setPosition(getPosition().x, getPosition().y);
}

void StatusBar::draw(Canvas* canvas)
{
	bar->draw(canvas);
}

void StatusBar::calculateBar(string text, int value, int max)
{
	Symbol symbol;
	if (value < 0)
		value = 0;
	unsigned int valueWidth = static_cast<int>(width * value / (max + 0.0f));
	unsigned int textPos = (width - text.length()) / 2;
	unsigned int count = 0;

	symbol.setForegroundColor(textColor);
	symbol.setBackgroundColor(filled);
	for (count; count < valueWidth; count++)
	{
		if (count < text.length() + textPos && count >= textPos)
			symbol.setChar(text.at(count - textPos));
		else
			symbol.setChar(' ');

		bar->setSymbol(symbol, count, 0);
	}
	symbol.setBackgroundColor(empty);
	for (count; count < width; count++)
	{
		if (count < text.length() + textPos && count >= textPos)
			symbol.setChar(text.at(count - textPos));
		else
			symbol.setChar(' ');

		bar->setSymbol(symbol, count, 0);
	}
}