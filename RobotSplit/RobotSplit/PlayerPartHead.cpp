#include "PlayerPartHead.h"
#include <iostream>
#include "UnitManager.h"

PlayerPartHead::PlayerPartHead(PlayerPart* Body):
mBody(Body),
	mLeftAnimation("StixShootAni", 200, 8),
	mRightAnimation("StixShootAni", 200, 8),
	mLeft("StixUpper", 200, 1),
	mRight("StixBrain", 200, 1),
	mMagnet("StixBrainLowered")
{
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(100, 100);
	mAttached=true;
	mMagnetCollided=true;
	mAniTime=0;
	mAnimationTimer.restart();
	mUnit=0;
}
void PlayerPartHead::update()
{
	//mMagnet.setOrigin();
	mActiveAnimation->update();
	if(mUnit!=0){
		mUnit->update();
	}
	if(mAttached==true)
	{
		mPosition=mBody->getPosition()+sf::Vector2f(26, 26);
	}
	if(mShootVector!=sf::Vector2f(0, 0))
	{
		PlayerPartHead::setPosition(mShootVector);
		//mMagnetCollided=true;
	}
} 
void PlayerPartHead::draw()
{
}
void PlayerPartHead::setPosition(sf::Vector2f Vec)
{
	if(mAttached==true)
	{
		mPosition=mBody->getPosition();
	}
	else
	{
		mPosition+=Vec;
	}
}
sf::Vector2f PlayerPartHead::getPosition()
{
	return mPosition;
} 
sf::Sprite PlayerPartHead::getSprite()
{
	mActiveAnimation->setPosition(sf::Vector2f(mPosition.x, mPosition.y));
	//sf::Sprite test(mActiveAnimation->getSprite());
	//test.scale(0.5, 0.5);
	return mActiveAnimation->getSprite();
}
std::string PlayerPartHead::getId()
{
	return mId;
}
void PlayerPartHead::restartTimer()
{
	mActiveAnimation->restart();
}
bool PlayerPartHead::getAttached()
{
	return mAttached;
}
void PlayerPartHead::setAttached(bool b)
{
	if (b==false){
		//mUnit=&mFeetExt;
	}
	else{
		mUnit=0;
	}
	mAttached=b;
}
void PlayerPartHead::jump()
{
	mJump=0;
}
void PlayerPartHead::setShootVector(sf::Vector2f Vec)
{
	float mSpeed=5;
	mShootVector=sf::Vector2f(Vec.x*mSpeed, Vec.y*mSpeed);
}
void PlayerPartHead::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		mActiveAnimation=&mRight;
	}
}
Unit* PlayerPartHead::getUnit()
{
	return mUnit;
}
void PlayerPartHead::forceMove(sf::Vector2f force){
	mPosition+=force;
	mShootVector=sf::Vector2f(0, 0);
	if(mAttached==false && mMagnetCollided==false){
		mMagnet.restartAnimations();
		mMagnet.setSolid(false);
		mUnit=&mMagnet;
		mUnit->setPosition(mPosition+sf::Vector2f(-mUnit->getSprite().getGlobalBounds().width/2+mActiveAnimation->getSprite().getGlobalBounds().width/2, 0));
	}
	Sound::playSound("HeadStuck");
	mMagnetCollided=true;
}
void PlayerPartHead::setMagnetSolid(bool b){
	mMagnet.setSolid(b);
}
void PlayerPartHead::setMagnetCollided(bool b)
{
	mMagnetCollided=b;
}
void PlayerPartHead::winning(){

}