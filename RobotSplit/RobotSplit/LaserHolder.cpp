#include "LaserHolder.h"
#include <iostream>
#include "Sound.h"

LaserHolder::LaserHolder(Laser* laser, std::string id, sf::Vector2f size, sf::Vector2f offset, bool active):
	Unit(laser->getPosition(), size, offset, id, "LaserHolder", false),
	mActive(active),
	mStartActive(active),
	mLaser(laser),
	mOff("LaserNewOffAni", 100, 4)
{
	mStandby=TextureManager::getSprite("LaserNewOn");
	mOn=TextureManager::getSprite("LaserNewOn");
	mActiveSprite=&mStandby;
	mPosition=laser->getPosition();
	mRotation=laser->getRotation()+180;
	mActiveSprite->setRotation(mRotation);
	if(laser->getRotation()==0)
	{
		mPosition+=sf::Vector2f(6, 4);
	}
	if(laser->getRotation()==90)
	{
		mPosition+=sf::Vector2f(-4, 6);
	}
	if(laser->getRotation()==180)
	{
		mPosition+=sf::Vector2f(-6, -4);
	}
	if(laser->getRotation()==270)
	{
		mPosition+=sf::Vector2f(4, -6);
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
	else if(mOff.getCurrentFrame()!=mOff.getMaxFrame()-1)
	{
		mOff.update();
		mOffSprite=mOff.getSprite();
		mActiveSprite=&mOffSprite;
	}
	//mLaser->deactivate();
}

void LaserHolder::hit(){
	if(mActive==true)
	{
		Sound::playSound("Laser");
		mActiveSprite=&mOn;
		mLaser->activate();
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
	mOffSprite=mOff.getSprite();
	mActiveSprite=&mOffSprite;
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

void LaserHolder::setReset()
{
	mStartActive=mActive;
}

void LaserHolder::rotate(float r)
{
	mRotation=r+180;
	mLaser->rotate(r);
	//Get Visibility range, length and rotaiton angle.
	float	visibility=0;
	float	length=mLaser->getLength();
	switch(int(mLaser->getRotation()))
	{
	case 0:
		visibility=getSize().x/2;
		mPosition=mLaser->getPosition()+sf::Vector2f(-10, -8);
		this->mSize=sf::Vector2f(visibility*2,length+visibility*2);
		this->mOffset=sf::Vector2f(-visibility,-length-visibility);
		break;
	case 90:
		visibility=getSize().y/2;
		mPosition=mLaser->getPosition()+sf::Vector2f(-8, 10);
		this->mSize=sf::Vector2f(length+visibility*2,visibility*2);
		this->mOffset=sf::Vector2f(-length-visibility,-visibility);
		break;
	case 180:
		visibility=getSize().x/2;
		mPosition=mLaser->getPosition()+sf::Vector2f(10, 8);
		this->mSize=sf::Vector2f(visibility*2,length+visibility*2);
		this->mOffset=sf::Vector2f(-visibility,-visibility);
		break;
	case 270:
		visibility=getSize().y/2;
		mPosition=mLaser->getPosition()+sf::Vector2f(8, -10);
		this->mSize=sf::Vector2f(length+visibility*2,visibility*2);
		this->mOffset=sf::Vector2f(-visibility,-visibility);
		break;
	}
	setPosition(mPosition);
}

void LaserHolder::setPosition(sf::Vector2f position)
{
	sf::Vector2f	offset=mPosition-mLaser->getPosition();
	offset.x=abs(offset.x);
	offset.y=abs(offset.y);
	mPosition=position;
	switch(int(mLaser->getRotation()))
	{
	case 0:
		offset.x=abs(offset.x);
		offset.y=abs(offset.y);
		break;
	case 90:
		offset.x=-abs(offset.x);
		offset.y=abs(offset.y);
		break;
	case 180:
		offset.x=-abs(offset.x);
		offset.y=-abs(offset.y);
		break;
	case 270:
		offset.x=abs(offset.x);
		offset.y=-abs(offset.y);
		break;
	}
	mLaser->setPosition(position-offset);
	mSprite.setPosition(mPosition);
}

bool LaserHolder::isSolid()
{
	return mSolid;
}

bool LaserHolder::isActive()
{
	return mActive;
}

std::string LaserHolder::getId()
{
	return mId;
}

sf::Vector2f LaserHolder::getSize()
{
	return mSize;
}

sf::Sprite	LaserHolder::getSprite()
{
	mActiveSprite->setRotation(mRotation);
	mActiveSprite->setPosition(mPosition);
	return *mActiveSprite;
}

sf::Vector2f LaserHolder::getPosition()
{
	return mPosition;
}

float	LaserHolder::getRotation()
{
	return mRotation;
}

Laser*	LaserHolder::getLaser()
{
	return mLaser;
}

void	LaserHolder::setVisibilityRange(float range)
{
	float visibility=range,length=getLaser()->getLength();
	switch(int(mLaser->getRotation()))
	{
	case 0:
		this->mSize=sf::Vector2f(visibility*2,length+visibility*2);
		this->mOffset=sf::Vector2f(-visibility,-length-visibility);
		break;
	case 90:
		this->mSize=sf::Vector2f(length+visibility*2,visibility*2);
		this->mOffset=sf::Vector2f(-length-visibility,-visibility);
		break;
	case 180:
		this->mSize=sf::Vector2f(visibility*2,length+visibility*2);
		this->mOffset=sf::Vector2f(-visibility,-visibility);
		break;
	case 270:
		this->mSize=sf::Vector2f(length+visibility*2,visibility*2);
		this->mOffset=sf::Vector2f(-visibility,-visibility);
		break;
	}
}

void	LaserHolder::setActive(bool newbool)
{
	if(newbool)
	{
		activate();
	}
	else
	{
		deactivate();
	}
}