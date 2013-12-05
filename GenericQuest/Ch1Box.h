#ifndef CH1_BOX
#define CH1_BOX

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class Ch1Box : public Branch
{
    public:
		Ch1Box(BranchManager* bm);
		~Ch1Box();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Text *text;
		Menu *menu;
		Animation *glitch;
		bool waiting;

		Ch1Box(const Ch1Box&);
		Ch1Box& operator=(const Ch1Box&);
};
#endif