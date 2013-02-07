#include "PlayerPartFeet.h"
#include <iostream>

PlayerPartFeet::PlayerPartFeet():
	mLeftAnimation("StixLowerAniL", 200, 8),
	mRightAnimation("StixLowerAni", 200, 8),
	mLeft("StixLowerL", 200, 1),
	mRight("StixLower", 200, 1),
	mFeetExt(),
	mLeftMagnet("StixLowerLMagnet", 200, 1),
	mRightMagnet("StixLowerMagnet", 200, 1),
	mLeftAnimationMagnet("StixLowerAniLMagnet", 200, 8),
	mRightAnimationMagnet("StixLowerAniMagnet", 200, 8)
{
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(0, 0);
	mAttached=false;
	mAttachedWall=false;
	mAniTime=0;
	mAnimationTimer.restart();
	mUnit=0;
	mAUnit=0;
	mFuel=100;
	mAO=0;
}
void PlayerPartFeet::update()
{
	mActiveAnimation->update();
	if(mUnit!=0){
		mUnit->update();
	}
	if(mJump>0)
	{
		if(mJumpClock.getElapsedTime().asSeconds()>0.1)
		{
			mJump-=1.2;
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
	PlayerPartFeet::decideAnimation(Vec);
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
		else if(mAUnit!=0){
			if(mAUnit==&mRightWall || mAUnit==&mLeftWall){
				mPosition.y+=Vec.y;
			}
			else{
				mPosition.x+=Vec.x;
			}
		}
		//En massa kod för när den går på väggar och liknande =)
	}
}
void PlayerPartFeet::decideAnimation(sf::Vector2f Vec){
	if(mAttachedWall==false){
		if(Vec.x>0)
		{
			mActiveAnimation=&mRightAnimation;
		}
		if(Vec.x<0)
		{
			mActiveAnimation=&mLeftAnimation;
		}
	}
	else if(mAO==0)
	{
		if(Vec.y>0){
			mActiveAnimation=&mRightAnimationMagnet;
		}
		if(Vec.y<0){
			mActiveAnimation=&mLeftAnimationMagnet;
		}
	}
	else if(mAO==2)
	{
		if(Vec.y<0){
			mActiveAnimation=&mRightAnimationMagnet;
		}
		if(Vec.y>0){
			mActiveAnimation=&mLeftAnimationMagnet;
		}
	}
	else
	{
		if(Vec.x<0)
		{
			mActiveAnimation=&mRightAnimationMagnet;
		}
		if(Vec.x>0)
		{
			mActiveAnimation=&mLeftAnimationMagnet;
		}
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
	sf::Vector2f TempOrigin(0, 0);
	if(mAUnit!=0){
		if(mAO==0)
		{
			mRotation=90;
			TempOrigin=sf::Vector2f(32, 32);
		}
		if(mAO==1)
		{
			mRotation=180;
			TempOrigin=sf::Vector2f(64, 16);
		}
		if(mAO==2)
		{
			mRotation=-90;
			TempOrigin=sf::Vector2f(32, -32);
		}
	}
	else{
		mRotation=0;
	}

	if(mUnit==&mFeetExt)
	{
		mUnit->update();
		//mUnit=&mFeetExt;
		sf::Sprite Temp2=mUnit->getSprite();
		Temp2.setPosition(mFeetExt.getPosition());
		if(mRotation==90)
		{
			Temp2.setRotation(90);
			Temp2.setOrigin(0, 64);
		}
		if(mRotation==-90)
		{
			Temp2.setRotation(-90);
			Temp2.setOrigin(64, 0);
		}
		if(mRotation==180)
		{
			Temp2.setRotation(180);
			Temp2.setOrigin(64, 80);
		}
		//Temp2.setOrigin(TempOrigin);
		//Temp2.rotate(mRotation);
		//mFeetExt.setPosition(mPosition);
		//mFeetExt.setOrigin(sf::Vector2f(mFeetExt.getSprite().getGlobalBounds().width/2, mFeetExt.getSprite().getGlobalBounds().width/2));
		//mFeetExt.rotate(mRotation);
		//mFeetExt.setPosition(mPosition+sf::Vector2f(32, 0));
		return Temp2;
	}
	if(mRotation!=0){
		sf::Sprite Temp=mActiveAnimation->getSprite();
		Temp.setOrigin(TempOrigin);
		Temp.rotate(mRotation);
		return Temp;
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
	if(!mAttached)
	{
		mUnit=0;
		mFeetExt.setFacingRight(true, true);
		if(mAO==1){
			mPosition+=sf::Vector2f(0, -16);
		}
	}
	if(mAttached)
	{
		mFeetExt.setPosition(mPosition+sf::Vector2f(0, -32));
		if(mAttachedWall==false && (mActiveAnimation==&mRight || mActiveAnimation==&mRightAnimation))
		{
			mFeetExt.setFacingRight(true, false);
		}
		else if(mAttachedWall==false && (mActiveAnimation==&mLeft || mActiveAnimation==&mLeftAnimation))
		{
			mFeetExt.setFacingRight(false, false);
		}
		else if(mActiveAnimation==&mRightMagnet || mActiveAnimation==&mRightAnimationMagnet)
		{
			mFeetExt.setFacingRight(true, true);
		}
		else if(mActiveAnimation==&mLeftMagnet || mActiveAnimation==&mLeftAnimationMagnet)
		{
			mFeetExt.setFacingRight(false, true);
		}
		mFeetExt.update();
		mUnit=&mFeetExt;
	}
}
void PlayerPartFeet::jump()
{
	mJump=10;
	mJumpClock.restart();
}
void PlayerPartFeet::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		if(mAttachedWall==false)
		{
			if(mActiveAnimation==&mRightAnimation || mActiveAnimation==&mLeftMagnet) 
			{
				mActiveAnimation=&mRight;
			}
			else if(mActiveAnimation==&mLeftAnimation || mActiveAnimation==&mRightMagnet)
			{
				mActiveAnimation=&mLeft;
			}
		}
		else if(mAttachedWall==true)
		{
			if(mActiveAnimation==&mRightAnimationMagnet || mActiveAnimation==&mRight){
				mActiveAnimation=&mRightMagnet;
			}
			else if(mActiveAnimation==&mLeftAnimationMagnet || mActiveAnimation==&mLeft){
				mActiveAnimation=&mLeftMagnet;
			}
		}
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
		PlayerPartFeet::setPosition(sf::Vector2f(0, -6));
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
	mJump=4;
}

void PlayerPartFeet::setAttachedWall(bool b, int w){
	if(b==true)
	{
		mAttachedWall=b;
		mAO=w;
		if(mAO==0)
		{
			mAUnit=&mRightWall;
			mJump=0;
		}
		if(mAO==1)
		{
			mAUnit=&mRoof;
			mJump=0;
			mPosition+=sf::Vector2f(0, -16);
			//Får lägga in -16 i y-led för att få rätt position mot "taket"
		}
		if(mAO==2)
		{
			mJump=0;
			mAUnit=&mLeftWall;
		}
	}
	else
	{
		mAO=w;
		mAttachedWall=false;
		mAUnit=0;
	}
}
bool PlayerPartFeet::getAttachedWall(){
	return mAttachedWall;
}
int PlayerPartFeet::getWall(){
	return mAO;
}
void PlayerPartFeet::forceMove(sf::Vector2f force){
	mPosition+=force;
}
void PlayerPartFeet::restartAnimation(){
	mRightAnimation.restart();
	mLeftAnimation.restart();
}