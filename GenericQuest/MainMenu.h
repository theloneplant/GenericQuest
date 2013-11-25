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
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
        virtual void start(float delta);
		virtual void input(float delta);
		virtual void end(float delta);

	private:
		Timer timer;
		Menu* menu;
		Frame* title;
		Animation* sword;

		MainMenu(const MainMenu&);
		MainMenu& operator=(const MainMenu&);
};
#endif