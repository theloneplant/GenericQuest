#include "stdafx.h"
#include "FileIO.h"
#include "Frame.h"
#include "Animation.h"

Animation::Animation(string file, int x, int y, bool newLoop, bool newReverse, int newFps)
{
	Actor::Actor();
	setPosition(x, y);
	FileIO::buildAnimation(file, anim, dimension);
	currentFrame = 0;
	frame = anim.at(currentFrame)->getFrame();

	paused = true;
	reversed = false;
	loop = newLoop; //Does the animation loop?
	reverse = newReverse; //Does the animation reverse after looping?
	fps = newFps;
}

Animation::Animation(string file, int x, int y)
{
	setPosition(x, y);
	FileIO::buildAnimation(file, anim, dimension);
	currentFrame = 0;
	paused = true;
	reversed = false;
	loop = false;
	reverse = false;
	fps = 10;
}

Animation::~Animation()
{
	//Delete frames
	for (int i = 0; i < anim.size(); i++)
	{
		delete anim.at(i);
	}
}

void Animation::update(float delta)
{
	Actor::update(delta);

	if (!paused)
	{
		if (timer.getTime() >= (1.0 / fps))
		{
			if (!reversed)
			{
				if (currentFrame + 1 < anim.size())
					currentFrame++;
				else if (loop)
				{
					if (reverse)
						reversed = true;
					else if(loop)
						currentFrame = 0;
				}
			}
			else
			{
				if (currentFrame - 1 >= 0)
					currentFrame--;
				else if (loop)
				{
					if (reverse)
						reversed = false;
					else if (loop)
						currentFrame = anim.size() - 1;
				}
			}
			timer.reset();
		}
	}
	else
	{
		timer.reset();
	}

	for (int i = 0; i < anim.size(); i++)
	{
		anim.at(i)->setPosition(position.x, position.y);
	}
	
	frame = anim.at(currentFrame)->getFrame();
}

void Animation::draw(Canvas* canvas)
{
	anim.at(currentFrame)->draw(canvas);
}

void Animation::pause()
{
	paused = true;
}

void Animation::play()
{
	paused = false;
}

void Animation::setDimension(int x, int y)
{
	Actor::setDimension(x, y);
}

void Animation::setPosition(int x, int y)
{
	Actor::setPosition(x, y);
	
	for (int i = 0; i < anim.size(); i++)
	{
		anim.at(i)->setPosition(position.x, position.y);
	}
}

void Animation::setVelocity(float x, float y)
{
	Actor::setVelocity(x, y);
}

void Animation::setAcceleration(float x, float y)
{
	Actor::setAcceleration(x, y);
}

Dimension Animation::getDimension()
{
	return dimension;
}
Vector Animation::getPosition()
{
	return position;
}

Vector Animation::getVelocity()
{
	return velocity;
}

Vector Animation::getAcceleration()
{
	return acceleration;
}