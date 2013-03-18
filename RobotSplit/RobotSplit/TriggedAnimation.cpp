#include "TriggedAnimation.h"

TriggedAnimation::TriggedAnimation(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, int speed, int frames)
	:Unit(position, size, offset, id, new Animation(spriteName, speed, frames), false, true)
	,mActivated(false)
{
	mSprite=TextureManager::getSprite("");
}

void TriggedAnimation::activate()
{
	mActivated=true;
	mSprite=mAnimation->getSprite();
}

void TriggedAnimation::draw()
{
	if (mActivated)
	{
		Unit::draw();
	}
}
