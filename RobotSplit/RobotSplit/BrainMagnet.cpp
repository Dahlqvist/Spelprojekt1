#include "BrainMagnet.h"

BrainMagnet::BrainMagnet(std::string spriteName):
	Unit(sf::Vector2f(100, 100), "FeetExt", spriteName),
	mBrain ("StixBrainLowered", 200, 1),
	mBrainAni("StixBrainAni", 200, 8)
{
	mSprite=TextureManager::getSprite(spriteName);
	mSolid=true;
	mTimer.restart();
	mActiveAnimation=&mBrain;
}

void BrainMagnet::setSolid(bool b){
	mSolid=b;
}

void BrainMagnet::update(){
	mActiveAnimation->update();
	if(mTimer.getElapsedTime().asSeconds() < 1.6){
		mActiveAnimation=&mBrainAni;
	}
	else{
		mActiveAnimation=&mBrain;
	}
}