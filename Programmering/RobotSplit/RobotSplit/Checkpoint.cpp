#include "Checkpoint.h"
#include "Sound.h"

Checkpoint::Checkpoint(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, Animation* animation)
	:Unit(position, size, offset, "Checkpoint", animation, false, true)
	,mActive(false)
{
	//mAnimation->setAnimate(false);
}

void Checkpoint::update()
{
	Unit::update();
	if (!mActive)
	{
		mAnimation->setCurrentFrame(0);
	}
}

void Checkpoint::activate()
{
	if (!mActive)
	{
		Sound::playSound("Checkpoint");
	}
	//mAnimation->setCurrentFrame(4);
	mActive=true;
}

void Checkpoint::deactivate()
{
	//mAnimation->setCurrentFrame(0);
	mActive=false;
}

void Checkpoint::draw()
{
	Unit::draw();
}

void Checkpoint::setCurrentFrame(int frame)
{
	if (!mActive)
	{
		mAnimation->setCurrentFrame(frame);
	}
}