#include "Platform.h"
#include <cassert>

std::string getSpriteName(int lives)
{
	if (lives==3)
	{
		return "Break3";
	}
	if (lives==2)
	{
		return "Break2";
	}
	if (lives==1)
	{
		return "Break1";
	}
	return "Break3";
}

Platform::Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size, sf::Vector2f offset)
	:Unit(position, size, offset, "Platform", spriteName)
	,mLives(0)
	,mDestructible(false)
{
	mSprite.setPosition(position);
}

Platform::Platform(int lives, sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset)
	:Unit(position, size, offset, "Platform", getSpriteName(lives))
	,mLives(lives)
	,mDestructible(true)
{
	assert(lives>=1);
	assert(lives<=3);
}

void Platform::draw()
{
	mSprite.setPosition(mPosition);
}

void Platform::hitOnce()
{
	if (mDestructible)
	{
		--mLives;
		//mSprite=TextureManager::getSprite(getSpriteName(mLives));
	}
}