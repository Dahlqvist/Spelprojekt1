#include "MiniBot.h"

MiniBot::MiniBot(sf::Vector2f position, float rotation, float length, bool sideways):
Unit(position, "MiniBot", "MiniBot", false, false),
	mWalking("MiniBot", 100, 1),
	mCharging("MiniBot", 100, 1),
	mRelease("StixBrainAni", 100, 7)
{
	mPosition=position;
	mStartPosition=position;
	mLength=length;
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
	if(mRotation==90)
	{
		mSprite.setOrigin(32, 32);
		mSprite.setRotation(90);
	}
	if(mRotation==180)
	{
		mSprite.setOrigin(32, 32);
		mSprite.setRotation(180);
	}
	if(mRotation==270)
	{
		mSprite.setOrigin(0, 0);
		mSprite.setRotation(270);
	}
	return mSprite;
}