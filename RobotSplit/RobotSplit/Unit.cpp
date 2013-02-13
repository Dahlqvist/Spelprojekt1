#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
{
	mPosition=position;
	mSize=sf::Vector2f(0,0);
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid)
	:GameObject()
	,mSolid(solid)
	,mSprite(animation->getSprite())
{
	mAnimation =animation;
	mPosition=position;
	mSize=sf::Vector2f(0,0);
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, sf::Vector2f size, std::string id, std::string spriteName, bool solid)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
{
	mPosition=position;
	mSize=size;
	mId=id;
	mSprite.setPosition(mPosition);
}

Unit::Unit(sf::Vector2f position, sf::Vector2f size, std::string id, Animation* animation, bool solid)
	:GameObject()
	,mSolid(solid)
	,mSprite(animation->getSprite())
{
	mAnimation =animation;
	mPosition=position;
	mSize=size;
	mId=id;
	mSprite.setPosition(mPosition);
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