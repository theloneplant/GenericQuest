#ifndef ANIMATION
#define ANIMATION

#include "Actor.h"
#include "Frame.h"
#include "Timer.h"

class Animation : public Frame
{
    public:
		Animation(string file, float x, float y, bool newLoop, bool newReverse, int newFps);
		Animation(string file, float x, float y);
		~Animation();
        virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void pause();
		virtual void play();
		virtual void restart();
		virtual void setForegroundColor(int color);
		virtual void setBackgroundColor(int color);
		virtual void setDimension(int x, int y);
		virtual void setPosition(float x, float y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual void setFinished(bool newFinished);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();
		virtual bool isFinished();

	private:
		vector<Frame*> anim;
		Timer timer;
		unsigned int fps, currentFrame;
		bool paused, loop, reverse, reversed, finished;
};
#endif