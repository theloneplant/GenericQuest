#ifndef PAUSE_MENU
#define PAUSE_MENU

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class Menu;

class PauseMenu : public Branch
{
    public:
		PauseMenu(BranchManager* bm);
		~PauseMenu();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Tween* tween;
		Menu* menu;
		Frame* frame;

		PauseMenu(const PauseMenu&);
		PauseMenu& operator=(const PauseMenu&);
};
#endif