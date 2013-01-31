#include "Unit.h"

Unit::Unit(sf::Vector2f position, std::string id, std::string spriteName, bool solid)
	:GameObject()
	,mSolid(solid)
	,mSprite(TextureManager::getSprite(spriteName))
	,mAnimation(nullptr)
{
	mPosition=position;
	mId=id;
	mSprite.setPosition(mPosition);
	if(id=="Lava")
	{
	}
}

Unit::Unit(sf::Vector2f position, std::string id, Animation* animation, bool solid)
	:GameObject()
	,mSolid(solid)
	,mAnimation(animation)
	,mSprite(animation->getSprite())
{
	mPosition=position;
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