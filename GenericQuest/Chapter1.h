#ifndef CHAPTER1
#define CHAPTER1

#include "Timer.h"

class BranchManager;
class Branch;
class Canvas;

class Character;
class Text;
class Frame;
class Animation;
class Menu;

class Chapter1 : public Branch
{
    public:
		Chapter1(BranchManager* bm);
		~Chapter1();
		void update(float delta);
		void draw(Canvas* canvas);
        void start(float delta);
		void input(float delta);
		void end(float delta);

	private:
		Text *text1, *text2;

		Chapter1(const Chapter1&);
		Chapter1& operator=(const Chapter1&);
};
#endif