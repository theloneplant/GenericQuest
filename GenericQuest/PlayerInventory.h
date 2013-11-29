#ifndef PLAYER_INVENTORY
#define PLAYER_INVENTORY

#include "Timer.h"
#include "Item.h"

class BranchManager;
class Branch;
class Canvas;

class Text;
class Frame;
class Animation;
class MultiMenu;
class StatusBar;

class PlayerInventory : public Branch
{
    public:
		PlayerInventory(BranchManager* bm);
		PlayerInventory(BranchManager* bm, float x, float y);
		~PlayerInventory();
		void init(bool animate);
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Timer timer;
		Menu* items;
		Frame* frame;
		Item selected;
		Text* currentName, *currentStr, *currentDex, *currentInt;
		Text* selectedName, *selectedStr, *selectedDex, *selectedInt;

		PlayerInventory(const PlayerInventory&);
		PlayerInventory& operator=(const PlayerInventory&);
};
#endif