#include "Laser.h"

Laser::Laser(sf::Vector2f position, std::string laserColor, bool active, float length, float rotate):
	Unit(position, laserColor, "Laser", false),
	mMaxLength(length),
	mActive(active),
	mLength(0),
	mRotation(rotate),
	mRedLaser("RedLaser", 10, 2),
	mBlueLaser("BlueLaser", 10, 2),
	mYellowLaser("YellowLaser", 10, 2),
	mSpeed(9)
{
	if(laserColor=="Red")
	{
		mAnimation=&mRedLaser;
	}
	if(laserColor=="Blue")
	{
		mAnimation=&mBlueLaser;
	}
	if(laserColor=="Yellow")
	{
		mAnimation=&mYellowLaser;
	}
	mId=laserColor;
}

void Laser::setLength(float l)
{
	mMaxLength=l;
}

void Laser::update()
{
	mAnimation->update();
	if(mMaxLength>mLength && mActive==true)
	{
		mLength+=mSpeed;
	}
	else if(mLength>0 && mActive==false)
	{
		mLength-=mSpeed;
	}
}

sf::Sprite Laser::getSprite()
{
	mSprite=mAnimation->getSprite();
	mSprite.setTextureRect(sf::IntRect(mSprite.getTextureRect().left,  mSprite.getTextureRect().top, mSprite.getTextureRect().width, mLength));
	mSprite.setPosition(mPosition);
	//mSprite.setOrigin(-8, -4);
	mSprite.setRotation(mRotation);
	return mSprite;
}