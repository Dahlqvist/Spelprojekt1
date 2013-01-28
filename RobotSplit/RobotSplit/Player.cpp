#include "Player.h"
#include <iostream>
#include <math.h>

Player::Player(sf::Vector2f Position):
mFeet(), mBody(&mFeet), mHead(&mBody)
{
	mParts.push_back(&mFeet);
	mParts.push_back(&mBody);
	mParts.push_back(&mHead);
	mFeet.restartTimer();
	mBody.restartTimer();
	mHead.restartTimer();
	mState=0;
	mSpeed=2;
	mHeadless=false;
	mTogether=true;
	mFeetAttached=false;
	mSprintTimer.restart();
	mFeet.setPosition(Position);
}
void Player::draw(sf::RenderWindow& Window)
{
	for(unsigned int i=0; i<mParts.size(); i++)
	{
		if(mParts[i]->getObject()!=0)
		{
			Window.draw(mParts[i]->getObject()->getSprite());
		}
	}
	Window.draw(mFeet.getSprite());
	Window.draw(mHead.getSprite());
	Window.draw(mBody.getSprite());
	//Window.draw(mBody.getObject()->getSprite());
}
void Player::update()
{
	for(unsigned int i=0; i < mParts.size(); i++)
	{
		if(mParts[i]->getPosition().y+mParts[i]->getSprite().getGlobalBounds().height<600)
		{
			if(i!=2)
			{
				mParts[i]->setPosition(sf::Vector2f(0, 3));
			}
		}
		mParts[i]->update();
	}
	//if(mJump>0){
	//	if(mJumpClock.getElapsedTime().asSeconds()>0.15){
	//		mJump-=1;
	//		mJumpClock.restart();
	//	}
	//	else{
	//		Player::move(sf::Vector2f(0, -mJump));
	//		/*for(unsigned int i=0; i < mParts.size(); i++){
	//			mParts[i]->setPosition(sf::Vector2f(0, -mJump));
	//		}*/
	//	}
	//}
}
void Player::move(sf::Vector2f Vec)
{
	Vec.x*=mSpeed;
	Vec.y*=mSpeed;
	if(mTogether==true)
	{
		for(unsigned int i=0; i < mParts.size(); i++)
		{
			if(mParts[i]!=&mHead || mHeadless!=true)
			{
				mParts[i]->setPosition(Vec);
			}
		}
	}
	else if(mBodyActive)
	{
		mBody.setPosition(Vec);
		if(mHeadless==false)
		{
			mHead.setPosition(Vec);
		}
	}
	else
	{
		mFeet.setPosition(Vec);
	}
}
//void Player::changeState(){
//	/*if(mTogether==false)
//	{
//		mState++;
//		switch(mState%2)
//		{
//		case 0:
//			mPartVector[0]->setActive(true);
//			mPartVector[1]->setActive(false);
//		break;
//		case 1:
//			mPartVector[0]->setActive(false);
//			mPartVector[1]->setActive(true);
//		break;
//		}
//	}
//	else if(mTogether==true){
//		Player::move(sf::Vector2f(0, 0));
//	}
//	if(mHeadless==false){
//		mPartVector[2]->setActive(mPartVector[1]->getActive());
//	}*/
//	//if(f==0){
//	//	mState++;
//	//	switch(mState%2){
//	//	case 0:
//	//		mPartVector[1]->setActive(true);
//	//		mPartVector[2]->setActive(false);
//	//	break;
//	//	case 1:
//	//		mPartVector[1]->setActive(false);
//	//		mPartVector[2]->setActive(true);
//	//	break;
//	//	}
//	//	/*switch(mState%5){
//	//	case 0:
//	//		mPartVector[0]->setActive(true);
//	//		mPartVector[1]->setActive(true);
//	//		mPartVector[2]->setActive(false);
//	//	break;
//	//	case 1:
//	//		mPartVector[0]->setActive(false);
//	//		mPartVector[1]->setActive(false);
//	//		mPartVector[2]->setActive(true);
//	//	break;
//	//	case 2:
//	//		mPartVector[0]->setActive(true);
//	//		mPartVector[1]->setActive(true);
//	//		mPartVector[2]->setActive(true);
//	//	break;
//	//	case 3:
//	//		mPartVector[0]->setActive(false);
//	//		mPartVector[1]->setActive(true);
//	//		mPartVector[2]->setActive(true);
//	//	break;
//	//	case 4:
//	//		mPartVector[0]->setActive(false);
//	//		mPartVector[1]->setActive(true);
//	//		mPartVector[2]->setActive(false);
//	//	break;
//	//	case 5:
//	//		mPartVector[0]->setActive(true);
//	//		mPartVector[1]->setActive(false);
//	//		mPartVector[2]->setActive(false);
//	//	break;
//	//	}*/
//	//}
//	//else if(f==1){
//	//	mPartVector[1]->setActive(true);
//	//	mPartVector[2]->setActive(true);
//	//}
//	//if(mHeadless==false){
//	//	mPartVector[0]->setActive(mPartVector[1]->getActive());
//	//}
//}
//int Player::getState(){
//	return mState;
//}
bool Player::getTogether()
{
	return mTogether;
}
void Player::setTogether(bool b)
{
	if(b==false)
	{
		mBodyActive=true;
		mBody.setAttached(false);
		mTogether=b;
	}
	else if((mFeet.getPosition().x-mBody.getPosition().x)*(mFeet.getPosition().x-mBody.getPosition().x) +
		(mFeet.getPosition().y-mBody.getPosition().y)*(mFeet.getPosition().y-mBody.getPosition().y) < 70*70 
		&& mFeet.getAttached()==false)
	{
		mBodyActive=false;
		mBody.setAttached(true);
		mTogether=b;
		Player::move(sf::Vector2f(0, 0));
	}
	/*if(b==false)
	{
	mState=1;
	mTogether=b;
	mPartVector[1]->setAttached(false);
	Player::changeState();
	}
	if((mPartVector[0]->getPosition().x-mPartVector[1]->getPosition().x)*(mPartVector[0]->getPosition().x-mPartVector[1]->getPosition().x)+
	(mPartVector[0]->getPosition().y-mPartVector[1]->getPosition().y)*(mPartVector[0]->getPosition().y-mPartVector[1]->getPosition().y)< 70*70
	&& b==true && mPartVector[0]->getMovable()==true)
	{
	mTogether=b;
	mPartVector[1]->setAttached(true);
	Player::changeState();
	}	*/
}
void Player::jump()
{
	if(mTogether==true)
	{
		mFeet.jump();
		mBody.jump();
	}
	else if(mBodyActive)
	{
		mBody.jump();
	}
	else
	{
		mFeet.jump();
	}
	/*if(mJumpTimer.getElapsedTime().asSeconds() > 2){
	if(mTogether==true){
	for(unsigned int i=0; i < mPartVector.size(); i++){
	mPartVector[i]->jump();
	}
	}
	else{
	for(unsigned int i=0; i < mPartVector.size(); i++){
	if(mPartVector[i]->getActive()==true){
	mPartVector[i]->jump();
	}
	}
	}
	mJumpTimer.restart();
	}*/
}
//void Player::resetJump(){
//	if(mTogether==true){
//		for(unsigned int i=0; i < mPartVector.size(); i++){
//			mPartVector[i]->resetJump();
//		}
//	}
//	else{
//		for(unsigned int i=0; i < mPartVector.size(); i++){
//			if(mPartVector[i]->getActive()==true){
//				mPartVector[i]->resetJump();
//			}
//		}
//	}
//}
//int Player::getHeight(){
//	return 0;
//}

