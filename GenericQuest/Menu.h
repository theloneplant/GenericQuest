#ifndef MENU
#define MENU

#include "Actor.h"
#include "Frame.h"

class Menu : public Actor
{
	public:
		Menu(Frame* newMessage, Frame* newCursor, float x, float y, char newUp, char newDown);
		~Menu();
		void update(float delta);
		int input();
		void draw(Canvas* canvas);
		void addMember(Frame* newFrame);
		void clear();
		void setFocusedIndex(int index);
		void setForegroundColor(int color);
		void setBackgroundColor(int color);
		void setDimension(int x, int y);
		void setPosition(float x, float y);
		void setVelocity(float x, float y);
		void setAcceleration(float x, float y);
		Frame* getMember(int i);
		Frame* getFocused();
		int getFocusedIndex();
		int getSize();
		Dimension getDimension();
		Vector getPosition();
		Vector getVelocity();
		Vector getAcceleration();

	private:
		vector<Frame*> members;
		Frame* message;
		Frame* cursor;
		int focusedMember;
		char up, down;
};

#endif