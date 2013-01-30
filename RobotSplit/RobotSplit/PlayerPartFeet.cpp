#include "PlayerPartFeet.h"
#include <iostream>

PlayerPartFeet::PlayerPartFeet():
mLeftAnimation("StixLowerAni", 200, 8),
	mRightAnimation("StixLowerAni", 200, 8),
	mLeft("StixLower", 200, 1),
	mRight("StixLower", 200, 1),
	mFeetExt("StixUpper")
{
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(0, 0);
	mAttached=false;
	mAniTime=0;
	mAnimationTimer.restart();
	mUnit=0;
	mFuel=100;
}
void PlayerPartFeet::update()
{
	mActiveAnimation->update();
	if(mJump>0)
	{
		if(mJumpClock.getElapsedTime().asSeconds()>0.15)
		{
			mJump-=1;
			mJumpClock.restart();
		}
		else
		{
			PlayerPartFeet::setPosition(sf::Vector2f(0, -mJump));
		}
	}
} 
void PlayerPartFeet::draw()
{

}
void PlayerPartFeet::setPosition(sf::Vector2f Vec)
{
	if(Vec.x!=0)
	{
		mActiveAnimation=&mRightAnimation;
	}
	if(mAttached==false)
	{
		mPosition+=Vec;
	}
	else
	{
		if(mUnit==&mRightWall){
			mPosition+=Vec;
			mActiveAnimation=&mRightAnimation;
		}
		//En massa kod för när den går på väggar och liknande =)
	}
}
sf::Vector2f PlayerPartFeet::getPosition()
{
	return mPosition;
} 
sf::Sprite PlayerPartFeet::getSprite()
{
	mActiveAnimation->setPosition(mPosition);
	/*if(mUnit==&mRightWall)
	{
		sf::Sprite Temp=mActiveAnimation->getSprite();
		Temp.setOrigin(Temp.getTextureRect().width/2, Temp.getTextureRect().width/2);
		Temp.setRotation(90);
		return Temp;
	}*/
	if(mUnit==&mFeetExt)
	{
		mFeetExt.setPosition(mPosition+sf::Vector2f(0, -32));
		mUnit=&mFeetExt;
		return mUnit->getSprite();
	}
	return mActiveAnimation->getSprite();
}
std::string PlayerPartFeet::getId()
{
	return mId;
}
void PlayerPartFeet::restartTimer()
{
	mActiveAnimation->restart();
}
bool PlayerPartFeet::getAttached()
{
	return mAttached;
}
void PlayerPartFeet::setAttached(bool b)
{
	mAttached=b;
	if(!mAttached){
		mUnit=0;
	}
	if(mAttached){
		mFeetExt.setPosition(mPosition+sf::Vector2f(0, -32));
		mUnit=&mFeetExt;
	}
}
void PlayerPartFeet::jump()
{
	mJump=7;
	mJumpClock.restart();
}
void PlayerPartFeet::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		mActiveAnimation=&mRight;
	}
}
Unit* PlayerPartFeet::getUnit()
{
	return mUnit;
}
void PlayerPartFeet::activateRocketBoots()
{
	if(mFuel>0 && mAttached==false)
	{
		mJump=0;
		PlayerPartFeet::setPosition(sf::Vector2f(0, -5));
		mFuel--;
	}
}
void PlayerPartFeet::reFuel(float fuel)
{
	if(mFuel<=0 && fuel<=100){
		mFuel=fuel;
	}
}
void PlayerPartFeet::jumpReset()
{
	mJump=3;
}