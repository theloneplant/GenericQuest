#ifndef COMBAT
#define COMBAT

#include "Timer.h"
#include "Item.h"

class BranchManager;
class Branch;
class Canvas;

class Enemy;
class Text;
class Frame;
class Animation;
class Menu;
class StatusBar;

class Combat : public Branch
{
    public:
		Combat(BranchManager* bm);
		Combat(BranchManager* bm, float x, float y);
		~Combat();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);
		void updateMenu();

	private:
		Timer timer;
		Enemy* enemy;
		Menu* choice;
		Text* text, *text1; //*dist,
			//*playerStatus, *enemyStatus;
		StatusBar *playerHP, *enemyHP;
		int distance;
		bool playerRooted, enemyRooted;
		bool playerStunned, enemyStunned;
		bool playerMiss, enemyMiss;
		Text *melee, *range, *magic,
			*bash, *charge,
			*stun,
			*freeze, *shock,
			*backUp, *moveIn, *potions;
		int meleeChoice, rangeChoice, magicChoice,
			knightBash, knightCharge,
			rangerStun,
			wizardFreeze, wizardShock,
			backUpChoice, moveInChoice, potionsChoice;
		
		Combat(const Combat&);
		Combat& operator=(const Combat&);
};
#endif