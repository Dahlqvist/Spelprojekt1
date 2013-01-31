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
	mLjus1.loadFromFile("Texture/Stix/stix_sil_full.png");
	mLjus2.loadFromFile("Texture/Stix/stix_sil_lower.png");
	mLjus3.loadFromFile("Texture/Stix/stix_sil_upper.png");
	mLjus.setTexture(mLjus1);
	mDash=0;
	mFacingRight=true;
	mJumpTemp.restart();
	Temp1=new sf::Sprite;
	Temp2=new sf::Sprite;
	Temp3=new sf::Sprite;
}
//Kontroller och funktioner för Player
void Player::draw(sf::RenderWindow& Window)
{
	/*if(mTogether==true)
	{
		mSprite.setPosition(mFeet.getPosition() + sf::Vector2f(0, -64));
		Window.draw(mSprite);
	}
	else
	{*/
	if(mTogether==true)
	{
		mLjus.setTexture(mLjus1);
		mLjus.setPosition(mBody.getPosition()+sf::Vector2f(-mSprite.getGlobalBounds().width/2, -mSprite.getGlobalBounds().height/2));
	}
	else if(mBodyActive==true)
	{
		mLjus.setTexture(mLjus3);
		mLjus.setPosition(mBody.getPosition()+sf::Vector2f(-mBody.getSprite().getGlobalBounds().width/2, -mBody.getSprite().getGlobalBounds().height/2));
	}
	else
	{
		if(mFeet.getAttachedWall()==true && (mFeet.getWall()==0 || mFeet.getWall()==2))
		{
			mLjus.setTexture(mLjus2);
		mLjus.setPosition(mFeet.getPosition()+sf::Vector2f(-32, -64));
		}
		else
		{
		mLjus.setTexture(mLjus2);
		mLjus.setPosition(mFeet.getPosition()+sf::Vector2f(-32, -48));
		}
	}
	Window.draw(mLjus);
	Window.draw(mFeet.getSprite());
	Window.draw(mHead.getSprite());
	Window.draw(mBody.getSprite());
	for(unsigned int i=0; i<mParts.size(); i++)
		{
			if(mParts[i]->getUnit()!=0)
			{
				Window.draw(mParts[i]->getUnit()->getSprite());
			}	
		}
	//}
	//Window.draw(mBody.getObject()->getSprite());
}
void Player::update()
{
	for(unsigned int i=0; i < mParts.size(); i++)
	{
		mParts[i]->update();
		if(mParts[i]->getPosition().y+mParts[i]->getSprite().getGlobalBounds().height<700)
		{
			if(i==1)
			{
				mParts[i]->setPosition(sf::Vector2f(0, 3));
			}
			else if(i==0 && mFeet.getAttached()==false && mFeet.getAttachedWall()==false)
			{
				mParts[i]->setPosition(sf::Vector2f(0, 3));
			}
		}
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

	if(mTogether==false && mFeet.getAttached()==true){
		Player::checkCollisionExt();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		if(mTogether==false && mBodyActive==false && mFeet.getAttached()==false){
			mFeet.setAttachedWall(true, 0);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		if(mTogether==false && mBodyActive==false && mFeet.getAttached()==false){
			mFeet.setAttachedWall(true, 1);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		if(mTogether==false && mBodyActive==false && mFeet.getAttached()==false){
			mFeet.setAttachedWall(true, 2);
		}
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		if(mFeet.getAttached()==false){
			mFeet.setAttachedWall(false);
		}
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
	else
	{
		if(Vec.x>0 && mFacingRight==false){
			mDashing=false;
			mDash=0;
		}
		if(Vec.x<0 && mFacingRight==true){
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
	}
	else if((mFeet.getPosition().x-mBody.getPosition().x)*(mFeet.getPosition().x-mBody.getPosition().x) +
		(mFeet.getPosition().y-mBody.getPosition().y)*(mFeet.getPosition().y-mBody.getPosition().y) < 70*70 
		&& mFeet.getAttached()==false && mFeet.getAttachedWall()==false)
	{
		//mBodyActive=false;
		mBody.setAttached(true);
		mTogether=b;
		Player::move(sf::Vector2f(-0.1, 0));
		Player::move(sf::Vector2f(0.1, 0));
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
	if(mJumpTemp.getElapsedTime().asSeconds()>1.0)
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
		mJumpTemp.restart();
	}	
}
void Player::shootHead(sf::Vector2f Vec)
{
	if(mHead.getAttached()==false)
	{
		mHead.setAttached(true);
		mHead.setShootVector(sf::Vector2f(0, 0));
		mHeadless=false;
	}
	else if(mHead.getAttached()==true)
	{
		mHeadless=true;
		float k=(mHead.getPosition().y-Vec.y)/(mHead.getPosition().x-Vec.x);
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
	if(!mFeet.getSprite().getGlobalBounds().intersects(mBody.getSprite().getGlobalBounds()))
	{
		mFeetAttached=b;
		mFeet.setAttached(b);
	}
	//else if(u==1){
	//	mFeetAttached=b;
	//	if(b==true)
	//	{
	//		mFeet.pointTo(u);
	//		mFeet.setAttached(true);
	//	}
	//	if(b==false)
	//	{
	//		mFeet.pointTo(u);
	//		mFeet.setAttached(false);
	//	}
	//}
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
}
void Player::activateFeetRockets(){
	mFeet.activateRocketBoots();
}
void Player::reFuel(float fuel){
	mFeet.reFuel(fuel);
}
//Göra om till string sen när alla kontroller är satta
void Player::interact(int action){
	if(action==0)
	{
		//Upp
		if(mTogether==true || mBodyActive==true){
			Player::jump();
		}
		else if(mFeet.getAttached()==false && mFeet.getAttachedWall()==false){
				Player::jump();
			}
		else if(mFeet.getAttached()==false){
			if(mFeet.getWall()==0 || mFeet.getWall()==2)
			{
				mFeet.setPosition(sf::Vector2f(0, -1));
			}
		}
	}
	if(action==1)
	{
		//Höger
		if(mTogether==true || mBodyActive==true){
			Player::move(sf::Vector2f(1, 0));
		}
		else if(mFeet.getAttached()==false && mFeet.getAttachedWall()==false){
				Player::move(sf::Vector2f(1, 0));
			}
		else if(mFeet.getAttached()==false){
			if(mFeet.getWall()==1)
			{
				mFeet.setPosition(sf::Vector2f(1, 0));
			}
			else if(mFeet.getWall()==0){
				mFeet.setAttachedWall(false);
			}
		}
	}
	if(action==2)
	{
		//Vänster
		if(mTogether==true || mBodyActive==true){
			Player::move(sf::Vector2f(-1, 0));
		}
		else if(mFeet.getAttached()==false && mFeet.getAttachedWall()==false){
				Player::move(sf::Vector2f(-1, 0));
			}
		else if(mFeet.getAttached()==false){
			if(mFeet.getWall()==1)
			{
				mFeet.setPosition(sf::Vector2f(-1, 0));
			}
			else if(mFeet.getWall()==2){
				mFeet.setAttachedWall(false);
			}
		}
		//if(mTogether==true || mBodyActive==true)
		//{
		//	Player::move(sf::Vector2f(-1, 0));
		//}
		//else if(mFeet.getAttached()==false)
		//{
		//	Player::move(sf::Vector2f(-1, 0));
		//}
		//else if(mFeet.getAttached()/*==Wall side*/){}
		//else if(mFeet.getAttached()/*==Top*/){}
	}
	if(action==3)
	{
		//Ner "S"
		if(mTogether==true)
		{
			Player::dash();
		}
		else if(mBodyActive==false && mFeet.getAttached()==false && mFeet.getAttachedWall()==true)
		{
			if(mFeet.getWall()==1)
			{
				mFeet.setAttachedWall(false);
			}
			else
			{
				mFeet.setPosition(sf::Vector2f(0, 1));
			}
		}
	}
	if(action==4)
	{
		//RocketBoost
		if(mTogether==false && mBodyActive==false && mFeet.getAttached()==false && mFeet.getAttachedWall()==false){
			mFeet.activateRocketBoots();
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
}
//Kollisioner
std::vector<sf::Sprite*> Player::getCollisionSprite()
{
	std::vector<sf::Sprite*> Parts;
	if(mTogether==true){
		mSprite.setPosition(mFeet.getPosition() + sf::Vector2f(0, -64));
		*Temp1=mSprite;
		Parts.push_back(Temp1);
		if(mHeadless==true){
			*Temp2=mHead.getSprite();
			Parts.push_back(Temp2);
		}
	}
	else{
		*Temp1=mFeet.getSprite();
		Parts.push_back(Temp1);
		*Temp2=mBody.getSprite();
		Parts.push_back(Temp2);
		*Temp3=mHead.getSprite();
		Parts.push_back(Temp3);
	}
	return Parts;
}
void Player::forceMove(int part, sf::Vector2f Vec)
{
	if(part==0)
	{
		if(Vec.y>0 && mFeet.getAttachedWall()==false)
		{
			mFeet.jumpReset();
		}
		mFeet.forceMove(Vec);
	}
	else if(part==1)
	{
		if(Vec.y>0)
		{
			mBody.jumpReset();
		}
		mBody.forceMove(Vec);
	}
	else if(part==2)
	{
		mHead.forceMove(Vec);
		mHead.setShootVector(sf::Vector2f(0, 0));
	}
	else
	{
		if(Vec.y>0)
		{
			mBody.jumpReset();
			mFeet.jumpReset();
		}
		mFeet.forceMove(Vec);
		mBody.forceMove(Vec);
	}
}
void Player::checkCollisionExt(){

	sf::FloatRect ColRect;
	sf::FloatRect TempFeet=mFeet.getSprite().getGlobalBounds();
	if(mFeet.getAttachedWall()==false || (mFeet.getAttachedWall()==true && mFeet.getWall()==1))
	{
		TempFeet.width-=50;
		TempFeet.left+=25;
	}
	else{
		TempFeet.height-=50;
		TempFeet.top+=25;
	}
	if(mBody.getSprite().getGlobalBounds().intersects(TempFeet, ColRect)){
		
		if(ColRect.width<ColRect.height)
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
			}
			else
			{
				mBody.forceMove(sf::Vector2f(0, -ColRect.height));
			}
		}
	}
	if(mHeadless==true){
		sf::FloatRect ColRect2;
		if(mHead.getSprite().getGlobalBounds().intersects(TempFeet, ColRect2)){
		
			if(ColRect2.width<ColRect2.height)
			{
				if(mHead.getSprite().getPosition().x > mFeet.getSprite().getPosition().x)
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
				if(mHead.getSprite().getPosition().y > mFeet.getSprite().getPosition().y)
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