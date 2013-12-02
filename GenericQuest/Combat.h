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
		void fadeOut();

	private:
		Timer timer;
		Enemy* enemy;
		Menu* choice;
		Text* enemyDesc, *playerDesc, *petDesc, //*dist,
			*playerName, *enemyName, *dist;
		Animation* playerStunFrame, *playerRootFrame,
			*enemyStunFrame, *enemyRootFrame, 
			*pHit;
		StatusBar *playerHP, *enemyHP;
		int distance;
		bool playerHit, petHit, enemyHit;
		bool playerRooted, enemyRooted;
		bool playerStunned, enemyStunned;
		int pStunCounter, eStunCounter,
			pRootCounter, eRootCounter;
		Text *melee, *range, *magic,
			*bash, *charge,
			*stun,
			*freeze, *shock,
			*backUp, *moveIn, *potions,
			*nothing;
		int meleeChoice, rangeChoice, magicChoice,
			knightBash, knightCharge,
			rangerStun,
			wizardFreeze, wizardShock,
			backUpChoice, moveInChoice, potionsChoice,
			nothingChoice;
		
		Combat(const Combat&);
		Combat& operator=(const Combat&);
};
#endif