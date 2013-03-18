#include "Player.h"
#include "TextureManager.h"
#include <iostream>
#include <math.h>
#include "UnitManager.h"
#include "Sound.h"
#include "Eric.h"
#include "RocketFuel.h"
#include "Timer.h"

Player::Player(sf::Vector2f Position):
mFeet(), mBody(&mFeet), mHead(&mBody)
{
	mParts.push_back(&mFeet);
	mParts.push_back(&mBody);
	mParts.push_back(&mHead);
	mFeet.restartTimer();
	mBody.restartTimer();
	mHead.restartTimer();
	//mSpeed=2;
	mHeadless=false;
	mTogether=true;
	mFeetAttached=false;
	mSprintTimer.restart();
	mFeet.setPosition(Position);
	mBody.update();
	mHead.update();
	mDash=0;
	mFacingRight=true;
	mJumpTemp.restart();
	mJumpTemp2.restart();
	mMagnetTimer.restart();
	magnetSlot=2;
	mHeadAttachedFeet=false;
	mBodyStandingFeet=false;
	TempPart= new PlayerPartFeet();
	TempPart->setId("InteKollision");
	mParts.push_back(TempPart);
	mParts.push_back(TempPart);
	mParts.push_back(TempPart);
	lastKey=0;
	thisKey=0;
	mKeyTimer.restart();
	mClock.restart();
	mClockStart=false;
	mStartPosition=Position;
	mWinning=false;
	mCourser=new Courser;
	Player::initSprites();
	mRocketing=false;
	mDying=false;
	mDieTimer.restart();
}
void Player::initSprites()
{
	TempFeet=new sf::Sprite;
	TempBody=new sf::Sprite;
	TempHead=new sf::Sprite;
	TempMagnet=new sf::Sprite;
	TempExtension=new sf::Sprite;
	TempWhole=new sf::Sprite;
	mRocketFuel=TextureManager::getSprite("StixFuelbar");
	mRocketFuelBar=TextureManager::getSprite("StixFuelbarEmpty");
	mRocketFuel.setOrigin(mRocketFuel.getGlobalBounds().width, mRocketFuel.getGlobalBounds().height);
	mRocketFuel.setRotation(180);
	temporary=mRocketFuel.getGlobalBounds().height;
}
Player::~Player()
{
	delete mCourser;
	delete TempFeet;
	delete TempBody;
	delete TempHead;
	delete TempMagnet;
	delete TempExtension;
	delete TempWhole;
	delete TempPart;
}

