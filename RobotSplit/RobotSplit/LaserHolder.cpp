#include "LaserHolder.h"

LaserHolder::LaserHolder(Laser* laser):
	Unit(laser->getPosition(), "LaserHolder", "LaserHolder", false)
{
	mStandby=TextureManager::getSprite("YellowLaserHolder");
	mOn=TextureManager::getSprite("YellowLaserHolder");
	mOff=TextureManager::getSprite("YellowLaserHolder");
	mActiveSprite=&mStandby;
	mPosition=laser->getPosition();//+sf::Vector2f(2, -2);
	mRotation=laser->getRotation()+180;
	//mSprite.setOrigin(8, 8);
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

