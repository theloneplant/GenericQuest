#ifndef ADVENTURE_START
#define ADVENTURE_START

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class AdventureStart : public Branch
{
    public:
		AdventureStart(BranchManager* bm);
		~AdventureStart();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Menu *menu;
		Text *text;

		AdventureStart(const AdventureStart&);
		AdventureStart& operator=(const AdventureStart&);
};
#endif