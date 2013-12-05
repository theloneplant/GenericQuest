#ifndef CH1_COMBAT1
#define CH1_COMBAT1

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class Ch1Combat1 : public Branch
{
    public:
		Ch1Combat1(BranchManager* bm, int input);
		~Ch1Combat1();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Text *text;
		Menu *menu;

		Ch1Combat1(const Ch1Combat1&);
		Ch1Combat1& operator=(const Ch1Combat1&);
};
#endif