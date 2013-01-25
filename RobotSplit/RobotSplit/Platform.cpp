#include "Platform.h"
#include <sstream>
#include <cassert>

Platform::Platform(sf::Vector2f position)
	:Unit(position, "Platform")
	,mLives(0)
	,mDestructible(false)
{
	mSprite=TextureManager::getSprite("Tile1");
	mSprite.setPosition(position);
}

Platform::Platform(int lives, sf::Vector2f position, sf::Vector2f size)
	:Unit(position, "Platform")
	,mLives(lives)
	,mDestructible(true)
{
	assert(lives>=1);
	assert(lives<=3);
	
	std::stringstream spriteName;
	spriteName<<"Platform"<<lives;
	mSprite.setPosition(mPosition);
	//mSprite=TextureManager::getSprite(spriteName.str());
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