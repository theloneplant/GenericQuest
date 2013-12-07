#include "stdafx.h"
#include "Canvas.h"
#include "Branch.h"
#include "Frame.h"
#include "Text.h"
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
	MainMenu *blah = new MainMenu(&bm);
	Text * fps = new Text(false, "yo", false, 0, 0, 0, 23);
	bm.push(blah);
	Canvas canvas;
	Timer timer;
	srand(time(0));
	float delta = 0;

	while(true)
	{
		delta += timer.getDelta();
		float frameRate = 1 / delta;
		fps->setText(false, "FPS: " + to_string(static_cast<long double>(frameRate)));
		fps->update(delta);

		if (frameRate <= 30)
		{
			Input::refresh();
			bm.update(delta);
			bm.draw(&canvas);
			canvas.draw(screen);
			fps->draw(&canvas);
			delta = 0;
		}
	}

	return 0;
}