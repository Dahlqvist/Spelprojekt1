#include "LaserHolder.h"

LaserHolder::LaserHolder(Laser* laser, std::string id, bool active):
	Unit(laser->getPosition(), id, "LaserHolder", false),
	mActive(active)
{
	mStandby=TextureManager::getSprite("YellowLaserHolder");
	mOn=TextureManager::getSprite("YellowLaserHolder");
	mOff=TextureManager::getSprite("YellowLaserHolder");
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

