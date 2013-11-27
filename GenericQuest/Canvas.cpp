#include "stdafx.h"
#include "Frame.h"
#include "Symbol.h"
#include "Canvas.h"

Canvas::Canvas()
{
	canvas = new Frame(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	prev = new Frame(CONSOLE_WIDTH, CONSOLE_HEIGHT);
	Symbol temp;
	for (int y = 0; y < canvas->getDimension().y; y++)
	{
		for (int x = 0; x < canvas->getDimension().x; x++)
		{
			canvas->setSymbol(temp, x, y);
		}
	}
}

void Canvas::overwrite(Frame* frame)
{
	overwrite(frame, 0, 0);
}

void Canvas::overwrite(Frame* frame, float xPos, float yPos)
{
	for (int y = 0; y < frame->getDimension().y; y++)
	{
		for (int x = 0; x < frame->getDimension().x; x++)
		{
			int xFinal = static_cast<int>(frame->getPosition().x + xPos + x);
			int yFinal = static_cast<int>(frame->getPosition().y + yPos + y);

			//If in the screen, draw the frame over what's already there
			if (frame->getSymbol(x, y).getChar() != '`' && xFinal >= 0 && yFinal >= 0 && xFinal < canvas->getDimension().x && yFinal < canvas->getDimension().y)
				canvas->setSymbol(frame->getSymbol(x, y), xFinal, yFinal);
		}
	}
}

void Canvas::draw(HANDLE screen)
{
	COORD position;
	//For each character to display
	for (int y = 0; y < canvas->getDimension().y; y++)
	{
		for (int x = 0; x < canvas->getDimension().x; x++)
		{
			//Draw everything
			position.X = x;
			position.Y = y;

			//if (prev->getSymbol(i, j).getChar() != canvas->getSymbol(i, j).getChar() || prev->getSymbol(i, j).getColor() != canvas->getSymbol(i, j).getColor())
			if (prev->getSymbol(x, y) != canvas->getSymbol(x, y))
			{
				SetConsoleCursorPosition(screen, position);
				SetConsoleTextAttribute(screen, canvas->getSymbol(x, y).getColor());
				cout << canvas->getSymbol(x, y).getChar();
			}
		}
	}

	//Copy the canvas to the previous frame
	for(int y = 0; y < prev->getDimension().y; y++)
	{
		for(int x = 0; x < prev->getDimension().x; x++)
		{
			prev->setSymbol(canvas->getSymbol(x, y), x, y);
		}
	}

	//Clear the screen
	clear();
}

void Canvas::clear()
{
	Symbol sym(' ', 0x07);

	for (int y = 0; y < canvas->getDimension().y; y++)
	{
		for (int x = 0; x < canvas->getDimension().x; x++)
		{
			canvas->setSymbol(sym, x, y);
		}
	}
}