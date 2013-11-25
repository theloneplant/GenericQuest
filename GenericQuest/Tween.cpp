#include "stdafx.h"
#include "Tween.h"

Tween::Tween(EaseType newEase, Actor* myActor, int finalX, int finalY, float newDuration)
{
	ease = newEase;
	actor = myActor;
	startPos = actor->getPosition();
	deltaPos.x = finalX - startPos.x;
	deltaPos.y = finalY - startPos.y;
	timer.reset();
	duration = newDuration;
	finished = false;
}

void Tween::update()
{
	if (!finished)
	{
		float percent = timer.getTime() / duration;

		if (percent <= 1)
		{
			switch(ease)
			{
				case Linear:
					easeLinear();
					break;
				case SinIn:
					easeSinIn();
					break;
				case SinOut:
					easeSinOut();
					break;
				case SinInOut:
					easeSinInOut();
					break;
			}
		}
		else
			finished = true;
	}
}

void Tween::easeLinear()
{
	int x, y;

	x = deltaPos.x * timer.getTime() / duration + startPos.x;
	y = deltaPos.y * timer.getTime() / duration + startPos.y;

	actor->setPosition(x, y);
}

void Tween::easeSinIn()
{
	int x, y;

	x = -deltaPos.x * (cos(pi / 2 * timer.getTime() / duration)) + deltaPos.x + startPos.x;
	y = -deltaPos.y * (cos(pi / 2 * timer.getTime() / duration)) + deltaPos.y + startPos.y;

	actor->setPosition(x, y);
}

void Tween::easeSinOut()
{
	int x, y;

	x = deltaPos.x * (sin(pi / 2 * timer.getTime() / duration)) + startPos.x;
	y = deltaPos.y * (sin(pi / 2 * timer.getTime() / duration)) + startPos.y;

	actor->setPosition(x, y);
}

void Tween::easeSinInOut()
{
	int x, y;

	x = -deltaPos.x / 2 * (cos(pi * timer.getTime() / duration) - 1) + startPos.x;
	y = -deltaPos.y / 2 * (cos(pi * timer.getTime() / duration) - 1) + startPos.y;

	actor->setPosition(x, y);
}

void Tween::restart()
{
	timer.reset();
	finished = false;
}

void Tween::restart(int startX, int startY)
{
	timer.reset();
	finished = false;
}

void Tween::restart(int startX, int startY, int finishX, int finishY)
{
	timer.reset();
	finished = false;
}

Vector Tween::getStartPos()
{
	return startPos;
}

Vector Tween::getFinalPos()
{
	Vector final;

	final.x = startPos.x + deltaPos.x;
	final.y = startPos.y + deltaPos.y;

	return final;
}

Timer Tween::getTimer()
{
	return timer;
}

bool Tween::isFinished()
{
	return finished;
}