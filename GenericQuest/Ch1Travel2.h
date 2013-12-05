#ifndef CH1_TRAVEL2
#define CH1_TRAVEL2

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class Ch1Travel2 : public Branch
{
    public:
		Ch1Travel2(BranchManager* bm);
		~Ch1Travel2();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Text *text;
		Menu *menu;

		Ch1Travel2(const Ch1Travel2&);
		Ch1Travel2& operator=(const Ch1Travel2&);
};
#endif