#ifndef TWEEN
#define TWEEN

#include "Actor.h"
#include "Vector.h"
#include "Timer.h"

enum EaseType  {Linear, SinIn, SinOut, SinInOut};

static class Tween
{
	public:
		Tween(EaseType newEase, Actor* myActor, int finalX, int finalY, float newDuration);
		void update();
		void easeLinear();
		void easeSinIn();
		void easeSinOut();
		void easeSinInOut();
		void restart();
		void restart(int finalX, int finalY);
		void add(Actor* actor);
		void setEaseType(EaseType newEase);
		Vector getFinalPos();
		Timer getTimer();
		bool isFinished();

	private:
		EaseType ease;
		vector<Actor*> actors;
		vector<Vector> actorPos;
		Vector deltaPos;
		Timer timer;
		float duration;
		bool finished;
};

#endif