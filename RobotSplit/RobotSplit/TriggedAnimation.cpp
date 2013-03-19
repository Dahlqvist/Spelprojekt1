#include "TriggedAnimation.h"

TriggedAnimation::TriggedAnimation(sf::Vector2f position, std::string id, std::string spriteName, int speed, int frames)
	:Unit(position, id, new Animation(spriteName, speed, frames), false, true)
	,mActivated(false)
	,mDeactivated(false)
{
	
}

void TriggedAnimation::activate()
{
	mActivated=true;
	mSprite=mAnimation->getSprite();
}

void TriggedAnimation::draw()
{
	if (mActivated && !mDeactivated)
	{
		Unit::draw();
		if (mAnimation->getCurrentFrame()==mAnimation->getMaxFrame()-1)
		{
			mDeactivated=true;
		}
	}
	else
	{
		mSprite=TextureManager::getSprite("");
	}
}
