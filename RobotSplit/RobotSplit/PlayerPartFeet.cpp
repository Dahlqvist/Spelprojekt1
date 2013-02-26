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
	mRightAnimationMagnet("StixLowerAniMagnet", 200, 8),
	mJumpAni("StixFeetJumpAni", 100, 8),
	mJumpAniLeft("StixFeetJumpAniL", 100, 8),
	mWinningAni("WinningFeet", 100, 6)
{
	mId="PlayerPartFeet";
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
		if(mJumpClock.getElapsedTime().asSeconds()>Eric::getTimer())
		{
			mJump-=Eric::getJumpchange();
			mJumpClock.restart();
			PlayerPartFeet::setPosition(sf::Vector2f(0, -mJump));
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
	if(mAnimationTimer.getElapsedTime().asSeconds()>mAniTime)
	{
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
	else if(mActiveAnimation==&mJumpAni || mActiveAnimation==&mJumpAniLeft)
	{
		if(Vec.x>0)
		{
			mActiveAnimation=&mJumpAni;
		}
		else if(Vec.x<0)
		{
			mActiveAnimation=&mJumpAniLeft;
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
		Sound::playSound("Extend");
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
void PlayerPartFeet::jump(float jump)
{
	mJump=jump;
	mJumpClock.restart();
	mJumpAni.restart();
	mJumpAniLeft.restart();
	mAnimationTimer.restart();
	if(mActiveAnimation==&mRight || mActiveAnimation==&mRightAnimation || mActiveAnimation==&mJumpAni){
		mActiveAnimation=&mJumpAni;
	}
	else
	{
		mActiveAnimation=&mJumpAniLeft;
	}
	mAniTime=0.8;
}
void PlayerPartFeet::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		if(mAttachedWall==false)
		{
			if(mActiveAnimation==&mRightAnimation || mActiveAnimation==&mLeftMagnet || mActiveAnimation==&mJumpAni || mActiveAnimation==&mWinningAni) 
			{
				mActiveAnimation=&mRight;
			}
			else if(mActiveAnimation==&mLeftAnimation || mActiveAnimation==&mRightMagnet || mActiveAnimation==&mJumpAniLeft)
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
	if(mUnit==&mRocketFuel){
		mUnit=0;
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
		mUnit=&mRocketFuel;
		mJump=0;
		mUnit->setPosition(mPosition+sf::Vector2f(16, 32));
		PlayerPartFeet::setPosition(sf::Vector2f(0, -Eric::getRocketboost()));
		mFuel--;
		mJump=Eric::getGravity();
	}
}
void PlayerPartFeet::reFuel(float fuel)
{
		mFuel=fuel;
}
void PlayerPartFeet::jumpReset()
{
	mJump=Eric::getGravity();
}

void PlayerPartFeet::setAttachedWall(bool b, int w){
	if(b==true)
	{
		mAniTime=0;
		PlayerPartFeet::resetAnimation();
		mAttachedWall=b;
		mAO=w;
		Sound::playSound("MagnetStuckWall");
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
		Sound::playSound("MagnetLetGo");
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
	//if(force.y!=0)
	//{
	//	mJump=Eric::getGravity();
	//}
}
void PlayerPartFeet::restartAnimation(){
	mRightAnimation.restart();
	mLeftAnimation.restart();
}
void PlayerPartFeet::winning(){
	mWinningAni.restart();
	mAnimationTimer.restart();
	mAniTime=2;
	mActiveAnimation=&mWinningAni;
}
int PlayerPartFeet::getFrame()
{
	return mActiveAnimation->getCurrentFrame();
}