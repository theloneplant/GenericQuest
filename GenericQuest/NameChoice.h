#ifndef NAME_CHOICE
#define NAME_CHOICE

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class NameChoice : public Branch
{
    public:
		NameChoice(BranchManager* bm, Role role);
		~NameChoice();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);
		void updateColors();

	private:
		Tween *tween;
		Frame *title;
		Text *namePrint, *error, *welcome;
		Animation *cursor;
		string name;
		bool valid;

		NameChoice(const NameChoice&);
		NameChoice& operator=(const NameChoice&);
};
#endif