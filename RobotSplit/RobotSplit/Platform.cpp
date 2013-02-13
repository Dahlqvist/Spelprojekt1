#include "Platform.h"
#include <sstream>
#include <cassert>

Platform::Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size)
	:Unit(position, size, "Platform", spriteName)
	,mLives(0)
	,mDestructible(false)
{
	mSprite.setPosition(position);
}

Platform::Platform(int lives, sf::Vector2f position, std::string spriteName, sf::Vector2f size)
	:Unit(position, size, "Platform", spriteName)
	,mLives(lives)
	,mDestructible(true)
{
	assert(lives>=1);
	assert(lives<=3);
}

void Platform::update()
{
	if (mLives==1)
	{
		mSolid=false;
	}
}

void Platform::draw()
{
	mSprite.setPosition(mPosition);
}

void Platform::hit()
{
	if (mDestructible)
	{
		--mLives;
	}
	std::stringstream spriteName;
	spriteName<<"Platform"<<mLives;
	//mSprite=TextureManager::getSprite(spriteName.str());
}