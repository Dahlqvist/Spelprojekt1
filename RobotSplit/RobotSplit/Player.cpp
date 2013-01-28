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
	mSpeed=2;
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
	if(mTogether==true)
	{
		mSpeed=4;
	}
}
void Player::activateFeetRockets(){
	mFeet.activateRocketBoots();
}
void Player::reFuel(float fuel){
	mFeet.reFuel(fuel);
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