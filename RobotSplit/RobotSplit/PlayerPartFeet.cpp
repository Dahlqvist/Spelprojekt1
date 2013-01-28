#include "PlayerPartFeet.h"
#include <iostream>

PlayerPartFeet::PlayerPartFeet():
mLeftAnimation("StixLowerAni", 200, 8),
	mRightAnimation("StixLowerAni", 200, 8),
	mLeft("StixLower", 200, 1),
	mRight("StixLower", 200, 1)
{
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(0, 0);
	mAttached=false;
	mAniTime=0;
	mAnimationTimer.restart();
	mObject=0;
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
		mObject=0;
	}
	if(mAttached){
		//mObject=&mPlatt;
	}
}
void PlayerPartFeet::jump()
{
	mJump=8;
	mJumpClock.restart();
}
void PlayerPartFeet::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		mActiveAnimation=&mRight;
	}
}
GameObject* PlayerPartFeet::getObject()
{
	if(mObject!=0)
	{
		mObject->setPosition(mPosition+sf::Vector2f(10, -10));
	}
	return mObject;
}
void PlayerPartFeet::activateRocketBoots(){
	if(mFuel>0 && mAttached==false)
	{
		mJump=0;
		PlayerPartFeet::setPosition(sf::Vector2f(0, -5));
		mFuel--;
	}
}
void PlayerPartFeet::reFuel(float fuel){
	if(mFuel<=0 && fuel<=100){
		mFuel=fuel;
	}
}
void PlayerPartFeet::jumpReset(){
	mJump=3;
}