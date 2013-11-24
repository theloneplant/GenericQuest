#ifndef TEXT_
#define TEXT_

#include "Timer.h"

class Symbol;
class Frame;

class Text : public Frame
{
	public:
		Text(bool useFile, string file, bool type, int newSpeed, int newPause, int x, int y);
		~Text();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void setSymbol(Symbol symbol, int x, int y);
		virtual void setDimension(int x, int y);
		virtual void setPosition(int x, int y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual Symbol getSymbol(int x, int y);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();

	private:
		vector<vector<Symbol>> text; //Holds the text
		Timer timer;
		int typeSpeed, pause, cursorX, cursorY;
		bool typewriter, paused;
};

#endif