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

	int targetFPS = 60;
	float delta = 0;
	float frameTime = 1.0 / targetFPS;
	Timer timer;
	srand(time(0));

	// Wait 0.1 second before starting
	while (timer.getTime() < 0.1);
	timer.reset();

	BranchManager bm;
	MainMenu *blah = new MainMenu(&bm);
	Text * fps = new Text(false, "DEFAULT", false, 0, 0, 0, 23);
	bm.push(blah);
	Canvas canvas;

	while(true)
	{
		delta += timer.getDelta();
		float frameRate = 1 / delta;
		fps->setText(false, "FPS: " + to_string(static_cast<long double>(frameRate)));
		fps->update(delta);

		if (delta >= frameTime)
		{
			Input::refresh();
			bm.update(delta);
			bm.draw(&canvas);
			canvas.draw(screen);
			// fps->draw(&canvas);
			delta = 0;
		}
	}

	return 0;
}