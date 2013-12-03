#ifndef REWARD
#define REWARD

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

class Reward : public Branch
{
    public:
		Reward(BranchManager* bm, Branch* newLink,  int cr);
		~Reward();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Branch* link;
		Tween* tween;
		Menu* menu;
		Frame* victory;
		Text *gold, *level, *item, *loot;
		Animation* flash, *levelUp;
		StatusBar* xpBar;
		Gold cash;
		int xp, xpCount;
		float duration;
		Item* randomItem;
		bool giveItem, goldFinish, xpFinish, lootFinish;

		Reward(const Reward&);
		Reward& operator=(const Reward&);
};
#endif