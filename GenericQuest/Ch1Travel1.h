#ifndef CH1_TRAVEL1
#define CH1_TRAVEL1

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class Ch1Travel1 : public Branch
{
    public:
		Ch1Travel1(BranchManager* bm);
		~Ch1Travel1();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Text *text;
		Menu *menu;

		Ch1Travel1(const Ch1Travel1&);
		Ch1Travel1& operator=(const Ch1Travel1&);
};
#endif