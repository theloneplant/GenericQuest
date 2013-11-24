#include "stdafx.h"
#include "Color.h"

int getColor(string c)
{
	string color = c;
	if (color == "BLACK")
	{
		return 0x00;
	}
	else if (color == "BLUE")
	{
		return 0x01;
	}
	else if (color == "GREEN")
	{
		return 0x02;
	}
	else if (color == "CYAN")
	{
		return 0x03;
	}
	else if (color == "RED")
	{
		return 0x04;
	}
	else if (color == "MAGENTA")
	{
		return 0x05;
	}
	else if (color == "BROWN")
	{
		return 0x06;
	}
	else if (color == "LIGHTGRAY" || color == "LIGHTGREY")
	{
		return 0x07;
	}
	else if (color == "DARKGRAY" || color == "DARKGREY")
	{
		return 0x08;
	}
	else if (color == "LIGHTBLUE")
	{
		return 0x09;
	}
	else if (color == "LIGHTGREEN")
	{
		return 0x0A;
	}
	else if (color == "LIGHTCYAN")
	{
		return 0x0B;
	}
	else if (color == "LIGHTRED")
	{
		return 0x0C;
	}
	else if (color == "LIGHTMAGENTA")
	{
		return 0x0D;
	}
	else if (color == "YELLOW")
	{
		return 0x0E;
	}
	else
	{
		return 0x0F;
	}
	return 0;
}