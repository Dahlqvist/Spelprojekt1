#include "PlayerPartBody.h"
#include <iostream>

PlayerPartBody::PlayerPartBody(PlayerPartFeet* Feet):
	mFeet(Feet),
	mLeftAnimation("StixUpperAniL", 200, 8),
	mRightAnimation("StixUpperAni", 200, 8),
	mLeft("StixUpperL", 200, 1),
	mRight("StixUpper", 200, 1),
	mWinningAni("WinningBody", 100, 6),
	mWalkingRight("StixUpperWalkPart", 100, 8),
	mWalkingLeft("StixUpperWalkPartL", 100, 8),
	mJumpingRight("StixUpperJump", 100, 8),
	mJumpingLeft("StixUpperJumpL", 100, 8),
	mLeftPart("StixUpperIdlePartL", 100, 1),
	mRightPart("StixUpperIdlePart", 100, 1),
	mSplitting("StixUpperSplit", 100, 8),
	mSplittingLeft("StixUpperSplitL", 100, 8)
{
	mId="PlayerPartBody";
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(100, 100);
	mAttached=true;
	mAniTime=0;
	mAnimationTimer.restart();
	mUnit=0;
	mCounter=0;
}
void PlayerPartBody::update()
{
	mActiveAnimation->update();
	if(mJump>0)
	{
		mCounter++;
		if(mCounter>=Eric::getTimer())
		{
			mJump-=Eric::getJumpchange();
			mCounter=0;
			PlayerPartBody::setPosition(sf::Vector2f(0, -mJump));
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
	else
	{
		mPosition+=sf::Vector2f(0, Eric::getGravity());
	}
} 
void PlayerPartBody::draw()
{

}
void PlayerPartBody::setPosition(sf::Vector2f Vec)
{
	PlayerPartBody::decideAnimation(Vec);
	if(mAttached==true && mActiveAnimation->getCurrentFrame()!=mFeet->getFrame())
	{
		mActiveAnimation->restart();
		mFeet->restartAnimation();
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
void PlayerPartBody::decideAnimation(sf::Vector2f Vec)
{
	if(mAnimationTimer.getElapsedTime().asSeconds()>mAniTime)
		{
		if(Vec.x>0 && mAttached==true)
		{
			mActiveAnimation=&mRightAnimation;
		}
		else if(Vec.x<0 && mAttached==true)
		{
			mActiveAnimation=&mLeftAnimation;
		}
		else if(Vec.x>0 && mAttached==false)
		{
			mActiveAnimation=&mWalkingRight;
		}
		else if(Vec.x<0 && mAttached==false)
		{
			mActiveAnimation=&mWalkingLeft;
		}
	}
	else if(mActiveAnimation==&mJumpingRight || mActiveAnimation==&mJumpingLeft)
	{
		if(Vec.x>0)
		{
			mActiveAnimation=&mJumpingRight;
		}
		else if(Vec.x<0)
		{
			mActiveAnimation=&mJumpingLeft;
		}
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
	if(b==false)
	{
		mSplitting.restart();
		mSplittingLeft.restart();
		mAnimationTimer.restart();
		if(mActiveAnimation==&mRightAnimation || mActiveAnimation==&mRight)
		{
			mActiveAnimation=&mSplitting;
			mAniTime=0.8;
		}
		else if(mActiveAnimation==&mLeftAnimation || mActiveAnimation==&mLeft)
		{
			mActiveAnimation=&mSplittingLeft;
			mAniTime=0.8;
		}
	}
}
void PlayerPartBody::jump(float jump)
{
	mCounter=0;
	mJump=jump;
	mJumpClock.restart();
	if(mAttached==false){
		mJumpingRight.restart();
		mJumpingLeft.restart();
		mAnimationTimer.restart();
		if(mActiveAnimation==&mRightPart || mActiveAnimation==&mWalkingRight || mActiveAnimation==&mJumpingRight){
			mActiveAnimation=&mJumpingRight;
		}
		else
		{
			mActiveAnimation=&mJumpingLeft;
		}
		mAniTime=0.8;
	}
}
void PlayerPartBody::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		if(mActiveAnimation==&mRightAnimation || mActiveAnimation==&mWinningAni)
		{
			mActiveAnimation=&mRight;
		}
		else if(mActiveAnimation==&mLeftAnimation)
		{
			mActiveAnimation=&mLeft;
		}
		else if(mActiveAnimation==&mWalkingLeft || mActiveAnimation==&mJumpingLeft || mActiveAnimation==&mSplittingLeft)
		{
			mActiveAnimation=&mLeftPart;
		}
		else if(mActiveAnimation==&mWalkingRight || mActiveAnimation==&mJumpingRight || mActiveAnimation==&mSplitting)
		{
			mActiveAnimation=&mRightPart;
		}
	}
}
Unit* PlayerPartBody::getUnit()
{
	return mUnit;
}
void PlayerPartBody::jumpReset(){
	mJump=Eric::getGravity()-Eric::getJumpchange();
}
void PlayerPartBody::forceMove(sf::Vector2f force){
	mPosition+=force;
}
void PlayerPartBody::restartAnimation(){
	mRightAnimation.restart();
	mLeftAnimation.restart();
}
void PlayerPartBody::winning(){
	mWinningAni.restart();
	mAnimationTimer.restart();
	mAniTime=2;
	mActiveAnimation=&mWinningAni;
}