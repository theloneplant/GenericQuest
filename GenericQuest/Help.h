#ifndef HELP
#define HELP

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class Menu;

class Help : public Branch
{
    public:
		Help(BranchManager* bm);
		~Help();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Timer timer;
		Menu* menu;
		Frame* frame;

		Help(const Help&);
		Help& operator=(const Help&);
};
#endif