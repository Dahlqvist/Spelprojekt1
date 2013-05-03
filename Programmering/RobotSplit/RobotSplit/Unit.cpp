#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid, bool behind, sf::Vector2f speed, sf::Vector2f distance, bool direction)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
	,mSize(sf::Vector2f(0,0))
	,mHit(false)
	,mHitThisFrame(false)
	,mBehind(behind)
	,mSpeed(speed)
	,mDistance(distance)
	,mDirection(direction)
{
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid, bool behind, sf::Vector2f speed, sf::Vector2f distance, bool direction)
	:GameObject()
	,mSolid(solid)
	,mSprite(animation->getSprite())
	,mSize(sf::Vector2f(0,0))
	,mBehind(behind)
	,mSpeed(speed)
	,mDistance(distance)
	,mDirection(direction)
{
	mAnimation =animation;
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, bool solid, bool behind, sf::Vector2f speed, sf::Vector2f distance, bool direction)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
	,mSize(size)
	,mOffset(offset)
	,mBehind(behind)
	,mSpeed(speed)
	,mDistance(distance)
	,mDirection(direction)
{
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, bool solid, bool behind, sf::Vector2f speed, sf::Vector2f distance, bool direction)
	:GameObject()
	,mSolid(solid)
	,mSprite(animation->getSprite())
	,mSize(size)
	,mOffset(offset)
	,mBehind(behind)
	,mSpeed(speed)
	,mDistance(distance)
	,mDirection(direction)
{
	mAnimation =animation;
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::~Unit()
{
	if (mAnimation!=0x0)
	{
		delete mAnimation;
	}
}

void Unit::draw()
{
	if (mAnimation!=nullptr)
	{
		mAnimation->update();
		mSprite=mAnimation->getSprite();
	}
	mSprite.setPosition(mPosition);
}

void Unit::update()
{
	if (mHit==false)
	{
		mWasHit=false;
	}
	mHit=false;

	if (mSpeed.x!=0 || mSpeed.y!=0)
	{
		mPosition+=mSpeed;
		if ((mDirection=0 /*Left*/ && (mPosition.x<(mStartPosition.x-mDistance.x) || (mPosition.y<(mStartPosition.y-mDistance.y)))) || (mDirection=1 /*Right*/ && (mPosition.x>(mStartPosition.x+mDistance.x) || (mPosition.y>(mStartPosition.y+mDistance.y)))))
		{
			mSpeed.x*=-1;
			mSpeed.y*=-1;
		}
	}
}