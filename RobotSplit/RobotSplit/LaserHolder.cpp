#include "LaserHolder.h"
#include "Sound.h"
#include <iostream>

LaserHolder::LaserHolder(Laser* laser, std::string id, sf::Vector2f size, sf::Vector2f offset, bool active):
	Unit(laser->getPosition(), size, offset, id, "LaserHolder", false),
	mActive(active),
	mStartActive(active),
	mLaser(laser)
{
	mStandby=TextureManager::getSprite("LaserHolderStandby");
	mOn=TextureManager::getSprite("LaserHolderStandby");
	mOff=TextureManager::getSprite("LaserHolderOff");
	mActiveSprite=&mStandby;
	mPosition=laser->getPosition();
	mRotation=laser->getRotation()+180;
	mActiveSprite->setRotation(mRotation);
	if(laser->getRotation()==0)
	{
		mPosition+=sf::Vector2f(10, 8);
	}
	if(laser->getRotation()==90)
	{
		mPosition+=sf::Vector2f(-8, 10);
	}
	if(laser->getRotation()==180)
	{
		mPosition+=sf::Vector2f(-10, -8);
	}
	if(laser->getRotation()==270)
	{
		mPosition+=sf::Vector2f(8, -10);
	}
	mActiveSprite->setPosition(mPosition);
}

LaserHolder::~LaserHolder()
{
}

void LaserHolder::update()
{
	if(mActive==true)
	{
		mActiveSprite=&mStandby;
	}
	//mLaser->deactivate();
}

void LaserHolder::hit(){
	if(mActive==true)
	{
		mActiveSprite=&mOn;
		mLaser->activate();
		Sound::playSound("StandInLaser");
	}
}

void LaserHolder::activate()
{
	mLaser->activate();
	mActiveSprite=&mOn;
	mActive=true;
}

void LaserHolder::deactivate()
{
	mLaser->deactivate();
	mActiveSprite=&mOff;
	mActive=false;
}

void LaserHolder::reset()
{
	if (mStartActive)
	{
		activate();
	}
	else
	{
		deactivate();
	}
}