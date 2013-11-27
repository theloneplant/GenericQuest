#include "stdafx.h"
#include "Tween.h"

Tween::Tween(EaseType newEase, Actor* myActor, int finalX, int finalY, float newDuration)
{
	ease = newEase;
	actors.push_back(myActor);
	actorPos.push_back(actors.at(0)->getPosition());
	deltaPos.x = finalX - actors.at(0)->getPosition().x;
	deltaPos.y = finalY - actors.at(0)->getPosition().y;
	timer.reset();
	duration = newDuration;
	finished = true;
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
		{
			finished = true;

			for (unsigned int i = 0; i < actors.size(); i++)
			{
				float x, y;

				x = actorPos.at(i).x + deltaPos.x;
				y = actorPos.at(i).y + deltaPos.y;

				actors.at(i)->setPosition(x, y);
			}
		}
	}
}

void Tween::easeLinear()
{
	float x, y;

	x = deltaPos.x * timer.getTime() / duration;
	y = deltaPos.y * timer.getTime() / duration;

	for (unsigned int i = 0; i < actors.size(); i++)
	{
		actors.at(i)->setPosition(x + actorPos.at(i).x, y + actorPos.at(i).y);
	}
}

void Tween::easeSinIn()
{
	float x, y;

	x = -deltaPos.x * (cos(static_cast<float>(pi) / 2 * timer.getTime() / duration)) + deltaPos.x;
	y = -deltaPos.y * (cos(static_cast<float>(pi) / 2 * timer.getTime() / duration)) + deltaPos.y;

	for (unsigned int i = 0; i < actors.size(); i++)
	{
		actors.at(i)->setPosition(x + actorPos.at(i).x, y + actorPos.at(i).y);
	}
}

void Tween::easeSinOut()
{
	float x, y;

	x = deltaPos.x * (sin(static_cast<float>(pi) / 2 * timer.getTime() / duration));
	y = deltaPos.y * (sin(static_cast<float>(pi) / 2 * timer.getTime() / duration));

	for (unsigned int i = 0; i < actors.size(); i++)
	{
		actors.at(i)->setPosition(x + actorPos.at(i).x, y + actorPos.at(i).y);
	}
}

void Tween::easeSinInOut()
{
	float x, y;

	x = -deltaPos.x / 2 * (cos(static_cast<float>(pi) * timer.getTime() / duration) - 1);
	y = -deltaPos.y / 2 * (cos(static_cast<float>(pi) * timer.getTime() / duration) - 1);

	for (unsigned int i = 0; i < actors.size(); i++)
	{
		actors.at(i)->setPosition(x + actorPos.at(i).x, y + actorPos.at(i).y);
	}
}

void Tween::play()
{
	timer.reset();
	finished = false;
}

void Tween::restart(int finalX, int finalY)
{
	timer.reset();
	finished = false;
	deltaPos.x = finalX - actors.at(0)->getPosition().x;
	deltaPos.y = finalY - actors.at(0)->getPosition().y;

	for (unsigned int i = 0; i < actorPos.size(); i++)
	{
		actorPos.at(i) = actors.at(i)->getPosition();
	}
}

void Tween::add(Actor* actor)
{
	actors.push_back(actor);
	actorPos.push_back(actor->getPosition());
}

void Tween::setEaseType(EaseType newEase)
{
	ease = newEase;
}

void Tween::setDuration(float newDuration)
{
	duration = newDuration;
}

Vector Tween::getFinalPos()
{
	Vector final;

	final.x = deltaPos.x + actors.at(0)->getPosition().x;
	final.y = deltaPos.y + actors.at(0)->getPosition().y;

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