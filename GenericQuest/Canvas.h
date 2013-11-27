#ifndef CANVAS
#define CANVAS

class Frame;
class Symbol;

class Canvas
{
	public:
		Canvas();
		void overwrite(Frame* frame);
		void overwrite(Frame* frame, float xPos, float yPos);
		void draw(HANDLE screen);
		void clear();

	private:
		Frame * canvas;
		Frame * prev;
};
#endif