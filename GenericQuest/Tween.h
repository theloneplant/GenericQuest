#ifndef TWEEN
#define TWEEN

class Actor;
class Vector;
class Timer;

enum EaseType  {Linear, //Only one kind of linear easing
				QuadIn, QuadOut, QuadInOut, 
				SinIn, SinOut, SinInOut};

static class Tween
{
	public:
		Tween(Actor* myActor, int finalX, int finalY, int duration);
		void update();
		void easeLinear();
		void easeQuadIn();
		void easeQuadOut();
		void easeQuadInOut();
		void easeSinIn();
		void easeSinOut();
		void easeSinInOut();
		void isFinished();

	private:
		Actor* actor;
		Vector startPos, finalPos;
		Timer timer;
		bool finished;
};

#endif