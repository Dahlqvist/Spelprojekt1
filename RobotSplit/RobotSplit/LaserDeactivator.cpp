#include "LaserDeactivator.h"

#include <cassert>

LaserDeactivator::LaserDeactivator(Trigger* trigger, float rotation)
	:Trigger(*trigger)
	,mPressed(false)
	,mStartPressed(false)
	,mRotation(rotation)
{
	assert(rotation==0 || rotation==90 || rotation==180 || rotation==270);
	mSprite.setRotation(rotation);
	if (rotation==180)
	{
		mPosition+=sf::Vector2f(0, mSprite.getGlobalBounds().height*2);
	}
	mSprite.setPosition(mPosition);
}

void LaserDeactivator::hitOnce()
{
	mTriggedObject->deactivate();
	mPressed=true;
}

void LaserDeactivator::draw()
{
	if (mPressed && mAnimation!=0x0 && mAnimation->getCurrentFrame()<2)
	{
		Unit::draw();
		mSprite.setRotation(mRotation);
	}
}

void LaserDeactivator::reset()
{
	mPressed=mStartPressed;
	mAnimation->restart();
	mSprite=mAnimation->getSprite();
	mSprite.setPosition(mPosition);
	mSprite.setRotation(mRotation);
}

void LaserDeactivator::setReset()
{
	mStartPressed=mPressed;
}