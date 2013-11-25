#ifndef FRAME
#define FRAME

#include "Symbol.h"
#include "Actor.h"

class Frame : public Actor
{
    public:
		Frame();
		Frame(int width, int height);
		Frame(string file, int x, int y);
		Frame(vector<vector<Symbol>> newFrame, int x, int y);
		~Frame();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void setFrame(vector<vector<Symbol>> newFrame);
		virtual void setSymbol(Symbol symbol, int x, int y);
		virtual void setDimension(int x, int y);
		virtual void setPosition(int x, int y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual void setHidden(bool newHidden);
		virtual Symbol getSymbol(int x, int y);
		virtual vector<vector<Symbol>> getFrame();
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();
		virtual bool isHidden();

	protected:
		vector<vector<Symbol>> frame;
		bool hidden;

	private:
		Frame(const Frame&);
		Frame& operator=(const Frame&);
};
#endif