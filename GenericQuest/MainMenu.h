#ifndef MAIN_MENU
#define MAIN_MENU

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class Menu;

class MainMenu : public Branch
{
    public:
		MainMenu(BranchManager* bm);
		~MainMenu();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Timer timer;
		Menu* menu;
		Frame* title;
		Animation* sword;

		MainMenu(const MainMenu&);
		MainMenu& operator=(const MainMenu&);
};
#endif