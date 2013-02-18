#include "BrainMagnet.h"
#include <iostream>

BrainMagnet::BrainMagnet(std::string spriteName):
	Unit(sf::Vector2f(100, 100), "FeetExt", spriteName),
	mBrain ("StixBrainLowered", 200, 1),
	mBrainAni("StixBrainAni", 50, 8)
{
	mSprite=TextureManager::getSprite(spriteName);
	mSolid=true;
	mTimer.restart();
	mActiveAnimation=&mBrainAni;
	mRotation=0;
	mRot=0;
	ropeSwing=true;
}

void BrainMagnet::setSolid(bool b){
	mSolid=b;
}

void BrainMagnet::update(){
	mActiveAnimation->update();

	if(mRot>=45)
	{
		ropeSwing=false;
	}
	if(mRot<=-45)
	{
		ropeSwing=true;
	}
	if(ropeSwing==true && mActiveAnimation==&mBrain)
	{
		if(mRot<20 && mRot>-20)
		{
			mRot+=1.7;
		}
		else
		{
			mRot+=1.3;
		}
		BrainMagnet::rotate(mRot);
	}
	else if(ropeSwing==false && mActiveAnimation==&mBrain)
	{
		if(mRot>-20 && mRot<20)
		{
			mRot-=1.7;
		}
		else
		{
			mRot-=1.3;
		}
		BrainMagnet::rotate(mRot);
	}

	if(mBrainAni.getCurrentFrame()!=7){
		mActiveAnimation=&mBrainAni;
		mSolid=false;
	}
	else{
		mActiveAnimation=&mBrain;
	}
}

sf::Sprite BrainMagnet::getSprite(){
	mActiveAnimation->setPosition(mPosition);
	mSprite=mActiveAnimation->getSprite();
	mSprite.setPosition(mSprite.getPosition()+sf::Vector2f(mSprite.getGlobalBounds().width/2, 10));
	mSprite.setOrigin(mSprite.getGlobalBounds().width/2, 0);
	mSprite.setRotation(mRotation);
	return mSprite;
}
void BrainMagnet::restartAnimations(){
	mBrainAni.restart();
	mTimer.restart(); 
	mActiveAnimation=&mBrainAni;
	mRot=0;
	mRotation=0;
	ropeSwing=false;
}