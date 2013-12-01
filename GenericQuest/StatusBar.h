#ifndef STATUS_BAR
#define STATUS_BAR

#include "Color.h"

class Symbol;
class Frame;

class StatusBar : public Actor
{
	public:
		StatusBar(unsigned int newWidth, Color fg, Color fill, Color empt, float x, float y);
		~StatusBar();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void calculateBar(string text, int myValue, int maxValue);

	private:
		Frame* bar;
		Color textColor, filled, empty;
		unsigned int width;
};

#endif