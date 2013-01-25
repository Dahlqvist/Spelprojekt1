#include "PlayerPartHead.h"

PlayerPartHead::PlayerPartHead(PlayerPart* Body):
mBody(Body),
	mLeftAnimation("StixShootAni", 200, 8),
	mRightAnimation("StixShootAni", 200, 8),
	mLeft("StixUpper", 200, 1),
	mRight("Tile6", 200, 1)
{
	mActiveAnimation=&mRight;
	mPosition=sf::Vector2f(100, 100);
	mAttached=true;
	mAniTime=0;
	mAnimationTimer.restart();
	mObject=0;
}
void PlayerPartHead::update()
{
	mActiveAnimation->update();
	if(mAttached==true)
	{
		mPosition=mBody->getPosition();
	}
	if(mShootVector!=sf::Vector2f(0, 0))
	{
		PlayerPartHead::setPosition(mShootVector);
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
	mActiveAnimation->setPosition(sf::Vector2f(mPosition.x+16, mPosition.y+16));
	sf::Sprite test(mActiveAnimation->getSprite());
	test.scale(0.5, 0.5);
	return test;
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
	mAttached=b;
}
void PlayerPartHead::jump()
{
	mJump=0;
}
void PlayerPartHead::setShootVector(sf::Vector2f Vec)
{
	float mSpeed=2;
	mShootVector=sf::Vector2f(Vec.x*mSpeed, Vec.y*mSpeed);
}
void PlayerPartHead::resetAnimation()
{
	if(mAnimationTimer.getElapsedTime().asSeconds() > mAniTime)
	{
		mActiveAnimation=&mRight;
	}
}
GameObject* PlayerPartHead::getObject()
{
	return mObject;
}