#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid, bool behind, float speed, int distance, int direction)
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

Unit::Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid, bool behind, float speed, int distance, int direction)
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

Unit::Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, bool solid, bool behind, float speed, int distance, int direction)
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

Unit::Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, bool solid, bool behind, float speed, int distance, int direction)
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
	//To check if object was hit this frame
	if (mHit==false)
	{
		mWasHit=false;
	}
	mHit=false;

	//Handle movement
	if (mSpeed!=0)
	{
		switch (mDirection)
		{
		case LEFT:
			mPosition.x-=mSpeed;
			break;
		case RIGHT:
			mPosition.x+=mSpeed;
			break;
		case UP:
			mPosition.y-=mSpeed;
			break;
		case DOWN:
			mPosition.y+=mSpeed;
			break;
		};
	}
}

void Unit::changeDirection(int distance)
{
	
}