#include "stdafx.h"
#include "Color.h"
#include "Symbol.h"

Symbol::Symbol()
{
	symbol = '`';
	color = 0x07;
}

Symbol::Symbol(char newSymbol, int newColor)
{
	symbol = newSymbol;
	color = newColor;
}

bool Symbol::operator==(const Symbol & other)
{
	return (symbol == other.symbol) && (color == other.color);
}

bool Symbol::operator!=(const Symbol & other)
{
	return ! (*this == other);
}

void Symbol::setChar(char newSymbol)
{
	symbol = newSymbol;
}

void Symbol::setForegroundColor(int newColor)
{
	color = (color & 0xF0) | (newColor & 0x0F);
}

void Symbol::setBackgroundColor(int newColor)
{
	color = (color & 0x0F) | (newColor & 0xF0);
}

char Symbol::getChar()
{
	return symbol;
}

int  Symbol::getColor()
{
	return color;
}