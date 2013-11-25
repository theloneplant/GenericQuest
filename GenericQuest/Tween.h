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
		void restart(int startX, int startY);
		void restart(int startX, int startY, int finishX, int finishY);
		Vector getStartPos();
		Vector getFinalPos();
		Timer getTimer();
		bool isFinished();

	private:
		EaseType ease;
		Actor* actor;
		Vector startPos, deltaPos;
		Timer timer;
		float duration;
		bool finished;
};

#endif