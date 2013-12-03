#ifndef CLASS_CHOICE
#define CLASS_CHOICE

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class Menu;

class ClassChoice : public Branch
{
    public:
		ClassChoice(BranchManager* bm);
		~ClassChoice();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Menu* menu;
		Frame* title, *knight, *ranger, *wizard;
		Animation *kAnim, *rAnim, *wAnim;

		ClassChoice(const ClassChoice&);
		ClassChoice& operator=(const ClassChoice&);
};
#endif