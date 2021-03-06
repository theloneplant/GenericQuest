#ifndef ACTOR
#define ACTOR

#include "Dimension.h"
#include "Vector.h"

class Canvas;

class Actor
{
    public:
		Actor();
		virtual ~Actor();
		virtual void update(float delta);
		virtual void draw(Canvas* canvas);
		virtual void setDimension(int x, int y);
		virtual void setPosition(float x, float y);
		virtual void setVelocity(float x, float y);
		virtual void setAcceleration(float x, float y);
		virtual void setHidden(bool newHidden);
		virtual Dimension getDimension();
		virtual Vector getPosition();
		virtual Vector getVelocity();
		virtual Vector getAcceleration();
		virtual bool isHidden();

	protected:
		Dimension dimension;
		Vector position, velocity, acceleration;
		bool hidden;

	private:
		Actor(const Actor&);
		Actor& operator=(const Actor&);
};
#endif