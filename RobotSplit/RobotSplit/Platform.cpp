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
	return "";
}

Platform::Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size, sf::Vector2f offset)
	:Unit(position, size, offset, "Platform", spriteName)
	,mLives(0)
	,mStartLives(0)
	,mDestructible(false)
{
	mSprite.setPosition(position);
}

Platform::Platform(int lives, sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset)
	:Unit(position, size, offset, "Platform", getSpriteName(lives))
	,mLives(lives)
	,mStartLives(lives)
	,mDestructible(true)
{
	assert(lives>=1);
	assert(lives<=3);
}

Platform::~Platform()
{
	if (mAnimation!=0x0)
	{
		delete mAnimation;
	}
}

void Platform::draw()
{
	
	if (mDestructible && getSpriteName(mLives)=="")
	{
		if (mAnimation->getCurrentFrame()==3)
		{
			mSprite=TextureManager::getSprite("");
			mSize=sf::Vector2f(0,0);
		}
		else
		{
			Unit::draw();
		}
	}
	
	mSprite.setPosition(mPosition);
}

void Platform::hitOnce()
{
	if (mDestructible)
	{
		--mLives;
		mSprite=TextureManager::getSprite(getSpriteName(mLives));

		if (mLives==0)
		{
			mAnimation=new Animation("BreakAnim", 100, 5);
		}
	}
}

void Platform::reset()
{
	mLives=mStartLives;
	if (mStartLives!=0)
	{
		mSprite=TextureManager::getSprite(getSpriteName(mLives));
	}
}