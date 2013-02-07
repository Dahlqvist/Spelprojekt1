#include "PlayerPartBody.h"
#include <iostream>

PlayerPartBody::PlayerPartBody(PlayerPart* Feet):
	mFeet(Feet),
	mLeftAnimation("StixUpperAniL", 200, 8),
	mRightAnimation("StixUpperAni", 200, 8),
	mLeft("StixUpperL", 200, 1),
	mRight("StixUpper", 200, 1)
{
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(100, 100);
	mAttached=true;
	mAniTime=0;
	mAnimationTimer.restart();
	mUnit=0;
}
void PlayerPartBody::update()
{
	mActiveAnimation->update();
	if(mJump>0)
	{
		if(mJumpClock.getElapsedTime().asSeconds()>0.1)
		{
			mJump-=1.3;
			mJumpClock.restart();
		}
		else
		{
			PlayerPartBody::setPosition(sf::Vector2f(0, -mJump));
		}
	}
	if(mAttached==true)
	{
		mPosition=sf::Vector2f(mFeet->getPosition().x, mFeet->getPosition().y-64);
	}
} 
void PlayerPartBody::draw()
{

}
void PlayerPartBody::setPosition(sf::Vector2f Vec)
{
	if(Vec.x>0)
	{
		mActiveAnimation=&mRightAnimation;
	}
	else if(Vec.x<0)
	{
		mActiveAnimation=&mLeftAnimation;
	}
	if(mAttached==true)
	{
		mPosition=sf::Vector2f(mFeet->getPosition().x, mFeet->getPosition().y-64);
	}
	else if(mAttached==false)
	{
		mPosition+=Vec;
	}
}
sf::Vector2f PlayerPartBody::getPosition()
{
	return mPosition;
} 
sf::Sprite PlayerPartBody::getSprite()
{
	mActiveAnimation->setPosition(mPosition);
	return mActiveAnimation->getSprite();
}
std::string PlayerPartBody::getId()
{
	return mId;
}
void PlayerPartBody::restartTimer()
{
	mActiveAnimation->restart();
}
bool PlayerPartBody::getAttached()
{
	return mAttached;
}
void PlayerPartBody::setAttached(bool b)
{
	mAttached=b;
}
void PlayerPartBody::jump()
{
	mJump=10;
	mJumpClock.restart();
}
void PlayerPartBody::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		if(mActiveAnimation==&mRightAnimation)
		{
			mActiveAnimation=&mRight;
		}
		else if(mActiveAnimation==&mLeftAnimation)
		{
			mActiveAnimation=&mLeft;
		}
	}
}
Unit* PlayerPartBody::getUnit()
{
	return mUnit;
}
void PlayerPartBody::jumpReset(){
	mJump=4;
}
void PlayerPartBody::forceMove(sf::Vector2f force){
	mPosition+=force;
}
void PlayerPartBody::restartAnimation(){
	mRightAnimation.restart();
	mLeftAnimation.restart();
}
void PlayerPartBody::setId(std::string Text){
	mId=Text;
}