#ifndef GAME_OVER
#define GAME_OVER

#include "Timer.h"
#include "Character.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class StatusBar;
class Menu;

class GameOver : public Branch
{
    public:
		GameOver(BranchManager* bm, Branch* newLink,  int cr);
		~GameOver();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Frame *frame;
		Tween *tween;
		Menu *menu;

		GameOver(const GameOver&);
		GameOver& operator=(const GameOver&);
};
#endif