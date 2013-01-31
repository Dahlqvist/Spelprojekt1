#include "PlayerPartFeet.h"
#include <iostream>

PlayerPartFeet::PlayerPartFeet():
	mLeftAnimation("StixLowerAniL", 200, 8),
	mRightAnimation("StixLowerAni", 200, 8),
	mLeft("StixLowerL", 200, 1),
	mRight("StixLower", 200, 1),
	mFeetExt("StixFeetExtend")
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
			mActiveAnimation=&mRightAnimation;
		}
		if(Vec.y<0){
			mActiveAnimation=&mLeftAnimation;
		}
	}
	else if(mAO==2)
	{
		if(Vec.y<0){
			mActiveAnimation=&mRightAnimation;
		}
		if(Vec.y>0){
			mActiveAnimation=&mLeftAnimation;
		}
	}
	else
	{
		if(Vec.x<0)
		{
			mActiveAnimation=&mRightAnimation;
		}
		if(Vec.x>0)
		{
			mActiveAnimation=&mLeftAnimation;
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
		
		mUnit=&mFeetExt;
		mFeetExt.setPosition(mPosition);
		mFeetExt.setOrigin(sf::Vector2f(mFeetExt.getSprite().getGlobalBounds().width/2, mFeetExt.getSprite().getGlobalBounds().width/2));
		mFeetExt.rotate(mRotation);
		mFeetExt.setPosition(mPosition+sf::Vector2f(32, 0));
		return mUnit->getSprite();
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
	}
	if(mAttached)
	{
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

void PlayerPartFeet::setAttachedWall(bool b, int w){
	if(b==true)
	{
		mAttachedWall=b;
		mAO=w;
		if(mAO==0)
		{
			mAUnit=&mRightWall;
		}
		if(mAO==1)
		{
			mAUnit=&mRoof;
			//Får lägga in -16 i y-led för att få rätt position mot "taket"
		}
		if(mAO==2)
		{
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