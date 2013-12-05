#ifndef NO_ADVENTURE
#define NO_ADVENTURE

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class NoAdventure : public Branch
{
    public:
		NoAdventure(BranchManager* bm);
		~NoAdventure();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Text *text;
		Menu *menu;

		NoAdventure(const NoAdventure&);
		NoAdventure& operator=(const NoAdventure&);
};
#endif