sf::FloatRect Player::getRect()
{
	sf::FloatRect Rect(mFeet.getSprite().getGlobalBounds());
	return Rect;
}
void Player::setBodyActive(bool b)
{
	mBodyActive=b;
}
bool Player::getBodyActive()
{
	return mBodyActive;
}
void Player::resetAnimations()
{
	for(unsigned int i=0; i < mParts.size(); i++)
	{
		mParts[i]->resetAnimation();
	}
}

void Player::shootHead(sf::Vector2f Vec)
{
	if(Vec==sf::Vector2f(0, 0))
	{
		mHead.setAttached(true);
		mHead.setShootVector(Vec);
		mHeadless=false;
	}
	else if(mHead.getAttached()==true)
	{
		mHeadless=true;
		float k=(mHead.getPosition().y-Vec.y)/(mHead.getPosition().x-Vec.x);
		float l=sqrt((mHead.getPosition().y-Vec.y)*(mHead.getPosition().y-Vec.y) + (mHead.getPosition().x-Vec.x)*(mHead.getPosition().x-Vec.x));
		float q=sqrt(1+k*k);
		int xValue;
		if(Vec.x-mHead.getPosition().x < 0)
		{
			xValue=-1;
			k*=-1;
		}
		else
		{
			xValue=1;
		}
		sf::Vector2f MathVec(xValue/q, k/q);
		mHead.setAttached(false);
		mHead.setShootVector(MathVec);
		float w=sqrt((xValue/q)*(xValue/q)+(k/q)*(k/q));
		std::cout << sin((k/q)/w) << std::endl;
	}
}
void Player::setHeadless(bool b)
{
	mHeadless=b;
}
bool Player::getHeadless()
{
	return mHeadless;
}
std::vector<sf::Sprite*> Player::getCollisionSprite()
{
	std::vector<sf::Sprite*> Parts;
	for(unsigned int i=0; i < mParts.size(); i++)
	{
		sf::Sprite* Temp=new sf::Sprite(mParts[i]->getSprite());
		Parts.push_back(Temp);
	}
	return Parts;
}
void Player::setAttachFeet(bool b)
{
	if(!mFeet.getSprite().getGlobalBounds().intersects(mBody.getSprite().getGlobalBounds()))
	{
		mFeetAttached=b;
		if(b==true)
		{
			mFeet.setAttached(true);
		}
		if(b==false)
		{
			mFeet.setAttached(false);
		}
	}
}
bool Player::getAttachFeet()
{
	return mFeetAttached;
}
void Player::sprint()
{
	
}
void Player::forceMove(int part, sf::Vector2f Vec)
{
	if(part==0)
	{
		mFeet.setPosition(Vec);
	}
	else if(part==1)
	{
		mBody.setPosition(Vec);
	}
	else if(part==2)
	{
		mHead.setPosition(Vec);
	}
	else
	{
		for(unsigned int i=0; i < mParts.size(); i++)
		{
			mParts[i]->setPosition(Vec);
		}

	}
}