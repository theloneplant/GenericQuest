#ifndef ACTOR
#define ACTOR

#include "Dimension.h"
#include "Vector.h"

class Canvas;

class Actor
{
    public:
		Actor();
		~Actor();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void setDimension(int x, int y);
		virtual void setPosition(int x, int y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();

	protected:
		Dimension dimension;
		Vector position, velocity, acceleration;

	private:
		Actor(const Actor&);
		Actor& operator=(const Actor&);
};
#endif