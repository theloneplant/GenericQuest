#ifndef FRAME
#define FRAME

#include "Symbol.h"
#include "Actor.h"

class Frame : public Actor
{
    public:
		Frame();
		Frame(int width, int height);
		Frame(string file, float x, float y);
		Frame(vector<vector<Symbol>> newFrame, float x, float y);
		~Frame();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void setFrame(vector<vector<Symbol>> newFrame);
		virtual void setForegroundColor(int color);
		virtual void setBackgroundColor(int color);
		virtual void setSymbol(Symbol symbol, int x, int y);
		virtual void setDimension(int x, int y);
		virtual void setPosition(float x, float y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual Symbol getSymbol(int x, int y);
		virtual vector<vector<Symbol>> getFrame();
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();

	protected:
		vector<vector<Symbol>> frame;

	private:
		Frame(const Frame&);
		Frame& operator=(const Frame&);
};
#endif