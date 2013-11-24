#ifndef BRANCH
#define BRANCH

class BranchManager;
class Symbol;
class Timer;
class Actor;
class Frame;
class Menu;
class Canvas;

enum State{Start, Input, End}; //Used in main loop to only use a specific update

class Branch
{
    public:
		Branch();
		Branch(BranchManager* bm);
		~Branch();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
        virtual void start(float delta);
		virtual void input(float delta);
		virtual void end(float delta);

	protected:
		BranchManager* manager;
		vector<Actor*> myFrames;
		State state;

	private:
		Branch(const Branch &);
		Branch& operator=(const Branch &);
};
#endif