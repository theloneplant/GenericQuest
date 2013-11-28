#ifndef PLAYER_STATS
#define PLAYER_STATS

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class Menu;
class StatusBar;

class PlayerStats : public Branch
{
    public:
		PlayerStats(BranchManager* bm);
		~PlayerStats();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Timer timer;
		Menu* menu;
		Frame* frame;
		StatusBar* hpBar;
		StatusBar* xpBar;


		PlayerStats(const PlayerStats&);
		PlayerStats& operator=(const PlayerStats&);
};
#endif