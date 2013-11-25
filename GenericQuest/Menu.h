#ifndef MENU
#define MENU

#include "Actor.h"
#include "Frame.h"

class Menu : public Actor
{
	public:
		Menu(Frame* newMessage, Frame* newCursor, Frame* member, int x, int y, char newUp, char newDown);
		~Menu();
		virtual void update(float delta);
		virtual int input();
		virtual void draw(Canvas* canvas);
		virtual void addMember(Frame* newFrame);
		virtual void setDimension(int x, int y);
		virtual void setPosition(int x, int y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual void setHidden(bool newHidden);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();
		virtual bool isHidden();

	private:
		vector<Frame*> members;
		Frame* message;
		Frame* cursor;
		int focusedMember;
		char up, down;
		bool hidden;
};

#endif