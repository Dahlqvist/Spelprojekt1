#include "Platform.h"
#include <cassert>
#include <iostream>

Platform::Platform(sf::Vector2f position, std::string spriteName, sf::Vector2f size, sf::Vector2f offset, bool behind)
	:Unit(position, size, offset, "Platform", spriteName, true, behind)
	,mLives(0)
	,mStartLives(0)
	,mDestructible(false)
	,mBreakAnim(0x0)
	,mNullAnim(0x0)
	,mStartAnimation(0x0)
{
	mSprite.setPosition(position);
}

Platform::Platform(int lives, sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string spriteName, bool behind)
	:Unit(position, size, offset, "Platform", new Animation(spriteName, 100, 3), true, behind)
	,mLives(lives)
	,mStartLives(lives)
	,mDestructible(true)
	,mBreakAnim(new Animation("BreakAnim", 100, 5))
	,mNullAnim(new Animation("",1,1))
{
	mStartAnimation=mAnimation;
	assert(lives>=1);
	assert(lives<=3);
}

Platform::~Platform()
{
	if (mStartAnimation!=0x0 && mAnimation!=mStartAnimation)
	{
		delete mStartAnimation;
	}
	if (mBreakAnim!=0x0 && mAnimation!=mBreakAnim)
	{
		delete mBreakAnim;
	}
	if (mNullAnim!=0x0 && mAnimation!=mNullAnim)
	{
		delete mNullAnim;
	}
}

void Platform::update()
{
	Unit::update();
	mHasCollided=false;
}

void Platform::draw()
{
	if (mDestructible)
	{
		//If destroyed
		if (mLives<=0)
		{
			mAnimation->setAnimate(true);
			if (mAnimation->getCurrentFrame()==3)
			{
				mAnimation->setAnimate(false);
				mAnimation=mNullAnim;
				mSize=sf::Vector2f(0,0);
			}
		}

		//Set tile based on lives left
		else 
		{
			mAnimation->setAnimate(false);
			mAnimation->setCurrentFrame(3-mLives);
		}

		Unit::draw();
	}
	
	mSprite.setPosition(mPosition);
}

void Platform::activate()
{
	if (mDestructible && mHasCollided)
	{
		--mLives;

		if (mLives==0)
		{
			mAnimation=mBreakAnim;
			mSize=sf::Vector2f(64, 36);
		}
	}
}

void Platform::hitOnce()
{
	mHasCollided=true;
}

void Platform::reset()
{
	if (mStartLives!=0)
	{
		mLives=mStartLives;
		mStartAnimation->setCurrentFrame(0);
		mBreakAnim->setCurrentFrame(0);
		mAnimation=mStartAnimation;
	}
}

void Platform::setReset()
{
	if (mStartLives!=0)
	{
		mStartLives=mLives;
		mStartAnimation=mAnimation;
	}
}