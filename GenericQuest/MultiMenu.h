#ifndef MULTI_MENU
#define MULTI_MENU

#include "Actor.h"
#include "Frame.h"
#include "Menu.h"

class MultiMenu : public Actor
{
	public:
		MultiMenu(Frame* newMessage, Frame* newCursor, Menu* menu, float x, float y, char newUp, char newDown);
		~MultiMenu();
		void update(float delta);
		int input();
		void draw(Canvas* canvas);
		void addMenu(Menu* newMenu);
		void setForegroundColor(int color);
		void setBackgroundColor(int color);

	private:
		vector<Menu*> menus;
		Frame* message;
		Frame* cursor;
		int focusedMember;
		char up, down;
};
#endif