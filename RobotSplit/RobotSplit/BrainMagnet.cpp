#include "BrainMagnet.h"
#include <iostream>

BrainMagnet::BrainMagnet(std::string spriteName):
	Unit(sf::Vector2f(100, 100), "FeetExt", spriteName),
	mBrain ("StixBrainLowered", 200, 1),
	mBrainAni("StixBrainAni", 200, 8)
{
	mSprite=TextureManager::getSprite(spriteName);
	mSolid=true;
	mTimer.restart();
	mActiveAnimation=&mBrainAni;
}

void BrainMagnet::setSolid(bool b){
	mSolid=b;
}

void BrainMagnet::update(){
	mActiveAnimation->update();
	if(mBrainAni.getCurrentFrame()!=7){
		mActiveAnimation=&mBrainAni;
	}
	else{
		mActiveAnimation=&mBrain;
	}
}

sf::Sprite BrainMagnet::getSprite(){
	mActiveAnimation->setPosition(mPosition);
	return mActiveAnimation->getSprite();
}