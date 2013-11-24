#ifndef CANVAS
#define CANVAS

class Frame;
class Symbol;

class Canvas
{
	public:
		Canvas();
		void overwrite(Frame* frame);
		void overwrite(Frame* frame, int xPos, int yPos);
		void draw(HANDLE screen);
		void clear();

	private:
		Frame * canvas;
		Frame * prev;
};
#endif