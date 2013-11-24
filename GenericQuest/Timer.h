#ifndef TIMER
#define TIMER

class Timer
{
	public:
		Timer();
		void reset();
		float getDelta();
		float getTime();
		bool hasElapsed(float elapsed);

	private:
		int start, oldTime;
};

#endif