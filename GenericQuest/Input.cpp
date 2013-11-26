#include "stdafx.h"
#include "Input.h"

//These variables can only be seen inside of Input, 
//and should never be modified outside of it.
static char recentInput = ' ';
static bool keyPressed = false;

void Input::refresh()
{
	keyPressed = false;

	while (_kbhit())
	{
		recentInput = _getch();
		keyPressed = true;
	}
}

void Input::clear()
{
	keyPressed = false;
}

char Input::get()
{
	return recentInput;
}

bool Input::keyHit()
{
	return keyPressed;
}