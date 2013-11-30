#include "stdafx.h"
#include "Canvas.h"
#include "Branch.h"
#include "MainMenu.h"
#include "BranchManager.h"
#include "Timer.h"
#include "Input.h"

using namespace std;

int main()
{
	HANDLE screen = GetStdHandle( STD_OUTPUT_HANDLE );
	
	SetConsoleTitle("Generic Quest");

	//Make the cursor invisible
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(screen, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(screen, &cursorInfo);

	BranchManager bm;
	MainMenu blah(&bm);
	bm.push(&blah);
	Canvas canvas;
	Timer timer;
	srand(time(0));

	while(true)
	{
		Input::refresh();

		bm.update(timer.getDelta());
		bm.draw(&canvas);

		canvas.draw(screen);
	}

	return 0;
}