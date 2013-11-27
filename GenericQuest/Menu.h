#ifndef MENU
#define MENU

#include "Actor.h"
#include "Frame.h"

class Menu : public Actor
{
	public:
		Menu(Frame* newMessage, Frame* newCursor, Frame* member, float x, float y, char newUp, char newDown);
		~Menu();
		virtual void update(float delta);
		virtual int input();
		virtual void draw(Canvas* canvas);
		virtual void addMember(Frame* newFrame);
		virtual void setForegroundColor(int color);
		virtual void setBackgroundColor(int color);
		virtual void setDimension(int x, int y);
		virtual void setPosition(float x, float y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();

	private:
		vector<Frame*> members;
		Frame* message;
		Frame* cursor;
		unsigned int focusedMember;
		char up, down;
};

#endif