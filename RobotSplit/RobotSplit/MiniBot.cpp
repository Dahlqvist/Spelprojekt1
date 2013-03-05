#include "MiniBot.h"

MiniBot::MiniBot(sf::Vector2f position, float rotation, float length, bool sideways):
Unit(position, "MiniBot", "MiniBot", false, false),
	mWalking("MiniBot", 100, 1),
	mCharging("MiniBotCharge", 100, 1),
	mRelease("StixShootAniL", 100, 8)
{
	mPosition=position;
	mStartPosition=position;
	mLength=length+10;
	mGoingRight=true;
	mAnimation=&mWalking;
	mCharge=0;
	mMaxCharge=500;
	mRotation=rotation;
	mSideways=sideways;
}

void MiniBot::update()
{
	mAnimation->update();
	mCharge++;
	if(mSideways==true)
	{
		if(mPosition.x-mStartPosition.x>mLength)
		{
			mGoingRight=false;
		}
		if(mPosition.x-mStartPosition.x<0)
		{
			mGoingRight=true;
		}
		if(mCharge<mMaxCharge)
		{
			if(mGoingRight)
			{
				mPosition.x++;
				mSprite.setPosition(mPosition);
			}
			else
			{
				mPosition.x--;
				mSprite.setPosition(mPosition);
			}
			if(mCharge>mMaxCharge-100 && mAnimation!=&mCharging)
			{
				mAnimation=&mCharging;
			}
		}
		else
		{
			mAnimation=&mRelease;
			if(mAnimation->getCurrentFrame()==6)
			{
				mAnimation=&mWalking;
				mCharge=0;
				mRelease.restart();
			}
		}
	}
	else
	{
		if(mPosition.y-mStartPosition.y>mLength)
		{
			mGoingRight=false;
		}
		if(mPosition.y-mStartPosition.y<0)
		{
			mGoingRight=true;
		}
		if(mCharge<mMaxCharge)
		{
			if(mGoingRight)
			{
				mPosition.y++;
				mSprite.setPosition(mPosition);
			}
			else
			{
				mPosition.y--;
				mSprite.setPosition(mPosition);
			}
			if(mCharge>mMaxCharge-100 && mAnimation!=&mCharging)
			{
				mAnimation=&mCharging;
			}
		}
		else
		{
			mAnimation=&mRelease;
			if(mAnimation->getCurrentFrame()==6)
			{
				mAnimation=&mWalking;
				mCharge=0;
				mRelease.restart();
			}
		}
	}
}

sf::Sprite MiniBot::getSprite()
{
	mAnimation->setPosition(mPosition);
	mSprite=mAnimation->getSprite();
	if(mRotation==0)
	{
		if(mAnimation==&mRelease)
		{
			mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(-16, -32));
		}
	}
	if(mRotation==90)
	{
		mSprite.setOrigin(32, 32);
		mSprite.setRotation(90);
		if(mAnimation==&mRelease)
		{
			mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(32, -16));
		}
	}
	if(mRotation==180)
	{
		mSprite.setOrigin(32, 32);
		mSprite.setRotation(180);
		mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(-13, 0));
		if(mAnimation==&mRelease)
		{
			mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(16, 32));
		}
	}
	if(mRotation==270)
	{
		mSprite.setOrigin(0, 0);
		mSprite.setRotation(270);
		mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(0, 18));
		if(mAnimation==&mRelease)
		{
			mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(-32, 16));
		}
	}
	return mSprite;
}