//Kontroller och funktioner för Player
void Player::draw(sf::RenderWindow& Window, bool front)
{
	if(front==false)
	{
		if(mBodyActive==true || mTogether==true)
		{
			mLights.setSprite(mTogether, mBodyActive, mFeet.getAttachedWall(), mFeet.getWall(), mBody.getPosition());
		}
		else
		{
			mLights.setSprite(mTogether, mBodyActive, mFeet.getAttachedWall(), mFeet.getWall(), mFeet.getPosition());
		}
		Window.draw(*mLights.getSprite());

		if(mFeet.getUnit()!=0 && mFeet.getUnit()->getSprite().getTexture()!=mFeet.getSprite().getTexture() && mFeet.getFuel()>0)
		{
			Window.draw(mFeet.getUnit()->getSprite());
		}

		if(mHead.getAttached()==false)
		{
			Window.draw(mHead.getSprite());
		}
		if(mHead.getUnit()!=0)
		{
			Window.draw(mHead.getUnit()->getSprite());
		}
		Window.draw(mFeet.getSprite());
		Window.draw(mBody.getSprite());
	}
	else
	{
//		sf::Vector2f mVec((float)sf::Mouse::getPosition(Window).x, (float)sf::Mouse::getPosition(Window).y);
		sf::Vector2f mVec(Window.convertCoords(sf::Mouse::getPosition(Window)));
		Window.draw(*mCourser->getSprite(mVec));

		if(mFeet.getUnit()!=0 && mFeet.getAttached()==false)
		{
			mRocketFuelBar.setPosition(mFeet.getPosition()+sf::Vector2f(-12, -32));
			Window.draw(mRocketFuelBar);
			mRocketFuel.setPosition(mRocketFuelBar.getPosition()+sf::Vector2f(1, 1));
			mRocketFuel.setTextureRect(sf::IntRect(mRocketFuel.getTextureRect().left, mRocketFuel.getTextureRect().top, mRocketFuel.getTextureRect().width, (int)temporary*(mFeet.getFuel()/Eric::getFueltank())));
			Window.draw(mRocketFuel);
		}
	}
	//Window.draw(*TempExtension);
	//Window.draw(TempPart->getSprite());
}
void Player::update()
{
	//mRocketing=false;
	if(mDying==true)
	{
		if(mBodyDied==true)
		{
			if(mBody.getFrame()==7)
			{
				Player::restartPlayer();
			}
		}
		else
		{
			if(mFeet.getFrame()==7)
			{
				Player::restartPlayer();
			}
		}
	}
	//Sound::playSound("Lava");
	if(mKeyTimer.getElapsedTime().asSeconds()>0.03)
	{
		lastKey=-1;
		Sound::stopSound("Move");
		mRocketing=false;
	}
	if(mDash>0)
	{
		if(mFacingRight==true)
		{
			mFeet.setPosition(sf::Vector2f(Eric::getSpeed()*2, 0));
			mBody.setPosition(sf::Vector2f(Eric::getSpeed()*2, 0));
			mDash--;
		}
		else
		{
			mFeet.setPosition(sf::Vector2f(-Eric::getSpeed()*2, 0));
			mBody.setPosition(sf::Vector2f(-Eric::getSpeed()*2, 0));
			mDash--;
		}
	}
	else{
		mDashing=false;
	}
	for(unsigned int i=0; i < mParts.size(); i++)
	{
		//if(i<3){
			mParts[i]->update();
		//}
	}
	mBodyStandingFeet=false;
	if(mHeadless==true && mHead.getUnit()==0)
	{
		TempPart->setPosition((mHead.getPosition()-TempPart->getPosition())+sf::Vector2f(-24, 32));
		if(!UnitManager::isCollidedSide(3, 2) && !UnitManager::isCollidedSide(3, 3) && !UnitManager::isCollidedSide(3, 4) && !UnitManager::isCollidedSide(3, 1))
		{
			mHead.setMagnetCollided(false);
		}
		else{
			mHead.setMagnetCollided(true);
		}
	}
	if(mTogether==false && mFeet.getAttached()==true)
	{
		Player::checkCollisionExt();
	}
	if(mHeadless==true && mHead.getUnit()!=0 && mTogether==false)
	{
		Player::checkCollisionMagnet();
	}
	if(mFeet.getAttachedWall()==true)
	{
		if(mFeet.getWall()==0 && !UnitManager::isCollidedSide(0, 4))
		{
			mFeet.forceMove(sf::Vector2f(0, 5));
			mFeet.setAttachedWall(false);
			mFeet.jumpReset();
		}
		if(mFeet.getWall()==1 && !UnitManager::isCollidedSide(0, 1))
		{
			mFeet.forceMove(sf::Vector2f(0, 1));
			mFeet.setAttachedWall(false);
			mFeet.jumpReset();
		}
		if(mFeet.getWall()==2 && !UnitManager::isCollidedSide(0, 3))
		{
			mFeet.forceMove(sf::Vector2f(0, 5));
			mFeet.setAttachedWall(false);
			mFeet.jumpReset();
		}
	}
}
void Player::move(sf::Vector2f Vec)
{
	if(mDashing==false && mDying==false)
	{
		if(Vec.x>0)
		{
			mFacingRight=true;
		}
		if(Vec.x<0)
		{
			mFacingRight=false;
		}
		Vec.x*=Eric::getSpeed();
		Vec.y*=Eric::getSpeed();
		if(mTogether==true)
		{
			//for(unsigned int i=0; i < mParts.size(); i++)
			//{
			//	if(mParts[i]!=&mHead || mHeadless!=true)
			//	{
			//		mParts[i]->setPosition(Vec);
			//	}
			//}
			mFeet.setPosition(Vec);
			mBody.setPosition(Vec);
		}
		else if(mBodyActive)
		{
			mBody.setPosition(Vec);
			if(mHeadless==false)
			{
				//mHead.setPosition(Vec);
			}
		}
		else
		{
			if(UnitManager::isCollidedSide(0, 4) && Vec.x<0 && mKeys==false && lastKey!=0)
			{
				mFeet.setAttachedWall(true, 0);
			}
			else if(UnitManager::isCollidedSide(0, 3) && Vec.x>0 && mKeys==false && lastKey!=0)
			{
				mFeet.setAttachedWall(true, 2);
			}
			else if(UnitManager::isCollidedSide(0, 1) && Vec.y<0 && mKeys==false)
			{
				mFeet.forceMove(sf::Vector2f(0, -16));
				mFeet.setAttachedWall(true, 1);
			}
			else if(UnitManager::isCollidedSide(0, 2) && Vec.y>0 && mKeys==false)
			{
				mFeet.setAttachedWall(false);
			}
			else
			{
				mFeet.setPosition(Vec);
			}
		}
	}
	else
	{
		if(Vec.x>0 && mFacingRight==false)
		{
			mDashing=false;
			mDash=0;
		}
		if(Vec.x<0 && mFacingRight==true)
		{
			mDashing=false;
			mDash=0;
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
		mBodyActive=false;
		mBody.setAttached(false);
		mTogether=b;
		Sound::playSound("Split");
	}
	else if((mFeet.getPosition().x-mBody.getPosition().x)*(mFeet.getPosition().x-mBody.getPosition().x) +
		(mFeet.getPosition().y-mBody.getPosition().y)*(mFeet.getPosition().y-mBody.getPosition().y) < 70*70 
		&& mFeet.getAttached()==false && mFeet.getAttachedWall()==false && mFeet.getPosition().y-20>mBody.getPosition().y
		&& !UnitManager::isCollidedSide(5, 1) && !UnitManager::isCollidedSide(5, 3) && !UnitManager::isCollidedSide(5, 4))
	{
		//mBodyActive=false;
		mBody.setAttached(true);
		mTogether=b;
		//mFeet.forceMove(mBody.getPosition()-mFeet.getPosition()+sf::Vector2f(0, 64));
		Player::move(sf::Vector2f((float)-0.1, 0));
		Player::move(sf::Vector2f((float)0.1, 0));
		mFeet.restartAnimation();
		mBody.restartAnimation();
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
void Player::setHeadless(bool b)
{
	mHeadless=b;
}
bool Player::getHeadless()
{
	return mHeadless;
}
//Enskilda funktioner för specifika delar
void Player::jump()
{
	if(mDashing==false/* && mJumpTemp.getElapsedTime().asSeconds()>0.5*/)
	{
		if(mTogether==true && UnitManager::isCollidedSide(0, 2))
		{
			mFeet.jump(Eric::getJump());
			mBody.jump(Eric::getJump());
			Sound::playSound("Jump");
		}
		if(mBodyActive==true && UnitManager::isCollidedSide(1, 2) || mBodyActive==true && mBodyStandingFeet==true || mBodyActive==true && (mAttachedMagnet==true && mBodyAttached==true))
		{
			mBody.jump(Eric::getJump());
			Sound::playSound("Jump");
		}
		if(mBodyActive==false && mTogether==false)
		{
			if(UnitManager::isCollidedSide(0, 2) || (mAttachedMagnet==true && mBodyAttached==false))
			{
				mFeet.jump(Eric::getJump());
				Sound::playSound("Jump");
				mJumpTemp2.restart();
			}
	/*		else if(!UnitManager::isCollidedSide(0, 2) && mJumpTemp2.getElapsedTime().asSeconds() > 0.5)
			{
				mFeet.activateRocketBoots();
				mRocketing=false;
			}*/
		}
	}	
}
void Player::shootHead(sf::Vector2f Vec)
{
	if(mHead.getAttached()==false)
	{
		mHead.setAttached(true);
		mHead.setShootVector(sf::Vector2f(0, 0));
		mHeadless=false;
		magnetSlot=2;
		mHeadAttachedFeet=false;
		mAttachedMagnet=false;
	}
	else if(mHead.getAttached()==true)
	{
		Sound::playSound("ShootHead");
		mHeadless=true;	
		float k=(mHead.getPosition().y-Vec.y)/(mHead.getPosition().x-Vec.x);

		//float k=(mHead.getSprite().getLocalBounds().top-Vec.y)/(mHead.getSprite().getLocalBounds().left-Vec.x);

		//float l=sqrt((mHead.getPosition().y-Vec.y)*(mHead.getPosition().y-Vec.y) + (mHead.getPosition().x-Vec.x)*(mHead.getPosition().x-Vec.x));
		//float Ys=mHead.getPosition().y-Vec.y;
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
		/*float Derivata=sqrt((xValue/q)*(xValue/q)+(k/q)*(k/q));
		std::cout << k/q << " " << Derivata << " " << sin((k/q)/Derivata) << std::endl; 
		float s=sin((k/q)/Derivata);
		float degrees = (asin(s)*180/3.1416)*1.5;
		std::cout << degrees << std::endl << std::endl;*/
	}
}
void Player::setAttachFeetExtension(bool b)
{
	sf::FloatRect Test(mFeet.getSprite().getGlobalBounds());
	if(mFeet.getAttachedWall()==false)
	{
		if(b==true)
		{
			Test.top-=32;
			Test.height+=32;
			Test.width-=50;
			Test.left+=25;
		}
		else
		{
			mFeet.jumpReset();
			Test.width-=50;
			Test.left+=25;
			Test.top+=5;
			Test.height-=5;
		}
	}
	else if(mFeet.getWall()==0)
	{
		if(b==true)
		{
			Test.width+=32;
			Test.height-=50;
			Test.top+=25;
		}
		else
		{
			Test.height-=50;
			Test.top+=25;
		}
	}
	else if(mFeet.getWall()==2)
	{
		if(b==true)
		{
			Test.width+=32;
			Test.left-=32;
			Test.height-=50;
			Test.top+=25;
		}
		else
		{
			Test.height-=50;
			Test.top+=25;
		}
	}
	else
	{
		if(b==true)
		{
			Test.height+=32;
			Test.width-=50;
			Test.left+=25;
		}
		else
		{
			Test.width-=50;
			Test.left+=25;
		}
	}
	if(!mBody.getSprite().getGlobalBounds().intersects(Test))
	{	
		if(mFeet.getAttachedWall()==true && b==true)
		{
			if(mFeet.getWall()==0 && UnitManager::isCollidedSide(0, 4) && !UnitManager::isCollidedSide(4, 1) && !UnitManager::isCollidedSide(4, 2) && !UnitManager::isCollidedSide(4, 3))
			{
				mFeetAttached=b;
				mFeet.setAttached(b);
			}
			else if(mFeet.getWall()==1 && UnitManager::isCollidedSide(0, 1) && !UnitManager::isCollidedSide(4, 4) && !UnitManager::isCollidedSide(4, 2) && !UnitManager::isCollidedSide(4, 3))
			{
				
				mFeetAttached=b;
				mFeet.setAttached(b);
			}
			else if(mFeet.getWall()==2 && UnitManager::isCollidedSide(0, 3) && !UnitManager::isCollidedSide(4, 1) && !UnitManager::isCollidedSide(4, 2) && !UnitManager::isCollidedSide(4, 4))
			{
				mFeetAttached=b;
				mFeet.setAttached(b);
			}
		}
		else if(b==true && UnitManager::isCollidedSide(0, 2) && !UnitManager::isCollidedSide(4, 1) && !UnitManager::isCollidedSide(4, 3) && !UnitManager::isCollidedSide(4, 4))
		{
			mFeetAttached=b;
			mFeet.setAttached(b);
		}
		if(b==false)
		{
			mFeetAttached=b;
			mFeet.setAttached(b);
		}
		//if(b==true && mFeetAttached==true)
		//{
		//	mBodyActive=true;
		//}
		if(mHeadAttachedFeet==true)
		{
			mHead.setAttached(true);
			mHeadAttachedFeet=false;
			mAttachedMagnet=false;
			mBody.jumpReset();
		}
	}
	else
	{
		Sound::playSound("ExtBodyColl");
	}
}
bool Player::getAttachFeetExtension()
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
	Sound::playSound("Dash");
}
void Player::activateFeetRockets()
{
	mFeet.activateRocketBoots();
	//mRocketing=true;
}
void Player::reFuel()
{
	mFeet.reFuel();
}

void Player::interact(int action)
{
	if(mWinning==false && mDying==false)
	{
		if(mClockStart==false)
		{
			mClockStart=true;
			mClock.restart();
			Timer::start();
		}
		thisKey=action;
		if(thisKey==lastKey)
		{
			mKeys=true;
		}
		else
		{
			mKeys=false;
		}
		if(action==0)
		{
			mKeyTimer.restart();
			//Upp
			if(mTogether==true || mBodyActive==true)
			{
				Player::jump();
			}
			else if(mFeet.getAttached()==false && mFeet.getAttachedWall()==false)
			{
				Player::jump();
				mRocketing=true;
			}
			else if(mFeet.getAttached()==false)
			{
				if(mFeet.getWall()==0 || mFeet.getWall()==2)
				{
					Player::move(sf::Vector2f(0, -1));
					Sound::playSound("Move");
				}
			}
			if(mAttachedMagnet==true && mBodyActive==mBodyAttached && mJumpTemp.getElapsedTime().asSeconds()>Eric::getJumpdelayMagnet())
			{
				mHead.setMagnetSolid(false);
				mAttachedMagnet=false;
				mMagnetTimer.restart();
			}
			lastKey=action;
		}
		if(action==1)
		{
			mKeyTimer.restart();
			//Höger
			if(mTogether==true || mBodyActive==true)
			{
				Player::move(sf::Vector2f(1, 0));
			}
			else if(mFeet.getAttached()==false && mFeet.getAttachedWall()==false)
			{
				Player::move(sf::Vector2f(1, 0));
			}
			else if(mFeet.getAttached()==false)
			{
				if(mFeet.getWall()==1)
				{
					Player::move(sf::Vector2f(1, 0));
				}
				else if(mFeet.getWall()==0)
				{
					mFeet.setAttachedWall(false);
					mFeet.jumpReset();
				}
			}
			if(mTogether==true&&UnitManager::isCollidedSide(0, 2) || (mBodyActive==false && mFeet.getAttachedWall()==false && UnitManager::isCollidedSide(0, 2)) || mBodyActive==false&&mFeet.getAttachedWall()==true&&mFeet.getWall()==1)
			{
				Sound::playSound("Move");
			}
			else
			{
				Sound::stopSound("Move");
			}
			lastKey=action;
		}
		if(action==2)
		{
			mKeyTimer.restart();
			//Vänster
			if(mTogether==true || mBodyActive==true)
			{
				Player::move(sf::Vector2f(-1, 0));
			}
			else if(mFeet.getAttached()==false && mFeet.getAttachedWall()==false)
			{
				Player::move(sf::Vector2f(-1, 0));
			}
			else if(mFeet.getAttached()==false)
			{
				if(mFeet.getWall()==1)
				{
					Player::move(sf::Vector2f(-1, 0));
				}
				else if(mFeet.getWall()==2)
				{
					mFeet.setAttachedWall(false);
					mFeet.jumpReset();
				}
			}
			if(mTogether==true&&UnitManager::isCollidedSide(0, 2) || (mBodyActive==false && mFeet.getAttachedWall()==false && UnitManager::isCollidedSide(0, 2)) || mBodyActive==false&&mFeet.getAttachedWall()==true&&mFeet.getWall()==1)
			{
				Sound::playSound("Move");
			}
			else
			{
				Sound::stopSound("Move");
			}
			lastKey=action;
		}
		if(action==3)
		{
			mKeyTimer.restart();
			//Ner "S"
			if(mBodyActive==false && mFeet.getAttached()==false && mFeet.getAttachedWall()==true)
			{
				if(mFeet.getWall()==1)
				{
					mFeet.setAttachedWall(false);
					mFeet.jumpReset();
				}
				else
				{
					Player::move(sf::Vector2f(0, 1));
					Sound::playSound("Move");
				}
			}
			if(mAttachedMagnet==true && mBodyActive==mBodyAttached)
			{
				mHead.setMagnetSolid(false);
				mAttachedMagnet=false;
				mBody.jumpReset();
				mFeet.jumpReset();
				mMagnetTimer.restart();
			}
			lastKey=action;
		}
		if(action==4)
		{
			//RocketBoost
			if(mTogether==false && mBodyActive==false && mFeet.getAttached()==false && mFeet.getAttachedWall()==false)
			{
				Player::activateFeetRockets();
			}
			if(UnitManager::isCollidedSide(0, 1) && lastKey==0)
			{
				mFeet.setAttachedWall(true, 1);
			}
		}
		if(action==5)
		{
			//Ihop/Isär
			Player::setTogether(!mTogether);
		}
		if(action==6)
		{
			//Skifta
			if(mTogether==false)
			{
				Player::setBodyActive(!mBodyActive);
			}
		}
		if(action==7)
		{
			//FeetExt
			if(mTogether==false && mBodyActive==false)
			{
				Player::setAttachFeetExtension(!mFeetAttached);
			}
		}
		if(action==8)
		{
			if(mTogether==true && UnitManager::isCollidedSide(0, 2))
			{
				Player::dash();
			}
		}
	}
}
//Kollisioner
std::vector<sf::Sprite*> Player::getCollisionSprite()
{
	std::vector<sf::Sprite*> Parts;
	//if(mTogether==true){
	//	mSprite.setPosition(mFeet.getPosition() + sf::Vector2f(0, -64));
	//	*Temp1=mSprite;
	//	Parts.push_back(Temp1);
	//	if(mHeadless==true){
	//		*Temp2=mHead.getSprite();
	//		Parts.push_back(Temp2);
	//		*Temp4=TempPart->getSprite();
	//		Parts.push_back(Temp4);
	//	}
	//}
	//else{
		*TempFeet=mFeet.getSprite();
		Parts.push_back(TempFeet);
		*TempBody=mBody.getSprite();
		Parts.push_back(TempBody);
		*TempHead=mHead.getSprite();
		Parts.push_back(TempHead);
		*TempMagnet=TextureManager::getSprite("StixUpper");
		TempMagnet->setPosition(TempPart->getPosition());
		Parts.push_back(TempMagnet);
		*TempExtension=TextureManager::getSprite("StixFeetExtend");
		TempExtension->setTextureRect(sf::IntRect(TempExtension->getTextureRect().left, TempExtension->getTextureRect().left, TempExtension->getTextureRect().width-2, TempExtension->getTextureRect().height-2));
		TempExtension->setPosition(TempFeet->getPosition()+sf::Vector2f(1, -31));
		if(mFeet.getAttachedWall()==true && mFeet.getWall()==1)
		{
			TempExtension->setPosition(TempExtension->getPosition()+sf::Vector2f(0, 16));
		}
		Parts.push_back(TempExtension);
		*TempWhole=TextureManager::getSprite("StixWhole");
		TempWhole->setTextureRect(sf::IntRect(TempExtension->getTextureRect().left, TempExtension->getTextureRect().left, TempExtension->getTextureRect().width-2, TempExtension->getTextureRect().height-2));
		TempWhole->setPosition(TempFeet->getPosition()+sf::Vector2f(1, -63));
		Parts.push_back(TempWhole);
	//}
	return Parts;
}
void Player::forceMove(int part, sf::Vector2f Vec)
{
	if(Vec!=sf::Vector2f(0, 0))
	{
		if(part==0 && mTogether==false)
		{
			if(!mFeet.getAttached())
			{
				if(Vec.y!=0 && mFeet.getAttachedWall()==false)
				{
					mFeet.jumpReset();
				}
				mFeet.forceMove(Vec);
			}
		}
		else if(part==1 && mTogether==false)
		{
			if(Vec.y!=0)
			{
				mBody.jumpReset();
			}
			mBody.forceMove(Vec);
		}
		else if(part==2)
		{
			mHead.forceMove(Vec);
			mHead.setShootVector(sf::Vector2f(0, 0));
			mMagnetTimer.restart();
		}
		else if(part==3)
		{
			std::cout << "ForceMoved Magnet";
		}
		else if(part==4)
		{
			std::cout << "ForceMoved Extension";
		}
		else if(part==5)
		{
			std::cout << "ForceMoved Whole";
		}
		else
		{
			if(Vec.y!=0)
			{
				mBody.jumpReset();
				mFeet.jumpReset();
			}
			mFeet.forceMove(Vec);
			mBody.forceMove(Vec);
		}
	}
}
void Player::checkCollisionExt(){

	sf::FloatRect ColRect;
	sf::FloatRect TempFeet=mFeet.getSprite().getGlobalBounds();
	if(mFeet.getAttachedWall()==false || (mFeet.getAttachedWall()==true && mFeet.getWall()==1))
	{
		TempFeet.width-=50;
		TempFeet.left+=25;
		TempFeet.top+=2;
		TempFeet.height-=16;
	}
	else
	{
		TempFeet.height-=50;
		TempFeet.top+=25;
	}
	if(mBody.getSprite().getGlobalBounds().intersects(TempFeet, ColRect))
	{
		if(mBody.getPosition().y<(TempFeet.top-45))
		{
			mBodyStandingFeet=true;
		}
		if(ColRect.width<ColRect.height && mBodyStandingFeet==false)
		{
			if(mBody.getSprite().getPosition().x > mFeet.getSprite().getPosition().x)
			{
				mBody.forceMove(sf::Vector2f(ColRect.width, 0));
			}
			else
			{
				mBody.forceMove(sf::Vector2f(-ColRect.width, 0));
			}
		}
		else
		{
			if(mBody.getSprite().getPosition().y > mFeet.getSprite().getPosition().y)
			{
				mBody.forceMove(sf::Vector2f(0, ColRect.height));
				mBody.jumpReset();
			}
			else
			{
				mBody.forceMove(sf::Vector2f(0, -ColRect.height));
				mBody.jumpReset();
			}
		}
	}
	if(mFeet.getAttachedWall()==false || (mFeet.getAttachedWall()==true && mFeet.getWall()==1))
	{
		TempFeet.height+=16;
	}
	if(mHeadless==true)
	{
		sf::FloatRect ColRect2;
		if(mHead.getSprite().getGlobalBounds().intersects(TempFeet, ColRect2))
		{
			mHeadAttachedFeet=true;
			if(ColRect2.width<=ColRect2.height)
			{
				if(mHead.getSprite().getPosition().x > TempFeet.left)
				{
					mHead.forceMove(sf::Vector2f(ColRect2.width, 0));
				}
				else
				{
					mHead.forceMove(sf::Vector2f(-ColRect2.width, 0));
				}
			}
			else
			{
				if(mHead.getSprite().getPosition().y > TempFeet.top)
				{
					mHead.forceMove(sf::Vector2f(0, ColRect2.height));
				}
				else
				{
					mHead.forceMove(sf::Vector2f(0, -ColRect2.height));
				}
			}
		}
	}
}
void Player::checkCollisionMagnet()
{
	if(mHead.getUnit()->isSolid()==false){
		if(mMagnetTimer.getElapsedTime().asSeconds()>0.5)
		{
			mHead.setMagnetSolid(true);
			magnetSlot=2;
		}
	}
	sf::Vector2f TempBody=mBody.getSprite().getPosition()+sf::Vector2f(mBody.getSprite().getGlobalBounds().width/2, mBody.getSprite().getGlobalBounds().height/2);
	sf::Vector2f TempFeet=mFeet.getSprite().getPosition()+sf::Vector2f(mFeet.getSprite().getGlobalBounds().width/2, mFeet.getSprite().getGlobalBounds().height/2);
	sf::Vector2f TempHead=mHead.getUnit()->getSprite().getPosition();
	if(mHead.getUnit()->getSprite().getRotation()<=0)
	{
		TempHead+=sf::Vector2f(mHead.getUnit()->getSprite().getGlobalBounds().width/2*(1-(mHead.getUnit()->getSprite().getRotation()/45))-8, mHead.getUnit()->getSprite().getGlobalBounds().height-10*(1-(mHead.getUnit()->getSprite().getRotation()/45))/**(mHead.getUnit()->getSprite().getRotation()/-45)*/);
	}
	else
	{
		TempHead+=sf::Vector2f(-mHead.getUnit()->getSprite().getGlobalBounds().width/2*(1-(mHead.getUnit()->getSprite().getRotation()/-45))+8, mHead.getUnit()->getSprite().getGlobalBounds().height-10*(1-(mHead.getUnit()->getSprite().getRotation()/-45))/**(mHead.getUnit()->getSprite().getRotation()/45)*/);
	}
	if((TempBody.x-TempHead.x)*(TempBody.x-TempHead.x)+(TempBody.y-TempHead.y)*(TempBody.y-TempHead.y)<48*16 && mHead.getUnit()->isSolid()==true && magnetSlot!=0)
	{
		mAttachedMagnet=true;
		mBodyAttached=true;
		if(magnetSlot!=1)
		{
			mJumpTemp.restart();
		}
		magnetSlot=1;
		mBody.jumpReset();
		mBody.forceMove(TempHead-TempBody);
	}
	else if((TempFeet.x-TempHead.x)*(TempFeet.x-TempHead.x)+(TempFeet.y-TempHead.y)*(TempFeet.y-TempHead.y)<48*16 && mHead.getUnit()->isSolid()==true && magnetSlot!=1)
	{
		mAttachedMagnet=true;
		mBodyAttached=false;
		if(magnetSlot!=0)
		{
			mJumpTemp.restart();
		}
		magnetSlot=0;
		mFeet.jumpReset();
		mFeet.forceMove(TempHead-TempFeet);
	}
}
void Player::restartPlayer()
{
	mHead.setAttached(true);
	mBody.setAttached(true);
	mFeet.setAttached(false);
	mFeet.setAttachedWall(false);
	mBody.jumpReset();
	mFeet.jumpReset();
	mTogether=true;
	mFeetAttached=false;
	Player::move(sf::Vector2f((float)0.1, 0));
	mFeet.forceMove(mStartPosition-mFeet.getPosition());
	mFeet.reFuel();
	mBodyActive=false;
	mClock.restart();
	Timer::stop();
	mClockStart=false;
	mWinning=false;
	mDying=false;

	mFeet.aniTimer();
	mBody.aniTimer();
}
std::string Player::getId(int i)
{
	return mParts[i]->getId();
}
void Player::dropFeet()
{
	mFeet.setAttachedWall(false);
	mFeet.jumpReset();
}

bool Player::getDying()
{
	return mDying;
}
void Player::die(int part)
{
	mDying=true;
	mHead.setAttached(true);
	mHeadless=false;
	if(mTogether==true)
	{
		mFeet.die();
		mBody.die();
		mBodyDied=true;
	}
	else if(part==0)
	{
		if(mFeet.getAttached()==true)
		{
			mFeet.setAttached(false);
		}
		mFeet.die();
		mBodyDied=false;
	}
	else
	{
		mBodyDied=true;
		mBody.die();
	}
}
void Player::win(){
	if(mWinning==false)
	{
		mFeet.winning();
		mBody.winning();
		Timer::stop();
		mWinning=true;
		//Sound::stopSound("Jump");
		Sound::playSound("Winning");
		std::cout << "Finishing time: " << mClock.getElapsedTime().asSeconds() << std::endl;
	}
}
bool Player::getWinning()
{
	return mWinning;
}
void Player::setStartingPosition(sf::Vector2f Vec)
{
	mStartPosition=Vec;
}