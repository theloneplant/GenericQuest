#ifndef BRANCH
#define BRANCH

#include "Timer.h"

class BranchManager;
class Symbol;
class Actor;
class Frame;
class Tween;
class Canvas;

enum State{Start, Input, End}; //Used in main loop to only use a specific update

class Branch
{
    public:
		Branch(BranchManager* bm = NULL);
		virtual ~Branch();
		virtual void init();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
        virtual void start(float delta);
		virtual void input(float delta);
		virtual void end(float delta);
		virtual void setState(State newState);
		virtual void resetTimer();

	protected:
		BranchManager* manager;
		Timer timer;
		vector<Actor*> myFrames;
		vector<Tween*> myTweens;
		State state;

	private:
		Branch(const Branch &);
		Branch& operator=(const Branch &);
};
#endif