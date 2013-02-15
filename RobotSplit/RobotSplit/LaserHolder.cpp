#include "LaserHolder.h"

LaserHolder::LaserHolder(Laser* laser, bool active):
	Unit(laser->getPosition(), "LaserHolder", "LaserHolder", false),
	mActive(active)
{
	mStandby=TextureManager::getSprite("LaserHolderStandby");
	mOn=TextureManager::getSprite("LaserHolderOn");
	mOff=TextureManager::getSprite("LaserHolderOff");
	mActiveSprite=&mStandby;
	mPosition=laser->getPosition();
	mRotation=laser->getRotation()+180;
	mActiveSprite->setRotation(mRotation);
	if(laser->getRotation()==0)
	{
		mPosition+=sf::Vector2f(10, 0);
	}
	if(laser->getRotation()==90)
	{
		mPosition+=sf::Vector2f(0, 10);
	}
	if(laser->getRotation()==180)
	{
		mPosition+=sf::Vector2f(-10, 0);
	}
	if(laser->getRotation()==270)
	{
		mPosition+=sf::Vector2f(0, -10);
	}
	mActiveSprite->setPosition(mPosition);
}

