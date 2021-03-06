#ifndef TEXT_
#define TEXT_

#include "Timer.h"

class Symbol;
class Frame;

class Text : public Frame
{
	public:
		Text(bool useFile, string file, bool type, int newSpeed, int newPause, float x, float y);
		~Text();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void reset();
		virtual void setText(bool useFile, string file);
		virtual void setTypewriter(bool type);
		virtual void setFinished(bool newFinished);
		virtual void setPaused(bool newPaused);
		virtual void setForegroundColor(int color);
		virtual void setBackgroundColor(int color);
		virtual void setSymbol(Symbol symbol, int x, int y);
		virtual void setDimension(int x, int y);
		virtual void setPosition(float x, float y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual Symbol getSymbol(int x, int y);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();
		virtual bool isFinished();

	private:
		vector<vector<Symbol>> text; //Holds the text
		Timer timer;
		unsigned int typeSpeed, pause, cursorX, cursorY;
		bool typewriter, paused, finished;
};

#endif