#include "Player.h"
#include "TextureManager.h"
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
	mTexture.loadFromFile("Texture/Stix/stix.png");
	mSprite.setTexture(mTexture);
	mDash=0;
	mFacingRight=true;
}
void Player::draw(sf::RenderWindow& Window)
{
	/*if(mTogether==true)
	{
		mSprite.setPosition(mFeet.getPosition() + sf::Vector2f(0, -64));
		Window.draw(mSprite);
	}
	else
	{*/
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
	//}
	//Window.draw(mBody.getObject()->getSprite());
}
void Player::update()
{
	for(unsigned int i=0; i < mParts.size(); i++)
	{
		if(mParts[i]->getPosition().y+mParts[i]->getSprite().getGlobalBounds().height<600)
		{
			if(i!=2 && mParts[i]->getAttached()==false)
			{
				mParts[i]->setPosition(sf::Vector2f(0, 3));
			}
		}
		mParts[i]->update();
	}
	if(mDash>0){
		if(mFacingRight==true)
		{
			mFeet.setPosition(sf::Vector2f(mSpeed*2, 0));
			mDash--;
		}
		else
		{
			mFeet.setPosition(sf::Vector2f(-mSpeed*2, 0));
			mDash--;
		}
	}
	else{
		mDashing=false;
	}
}
void Player::move(sf::Vector2f Vec)
{
	if(mDashing==false)
	{
		if(Vec.x>0){
			mFacingRight=true;
		}
		if(Vec.x<0){
			mFacingRight=false;
		}
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
	if(mTogether==true){
		mSprite.setPosition(mFeet.getPosition() + sf::Vector2f(0, -64));
		sf::Sprite* Temp1=new sf::Sprite(mSprite);
		Parts.push_back(Temp1);
		if(mHeadless==true){
			sf::Sprite* Temp2=new sf::Sprite(mHead.getSprite());
			Parts.push_back(Temp2);
		}
	}
	else{
		for(unsigned int i=0; i < mParts.size(); i++)
		{
			sf::Sprite* Temp=new sf::Sprite(mParts[i]->getSprite());
			Parts.push_back(Temp);
		}
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
void Player::dash()
{
	if(mTogether==true)
	{
		mDashing=true;
		mDash=20;
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
		mHead.setShootVector(sf::Vector2f(0, 0));
	}
	else
	{
		mBody.setPosition(Vec);
		mFeet.setPosition(Vec);
		/*for(unsigned int i=0; i < mParts.size(); i++)
		{
			mParts[i]->setPosition(Vec);
		}*/
	}
}