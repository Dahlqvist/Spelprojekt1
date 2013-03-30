#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid, bool behind)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
	,mSize(sf::Vector2f(0,0))
	,mHit(false)
	,mHitThisFrame(false)
	,mBehind(behind)
{
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid, bool behind)
	:GameObject()
	,mSolid(solid)
	,mSprite(animation->getSprite())
	,mSize(sf::Vector2f(0,0))
	,mBehind(behind)
{
	mAnimation =animation;
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, std::string spriteName, bool solid, bool behind)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
	,mSize(size)
	,mOffset(offset)
	,mBehind(behind)
{
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, sf::Vector2f size, sf::Vector2f offset, std::string id, Animation* animation, bool solid, bool behind)
	:GameObject()
	,mSolid(solid)
	,mSprite(animation->getSprite())
	,mSize(size)
	,mOffset(offset)
	,mBehind(behind)
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
}